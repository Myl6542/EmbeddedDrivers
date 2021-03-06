#ifndef IMODBUS_RTU_CRC_H_
#define IMODBUS_RTU_CRC_H_

#include "stdint.h"

typedef enum 
{
    CRC_ERROR = 0,
    CRC_OK = 1,
}CRC_RESULT_t;
class IModbusRTU_CRC
{
public:
    //==============================================================================
    //                          �������� CRC16     
    //------------------------------------------------------------------------------
    // buffer           - �������� �����
    // buffer_size     - ������ ������
    // \return          1 - CRC �����
    //==============================================================================
    virtual CRC_RESULT_t check_crc( uint8_t * buffer, int buffer_size ) = 0;
    //==============================================================================
    //                          ������ CRC16     
    //------------------------------------------------------------------------------
    // buffer           - �������� �����
    // buffer_size     - ������ �������
    // \return          - ����������� CRC
    //==============================================================================
    virtual uint16_t get_crc( uint8_t * buffer, int buffer_size ) = 0;
};



#endif