#include "ModbusSlaveDevice.h"


#include "stddef.h"


ModbusSlaveDevice::ModbusSlaveDevice(uint16_t slave_id, int input_regs, int hold_regs)
{
    if (input_regs > MAX_INPUT_REGISTERS || hold_regs > MAX_HOLDING_REGISTERS)
    {
        mdb_slave_status = -1;
        return;
    }
    
    mdb_slave_status = 1;
    
    this->interface = NULL;
    this->crc = NULL;
    
    this->id = slave_id;
    
    this->input_regs_quantity = input_regs;
    for (uint32_t i = 0; i < input_regs; i++)
    {
        this->input_registers[i] = 0;
    }
    this->hold_regs_quantity = hold_regs;
    for (uint32_t i = 0; i < hold_regs; i++)
    {
        this->holdings_registers[i].value = 0x00;
        this->holdings_registers[i].max = 0xFFFF;
        this->holdings_registers[i].min = 0x00;
    }

}
void ModbusSlaveDevice::set_driver (IModbusRTU_Driver * drv)
{
    this->interface = drv;
}

void ModbusSlaveDevice::set_crc (IModbusRTU_CRC * c)
{
    this->crc = c;
}
int ModbusSlaveDevice::set_input_reg(uint16_t reg_num, uint16_t value)
{
    //проверка инициализации
    if (mdb_slave_status != 1)
        return -5;
    
    //проверка номера регистра
    if (reg_num >= this->input_regs_quantity)
        return -5;
    
    this->input_registers[reg_num] = value;
    return 0;
}

int ModbusSlaveDevice::set_holding_reg(uint16_t reg_num, uint16_t value)
{
    //проверка инициализации
    if (mdb_slave_status != 1)
        return -5;
    
    //проверка номера регистра
    if (reg_num >= this->hold_regs_quantity)
        return -5;
    
    //проверка значения для записи в регистр
    if (value  > this->holdings_registers[reg_num].max || 
        value  < this->holdings_registers[reg_num].min)
        return -5;
    
    this->holdings_registers[reg_num].value = value;
    return 0;
}

uint16_t ModbusSlaveDevice::get_holding_reg_value (uint16_t reg_num)
{
    //проверка инициализации
    if (mdb_slave_status != 1)
        return 0;
    
    return this->holdings_registers[reg_num].value;
}

int ModbusSlaveDevice::modbus_handler()
{
    //проверка инициализации
    if (mdb_slave_status != 1)
        return -5;
    
    //проверка "внедрения зависимостей"
    if ( this->interface == NULL || this->crc == NULL )
        return -5;
    
    //проверка кол-ва приянтых байт
    int received_bytes = this->interface->get_rx_bytes();
    if ( received_bytes < 2)
        return -1;
    
    //получаем указатель на приянтый буфер
    uint8_t * rx_buffer = this->interface->get_rx_buffer();
    if (rx_buffer == NULL)
        return -5;

    //проверка алгоритма crc
    if ( this->crc->check_crc(rx_buffer, received_bytes) == CRC_ERROR )
    {
        //обнулить кол-во принятых байт
        this->interface->reload_rx_bytes();
        return -2;
    }

    //проверка адреса
    if ( rx_buffer[0] != this->id )
        return -3;
	
    //обнулить кол-во принятых байт
    this->interface->reload_rx_bytes();
	
    //получение команды
    uint16_t command = rx_buffer[1];
    
    if (command == READ_MULT_HOLDING_REG_COMMAND_MBS)
        this->read_register(HOLDING_REGISTER, rx_buffer);
    
    else if (command == READ_MULT_INPUT_REG_COMMAND_MBS)            
        this->read_register(INPUT_REGISTER, rx_buffer);
    
    else if (command == WRITE_ONE_HOLDING_REG_COMMAND_MBS)
        this->write_one_holding_reg(rx_buffer);
    
    else if (command == WRITE_MULT_HOLDING_REG_COMMAND_MBS)
        this->write_multi_holding_reg(rx_buffer);
    
    else if (command == READ_COIL_STATUS_COMMAND_MBS)
        send_error(ILLEGAL_FUNCTION_ERROR_MBS, rx_buffer);
    else if (command == READ_DISCRETE_INPUTS_COMMAND_MBS)
        send_error(ILLEGAL_FUNCTION_ERROR_MBS, rx_buffer);
    else if (command == WRITE_ONE_COIL_COMMAND_MBS)
        send_error(ILLEGAL_FUNCTION_ERROR_MBS, rx_buffer);
    else if (command == WRITE_MULT_COILS_COMMAND_MBS)
        send_error(ILLEGAL_FUNCTION_ERROR_MBS, rx_buffer);
    else if (command == WRITE_MULT_HOLDING_REG_COMMAND_MBS)
        send_error(ILLEGAL_FUNCTION_ERROR_MBS, rx_buffer);
    return 0;
}

void ModbusSlaveDevice::send_error(eERROR_CODES_t code, uint8_t * rx_buffer)
{
    uint8_t tx_buffer[10];
    // Формирование ошибки
    tx_buffer[0] = this->id;    
    tx_buffer[1] = rx_buffer[1];
    tx_buffer[2] = code;  
    
    uint16_t crc = this->crc->get_crc(tx_buffer, 3);
    tx_buffer[3] = crc >> 8;
    tx_buffer[4] = crc & 0xFF;        
    
    // Отправка
    this->interface->send_buffer(tx_buffer, 5); 
}
void ModbusSlaveDevice::read_register(eREGISTER_TYPE_t regs_type, uint8_t * rx_buffer)
{
    //стартовый регистр и кол-во регистров
    uint16_t start_reg_address = (rx_buffer[2] << 8 | rx_buffer[3]);;
    uint16_t regs_quantity = (rx_buffer[4] << 8 | rx_buffer[5]);
    
    //установка кол-ва регистров
    int registers_quantity;
    if (regs_type == INPUT_REGISTER)
        registers_quantity = this->input_regs_quantity;
    else if (regs_type == HOLDING_REGISTER)
        registers_quantity = this->hold_regs_quantity;
    
    //проверка адресов регистров
    if ((start_reg_address + regs_quantity) > registers_quantity)
    {
        this->send_error( ILLEGAL_DATA_ADDRESS_ERROR_MBS , rx_buffer);
        return;            
    }
    
    //формирование ответа
    uint8_t tx_buffer[260];
    tx_buffer[0] = this->id;
    tx_buffer[1] = rx_buffer[1];
    tx_buffer[2] = regs_quantity * 2;
    if ( regs_type == INPUT_REGISTER)
    {
        for (int i = 0; i < regs_quantity; i++)
        {
             tx_buffer[3 + (i * 2)] = this->input_registers[i + start_reg_address] >> 8;   
             tx_buffer[4 + (i * 2)] = this->input_registers[i + start_reg_address] & 0xFF;                 
        }
    }
    else if ( regs_type == HOLDING_REGISTER )
    {
        for (int i = 0; i < regs_quantity; i++)
        {
             tx_buffer[3 + (i * 2)] = this->holdings_registers[i + start_reg_address].value >> 8;   
             tx_buffer[4 + (i * 2)] = this->holdings_registers[i + start_reg_address].value & 0xFF; 
        }            
    }
    uint16_t crc = this->crc->get_crc(tx_buffer, tx_buffer[2] + 3);
    tx_buffer[tx_buffer[2] + 3] = crc >> 8;
    tx_buffer[tx_buffer[2] + 4] = crc & 0xFF; 
    this->interface->send_buffer(tx_buffer, tx_buffer[2] + 5);
}

void ModbusSlaveDevice::write_one_holding_reg(uint8_t * rx_buffer)
{
    // Адрес регистра
    uint16_t writing_address   = (rx_buffer[2] << 8 | rx_buffer[3]);
    
    // Проверка адекватности адреса регистра
    if( writing_address >= this->hold_regs_quantity )
    {
        this->send_error( ILLEGAL_DATA_ADDRESS_ERROR_MBS, rx_buffer );
        return;
    }
    
    // Проверка адекватности нового значения
    uint16_t writing_data = (rx_buffer[4] << 8 | rx_buffer[5]);
    if (writing_data > this->holdings_registers[writing_address].max  || 
        writing_data < this->holdings_registers[writing_address].min)
    {
        this->send_error( ILLEGAL_DATA_VALUE, rx_buffer );
        return;            
    }
    
    //запись в регистр
    this->holdings_registers[writing_address].value = writing_data;
    
    //формируем ответ
    uint8_t tx_buffer[10];
    tx_buffer[0] = this->id;
    tx_buffer[1] = rx_buffer[1];
    tx_buffer[2] = rx_buffer[2];
    tx_buffer[3] = rx_buffer[3];
    
    tx_buffer[4] = this->holdings_registers[writing_address].value >> 8;
    tx_buffer[5] = this->holdings_registers[writing_address].value && 0xFF;
    
    uint16_t crc = this->crc->get_crc(tx_buffer, 6);
    
    tx_buffer[6] = crc >> 8;
    tx_buffer[7] = crc & 0xFF;
    
    this->interface->send_buffer(tx_buffer, 8);
}


void ModbusSlaveDevice::write_multi_holding_reg(uint8_t * rx_buffer)
{
    //адрес регистра и кол-во
    uint16_t start_reg_address = (rx_buffer[2] << 8 | rx_buffer[3]);
    uint16_t regs_quantity = rx_buffer[4] << 8 | rx_buffer[5];
    
    //проверка адресов
    if ( (start_reg_address + regs_quantity) > this->hold_regs_quantity)
    {
        this->send_error( ILLEGAL_DATA_ADDRESS_ERROR_MBS, rx_buffer );
        return;          
    }
    //проверка данных
    for ( int i = 0; i < regs_quantity; i++)
    {
        uint16_t reg_data = (rx_buffer[7 + (i * 2)] << 8 | rx_buffer[8 + (i * 2)]);
        if ( reg_data > this->holdings_registers[i + start_reg_address].max ||
             reg_data < this->holdings_registers[i + start_reg_address].min)
        {
            this->send_error( ILLEGAL_DATA_VALUE, rx_buffer );
            return;                    
        }
    }
    //запись в регистры
    for (int i = 0; i < regs_quantity; i++)
        this->holdings_registers[i + start_reg_address].value = (rx_buffer[7 + (i * 2)] << 8 | rx_buffer[8+ (i * 2)]);
    
    //формирование ответа
    uint8_t tx_buffer[10];
    tx_buffer[0] = this->id;
    tx_buffer[1] = rx_buffer[1];
    tx_buffer[2] = rx_buffer[2];
    tx_buffer[3] = rx_buffer[3];
    tx_buffer[4] = rx_buffer[4];
    tx_buffer[5] = rx_buffer[5];
    
    uint16_t crc = this->crc->get_crc(tx_buffer, 6);
    tx_buffer[6] = crc >> 8;
    tx_buffer[7] = crc & 0xFF;
    
    this->interface->send_buffer(tx_buffer, 8);
}