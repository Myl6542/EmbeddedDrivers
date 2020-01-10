#include "ModbusMasterDevice.h"
#include "ModbusMaster/ModbusMaster.h"


ModbusMasterDevice::ModbusMasterDevice(uint32_t * _msec_tim)
{
    this->_msec_timer = _msec_tim;
}

void ModbusMasterDevice::set_driver (IModbusRTU_Driver * drv)
{
    this->interface = drv;
}

void ModbusMasterDevice::set_crc (IModbusRTU_CRC * c)
{
    this->crc = c;
}

int ModbusMasterDevice::write_hold_registers( uint16_t slave_id,
                                            uint16_t reg_addr,
                                            uint16_t reg_quantity,
                                            uint16_t * write_buffer,
                                            int wait_time)
{
    eMODBUS_RESULT_t ret = MODBUS_ERROR;
    
    uint8_t tx_buffer[100];
    uint16_t byteNumber = 0;
    tx_buffer[byteNumber++] = slave_id;
    tx_buffer[byteNumber++] = WRITE_MULT_HOLDING_REG_COMMAND_MBS;
    tx_buffer[byteNumber++] = reg_addr >> 8;
    tx_buffer[byteNumber++] = reg_addr & 0xFF;
    tx_buffer[byteNumber++] = reg_quantity >> 8;
    tx_buffer[byteNumber++] = reg_quantity & 0xFF;
    tx_buffer[byteNumber++] = reg_quantity * 2;
    
    for(uint8_t i = 0; i < reg_quantity; i++)
    {
        tx_buffer[byteNumber++] = write_buffer[i] >> 8;
        tx_buffer[byteNumber++] = write_buffer[i] & 0xFF;
    }
    
    uint16_t crc = this->crc->get_crc(tx_buffer, byteNumber);
 
    tx_buffer[byteNumber++] = crc >> 8;
    tx_buffer[byteNumber++] = crc & 0xFF;  
    
    this->interface->send_buffer(tx_buffer,byteNumber);
    
    static uint32_t usart_timer_flag  = 0;
    usart_timer_flag = *_msec_timer;
    while( (this->interface->get_rx_bytes() == 0) &&
           ((*_msec_timer - usart_timer_flag) < wait_time) ); 
    
    
    uint32_t rx_bytes = this->interface->get_rx_bytes();
    if(rx_bytes < 2)
        return ret;

    uint8_t * rx_buffer = this->interface->get_rx_buffer();
    if (this->crc->check_crc(rx_buffer, rx_bytes) != CRC_OK)
    {
        this->interface->reload_rx_bytes();
        return ret;
    }
    this->interface->reload_rx_bytes();

    if((rx_buffer[0] == slave_id) && (rx_buffer[1] == WRITE_MULT_HOLDING_REG_COMMAND_MBS))
    {
        ret = MODBUS_OK;
    }
    return ret;
 
}

int ModbusMasterDevice::write_hold_register(  uint16_t slave_id,
                                              uint16_t reg_addr,
                                              uint16_t reg_value,
                                              int wait_time)
{
    
}

int ModbusMasterDevice::read_hold_registers(uint16_t slave_id,
                              uint16_t reg_addr,
                              uint16_t reg_quantity,
                              uint16_t * buffer,
                              int wait_time)
{
    eMODBUS_RESULT_t ret = MODBUS_ERROR;
    uint16_t byteNumber = 0;
    uint8_t tx_buffer[10];
    
    tx_buffer[byteNumber++] = slave_id;
    tx_buffer[byteNumber++] = READ_MULT_HOLDING_REG_COMMAND_MBS;
    tx_buffer[byteNumber++] = reg_addr >> 8;
    tx_buffer[byteNumber++] = reg_addr & 0xFF;
    tx_buffer[byteNumber++] = reg_quantity >> 8;
    tx_buffer[byteNumber++] = reg_quantity & 0xFF; 
    
    uint16_t crc = this->crc->get_crc(tx_buffer, byteNumber);
    
    tx_buffer[byteNumber++] = crc >> 8;
    tx_buffer[byteNumber++] = crc & 0xFF; 
    
    this->interface->send_buffer(tx_buffer, byteNumber);
    
    this->interface->reload_rx_bytes();

    //ожидание таймаута
    static uint32_t usart_timer_flag  = 0;
    usart_timer_flag = *_msec_timer;
    while( (this->interface->get_rx_bytes() == 0) &&
          ((*_msec_timer - usart_timer_flag) < wait_time)); 

    //проверка кол-ва принятых байт
    if(this->interface->get_rx_bytes() < 2)
        return ret;
        
    uint8_t * rx_buffer = this->interface->get_rx_buffer();
    uint32_t rx_bytes = this->interface->get_rx_bytes();
    //проверка CRC
    if (this->crc->check_crc(rx_buffer, rx_bytes) != CRC_OK )
    {
        this->interface->reload_rx_bytes();
        return ret;
    }
    this->interface->reload_rx_bytes();
    
    //проверка ID проверка команды
    if((rx_buffer[0] != slave_id) || (rx_buffer[1] != READ_MULT_HOLDING_REG_COMMAND_MBS))
        return ret;
    
    ret = MODBUS_OK;
    uint16_t regNumber = 0;
    uint16_t byteNum = 3;
    while(regNumber < reg_quantity)
    {
        buffer[regNumber] = ((uint16_t)(rx_buffer[byteNum++])) << 8; 
        buffer[regNumber++] |= rx_buffer[byteNum++];
    }
    return ret;
}
    
int ModbusMasterDevice::read_input_registers(uint16_t slave_id,
                                            uint16_t reg_addr,
                                            uint16_t reg_quantity,
                                            uint16_t * buffer,
                                            int wait_time)
{
    eMODBUS_RESULT_t ret = MODBUS_ERROR;
    uint16_t byteNumber = 0;
    uint8_t tx_buffer[10];
    
    tx_buffer[byteNumber++] = slave_id;
    tx_buffer[byteNumber++] = READ_MULT_INPUT_REG_COMMAND_MBS;
    tx_buffer[byteNumber++] = reg_addr >> 8;
    tx_buffer[byteNumber++] = reg_addr & 0xFF;
    tx_buffer[byteNumber++] = reg_quantity >> 8;
    tx_buffer[byteNumber++] = reg_quantity & 0xFF; 
    
    uint16_t crc = this->crc->get_crc(tx_buffer, byteNumber);
    
    tx_buffer[byteNumber++] = crc >> 8;
    tx_buffer[byteNumber++] = crc & 0xFF; 
    
    this->interface->send_buffer(tx_buffer, byteNumber);
    
    this->interface->reload_rx_bytes();

    //ожидание ответа от ведомого
    static uint32_t usart_timer_flag  = 0;
    usart_timer_flag = *_msec_timer;
    while( (this->interface->get_rx_bytes() == 0) &&
          ((*_msec_timer - usart_timer_flag) < wait_time)); 
    
    //проверка кол-во принятых байт
    int rx_bytes = this->interface->get_rx_bytes();
    int expected_bytes = reg_quantity * 2 + 5;
    if ( (rx_bytes < 2) || (rx_bytes != expected_bytes) )
        return ret;
    
    //получение буфера принятых байт
    uint8_t * rx_buffer = this->interface->get_rx_buffer();
    //проверка контрольной суммы
    if (this->crc->check_crc(rx_buffer, rx_bytes) != CRC_OK )
    {
        this->interface->reload_rx_bytes();
        return ret;
    }
    //обнулить кол-во принятых байт
    this->interface->reload_rx_bytes();
    //проверка принятой команды
    if((rx_buffer[0] != slave_id) || (rx_buffer[1] != READ_MULT_INPUT_REG_COMMAND_MBS))
        return ret;
    
    ret = MODBUS_OK;
    uint16_t regNumber = 0;
    uint16_t byteNum = 3;
    //установка принятых данных
    while(regNumber < reg_quantity)
    {
        buffer[regNumber] = ((uint16_t)(rx_buffer[byteNum++])) << 8; 
        buffer[regNumber++] |= rx_buffer[byteNum++];
    }
    return ret;
}
