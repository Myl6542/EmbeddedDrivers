#ifndef MODBUS_MASTER_DEVICE_H_
#define MODBUS_MASTER_DEVICE_H_

#include "stdint.h"

#include "IModbusRTU_CRC.h"
#include "IModbusRTUDriver.h"
#include "ModbusTypes.h"


class ModbusMasterDevice
{
public:
    ModbusMasterDevice(uint32_t * _msec_tim);

    int read_hold_registers(  uint16_t slave_id,
                              uint16_t reg_addr,
                              uint16_t reg_quantity,
                              uint16_t * buffer,
                              int wait_time);
    
    int read_input_registers( uint16_t slave_id,
                              uint16_t reg_addr,
                              uint16_t reg_quantity,
                              uint16_t * buffer,
                              int wait_time);
    
    int write_hold_registers( uint16_t slave_id,
                              uint16_t reg_addr,
                              uint16_t reg_quantity,
                              uint16_t * write_buffer,
                              int wait_time);
    
    int write_hold_register(  uint16_t slave_id,
                              uint16_t reg_addr,
                              uint16_t reg_value,
                              int wait_time);
    
    void set_driver (IModbusRTU_Driver * drv);
    void set_crc (IModbusRTU_CRC * c);
private:
    IModbusRTU_CRC * crc;
    IModbusRTU_Driver * interface;
    
    uint32_t *_msec_timer;
};



#endif