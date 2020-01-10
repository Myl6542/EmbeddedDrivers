//******************************************************************************
// Имя файла    :  'USART.h'
// заголовок    :  Драйвер интерфейса USART (F4)
// Автор        :  Маньянов Р.Р.
// Контакты     :  manianov.rus@gmail.com
// Дата         :  30.04.2015
//******************************************************************************

#ifndef __USART_H
#define __USART_H

#include "GPIO/GPIO.h"
#include "DMA/DMA.h"

//==============================================================================
//                      Структуры и типы
//==============================================================================

    // интерфейс USART
    typedef struct USART
    {            
        USART_TypeDef*          number;                 // номер уарта
        uint32_t                rcc;                    // источник тактирования USART 
        USART_InitTypeDef       definitions;            // настройки
        uint8_t                 IRQn;                   // вектор прерывания    
        
        sGpio*                  txGpio;                 // пин TX
        sGpio*                  rxGpio;                 // пин RX
        sGpio*                  reGpio;                 // пин RE
        sGpio*                  deGpio;                 // пин DE   

        uint32_t                txBufferSize;           // размер буфера TX
        uint32_t                rxBufferSize;           // размер буфера RX
        
        uint8_t*                txBuffer;               // буфер TX
        uint8_t*                rxBuffer;               // буфер RX
           
        sDma*                   txDma;                  // DMA отправки
        sDma*                   rxDma;                  // DMA приёма
    
        void                    (*RxMessageHandler)();  // внешний обработчик прерывания приёма пакета
        
        uint16_t                txByteCount;            // кол-во отправляемых байт
        uint16_t                rxByteCount;            // кол-во принятых байт
    } sUsart;
    
//==============================================================================
//                      Прототипы функций
//==============================================================================

    // Инициализация интерфейса
    void USARTInit (sUsart* usart);

    // Отправка данных
    void USARTSendData(uint16_t txLenght, sUsart* usart);
    
#endif // __USART_H