#include "ModbusDriver.h"
#include "main.h"



ModbusDriver::ModbusDriver(UsartRS485_t * u)
{
    this->usart_handle = u;
}


//отправить буфер с данными
int ModbusDriver::send_buffer(uint8_t * buffer, uint32_t buff_size)
{
    Usart_RS485_Send(usart_handle, buffer, buff_size);
}
//возвращает кол-во принятых байт
int ModbusDriver::get_rx_bytes()
{
    return usart_handle->rx_package_size;
}
//возвращает указатель на буфер принятых данных
uint8_t * ModbusDriver::get_rx_buffer( )
{
    return usart_handle->huart->pRxBuffPtr;
}
//обнулить кол-во принятых байт
void ModbusDriver::reload_rx_bytes()
{
    usart_handle->rx_package_size = 0;
}