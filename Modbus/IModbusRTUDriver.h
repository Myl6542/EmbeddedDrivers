#ifndef IMODBUS_RTU_DRIVER_H_
#define IMODBUS_RTU_DRIVER_H_

#include "stdint.h"

#define  CPP_DRIVER

//��������� ��� "C++"
#ifdef CPP_DRIVER
//�������������� ���������� ����������, ������� "��������" ModbusRTU ��� ������
class IModbusRTU_Driver
{
public:
    //��������� ����� � �������
    virtual int send_buffer(uint8_t * buffer, uint32_t buff_size) = 0;

    //���������� ���-�� �������� ����
    virtual int get_rx_bytes() = 0;

    //���������� ��������� �� ����� �������� ������
    virtual uint8_t * get_rx_buffer( ) = 0;

    //�������� ���-�� �������� ����
    virtual void reload_rx_bytes() = 0;
};

#endif



//��������� ��� "C"
#ifdef C_DRIVER
typedef struct
{
    //��������� ����� � �������
    int (*send_buffer)(uint8_t * buffer, uint32_t buff_size);
    
    //���������� ���-�� �������� ����
    int (*get_rx_bytes)();
    
    //���������� ��������� �� ����� �������� ������
    uint8_t * (*get_rx_buffer)( );
    
    //�������� ���-�� �������� ����
    void (*reload_rx_bytes)();    
}IModbusRTU_Driver_t;
#endif


#endif