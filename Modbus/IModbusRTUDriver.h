#ifndef IMODBUS_RTU_DRIVER_H_
#define IMODBUS_RTU_DRIVER_H_

#include "stdint.h"

#define  CPP_DRIVER

//интерфейс для "C++"
#ifdef CPP_DRIVER
//низкоуровневая реализация интерфейса, которую "заявляет" ModbusRTU для работы
class IModbusRTU_Driver
{
public:
    //отправить буфер с данными
    virtual int send_buffer(uint8_t * buffer, uint32_t buff_size) = 0;

    //возвращает кол-во принятых байт
    virtual int get_rx_bytes() = 0;

    //возвращает указатель на буфер принятых данных
    virtual uint8_t * get_rx_buffer( ) = 0;

    //обнулить кол-во принятых байт
    virtual void reload_rx_bytes() = 0;
};

#endif



//интерфейс для "C"
#ifdef C_DRIVER
typedef struct
{
    //отправить буфер с данными
    int (*send_buffer)(uint8_t * buffer, uint32_t buff_size);
    
    //возвращает кол-во принятых байт
    int (*get_rx_bytes)();
    
    //возвращает указатель на буфер принятых данных
    uint8_t * (*get_rx_buffer)( );
    
    //обнулить кол-во принятых байт
    void (*reload_rx_bytes)();    
}IModbusRTU_Driver_t;
#endif


#endif