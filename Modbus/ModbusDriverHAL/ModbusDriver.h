#ifndef MODBUS_DRIVER_H_
#define MODBUS_DRIVER_H_

#include "../Modbus/IModbusRTUDriver.h"
#include "USART_RS485_HAL.h"


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
    
    ModbusDriver(UsartRS485_t * u);

    
private:
    UsartRS485_t * usart_handle;
};



#endif
