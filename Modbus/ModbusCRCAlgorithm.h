#ifndef MODBUS_CRC_ALGORITHM_H_
#define MODBUS_CRC_ALGORITHM_H_

#include "stdint.h"

#include "IModbusRTU_CRC.h"

class ModbusCRC16: public IModbusRTU_CRC
{
public:
    ModbusCRC16();
    CRC_RESULT_t check_crc( uint8_t * buffer, int buffer_size );
    uint16_t get_crc( uint8_t * buffer, int buffer_size );  
};

#endif