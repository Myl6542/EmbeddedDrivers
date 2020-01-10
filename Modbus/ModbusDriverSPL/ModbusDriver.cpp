#include "ModbusDriver.h"

ModbusDriver::ModbusDriver()
{
    
}

void ModbusDriver::init(sUsart * u)
{
    USARTInit(u);
    this->usart = u;
}
//��������� ����� � �������
int ModbusDriver::send_buffer(uint8_t * buffer, uint32_t buff_size)
{
    for (int i = 0; i < buff_size; i++)
    {
        this->usart->txBuffer[i] = buffer[i];
    }
    USARTSendData(buff_size, this->usart);
    return 0;
}
//���������� ���-�� �������� ����
int ModbusDriver::get_rx_bytes()
{
    return ((int)(this->usart->rxByteCount));
}
//���������� ��������� �� ����� �������� ������
uint8_t * ModbusDriver::get_rx_buffer( )
{
    return (this->usart->rxBuffer);
}
//�������� ���-�� �������� ����
void ModbusDriver::reload_rx_bytes()
{
    this->usart->rxByteCount = 0;
}