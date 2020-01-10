#ifndef MODBUS_DRIVER_H_
#define MODBUS_DRIVER_H_

#include "IModbusRTUDriver.h"
#include "USART/USART.h"

class ModbusDriver: public IModbusRTU_Driver
{
public:
    //��������� ����� � �������
    int send_buffer(uint8_t * buffer, uint32_t buff_size);//override
    //���������� ���-�� �������� ����
    int get_rx_bytes();//override
    //���������� ��������� �� ����� �������� ������
    uint8_t * get_rx_buffer( );//override
    //�������� ���-�� �������� ����
    void reload_rx_bytes();//override
    
    ModbusDriver();
    void init(sUsart * u);
    
private:
    sUsart * usart;
};



#endif
