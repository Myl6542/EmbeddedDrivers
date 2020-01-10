#include "ModbusDriver.h"
#include "main.h"



ModbusDriver::ModbusDriver(UsartRS485_t * u)
{
    this->usart_handle = u;
}


//��������� ����� � �������
int ModbusDriver::send_buffer(uint8_t * buffer, uint32_t buff_size)
{
    Usart_RS485_Send(usart_handle, buffer, buff_size);
}
//���������� ���-�� �������� ����
int ModbusDriver::get_rx_bytes()
{
    return usart_handle->rx_package_size;
}
//���������� ��������� �� ����� �������� ������
uint8_t * ModbusDriver::get_rx_buffer( )
{
    return usart_handle->huart->pRxBuffPtr;
}
//�������� ���-�� �������� ����
void ModbusDriver::reload_rx_bytes()
{
    usart_handle->rx_package_size = 0;
}