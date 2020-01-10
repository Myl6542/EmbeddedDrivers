#ifndef MODBUS_SLAVE_DEVICE_H_
#define MODBUS_SLAVE_DEVICE_H_

#include "IModbusRTU_CRC.h"
#include "IModbusRTUDriver.h"
#include "ModbusDriver/ModbusDriver.h"
#include "ModbusTypes.h"

#define MAX_INPUT_REGISTERS   100
#define MAX_HOLDING_REGISTERS 100

class ModbusSlaveDevice
{
public:
    ModbusSlaveDevice(uint16_t slave_id, int input_regs, int hold_regs);
    //установить значение инпут регистра
    int set_input_reg(uint16_t reg_num, uint16_t value);
    //установить значение холдинг регистра
    int set_holding_reg(uint16_t reg_num, uint16_t value);
    //обработчик модбас
    int modbus_handler();
    //считать значение холдинг регистра
    uint16_t get_holding_reg_value (uint16_t reg_num);
    //установить драйвер
    void set_driver (IModbusRTU_Driver * drv);
    //установить алгоритм контрольной суммы
    void set_crc (IModbusRTU_CRC * c);
private:
    //низкоуровневый интерфейс передачи данных
    IModbusRTU_Driver * interface;
    //алгоритм расчета crc
    IModbusRTU_CRC * crc;
    
    //адрес слейв устройства
    uint16_t id;
    //холдинг регистры
    sHoldingRegister_t holdings_registers[MAX_HOLDING_REGISTERS];
    //кол-во холдингов
    int hold_regs_quantity;
    //инпут регистры
    uint16_t input_registers[MAX_INPUT_REGISTERS];
    //кол-во инпутов
    int input_regs_quantity;

    //состояние slave
    int mdb_slave_status;
    
    //отправить код ошибки
    void send_error(eERROR_CODES_t code, uint8_t * rx_buffer);
    //считать регистр( отправить мастеру значение регистра )
    void read_register(eREGISTER_TYPE_t type, uint8_t * rx_buffer);
    //записать в регистр ( команда от мастера  )
    void write_one_holding_reg(uint8_t * rx_buffer);
    //записать в несколько регистров ( команда от мастера  )
    void write_multi_holding_reg(uint8_t * rx_buffer);
};


#endif