//******************************************************************************
// Имя файла    :  'USART.c'
// заголовок    :  Драйвер интерфейса USART (F4)
// Автор        :  Маньянов Р.Р.
// Контакты     :  manianov.rus@gmail.com
// Дата         :  30.04.2015
//******************************************************************************

#include "USART.h"
#include "Settings\Settings.h"

//==============================================================================
//                      Константы и макросы
//==============================================================================

    // использование USART1
    //#define USE_USART1  

    // использование USART2
    #define USE_USART2 

    // использование USART3
    //#define USE_USART3 

    // использование USART4
    //#define USE_USART4 

    // использование USART5
    //#define USE_USART5

    // использование USART6
    //#define USE_USART6 

    // Размер приёмного буфера USART1
    #define USART1_RX_BUFFER_SIZE    50

    // Размер отправного буфера USART1
    #define USART1_TX_BUFFER_SIZE    50

    // Размер приёмного буфера USART2
    #define USART2_RX_BUFFER_SIZE    550

    // Размер отправного буфера USART2
    #define USART2_TX_BUFFER_SIZE    100

    // Размер приёмного буфера USART3
    #define USART3_RX_BUFFER_SIZE    250

    // Размер отправного буфера USART3
    #define USART3_TX_BUFFER_SIZE    250

    // Размер приёмного буфера USART4
    #define USART4_RX_BUFFER_SIZE    100

    // Размер отправного буфера USART4
    #define USART4_TX_BUFFER_SIZE    100

    // Размер приёмного буфера USART4
    #define USART5_RX_BUFFER_SIZE    100

    // Размер отправного буфера USART4
    #define USART5_TX_BUFFER_SIZE    100

//==============================================================================
//                      Глобальные переменные
//==============================================================================

    // внешне определенные переменные 
    extern uint32_t globalTimer;
    extern sGpio gpioUsart2Tx;
    extern sGpio gpioUsart2Rx;
    extern sGpio gpioUsart2De;
    extern sGpio gpioUsart2Re;
    //extern sDma  dmaUsart2Tx;
    extern sDma  dmaUsart2Rx;
    
#ifdef USE_USART1

    // буфер отправки USART1
    uint8_t usart1TxBuffer[USART1_TX_BUFFER_SIZE];
    
    // буфер приёма USART1
    uint8_t usart1RxBuffer[USART1_RX_BUFFER_SIZE];

    // USART1
    sUsart usart1 = 
    {
        USART1,                // номер уарта     
        
        RCC_APB2Periph_USART1, // источник тактирования USART     
        {
            38400,                     
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Rx | USART_Mode_Tx,
            USART_HardwareFlowControl_None
        },
        
        USART1_IRQn,            // глобальное прерывание
        
        &gpioUsart1Tx,          // пин TX 
        &gpioUsart1Rx,          // пин RX 
        &gpioUsart1Re,          // пин RE 
        0,                      // пин DE 
        
        USART1_TX_BUFFER_SIZE,  // размер буфера TX
        USART1_RX_BUFFER_SIZE,  // размер буфера RX
        
        usart1TxBuffer,         // буфер TX
        usart1RxBuffer,         // буфер RX
        
        &dmaUsart1Tx,
        &dmaUsart1Rx,
        
        
    };
    
#endif //USE_USART1

#ifdef USE_USART2

   // буфер отправки USART2
    uint8_t usart2TxBuffer[USART2_TX_BUFFER_SIZE];
    
    // буфер приёма USART2
    uint8_t usart2RxBuffer[USART2_RX_BUFFER_SIZE];

    // USART2
    sUsart usart2 = 
    {
        USART2,                // номер уарта     
        
        RCC_APB1Periph_USART2, // источник тактирования USART     
        {
            19200,                     
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Rx | USART_Mode_Tx,
            USART_HardwareFlowControl_None
        },
        
        USART2_IRQn,            // глобальное прерывание
        
        &gpioUsart2Tx,          // пин TX 
        &gpioUsart2Rx,          // пин RX 
        &gpioUsart2Re,          // пин RE 
        &gpioUsart2De,          // пин DE 
        
        USART2_TX_BUFFER_SIZE,  // размер буфера TX
        USART2_RX_BUFFER_SIZE,  // размер буфера RX
        
        usart2TxBuffer,         // буфер TX
        usart2RxBuffer,         // буфер RX
        
        0,
        &dmaUsart2Rx,
        
        &SettingsPollPrivateParameter,  // внешний обработчик приёма сообщения
    };
    
#endif //USE_USART2

#ifdef USE_USART3

   // буфер отправки USART3
    uint8_t usart3TxBuffer[USART3_TX_BUFFER_SIZE];
    
    // буфер приёма USART3
    uint8_t usart3RxBuffer[USART3_RX_BUFFER_SIZE];

    // USART3
    sUsart usart3 = 
    {
        USART3,                 // номер уарта     
        
        RCC_APB1Periph_USART3,  // источник тактирования USART     
        {
            115200,                     
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Rx | USART_Mode_Tx,
            USART_HardwareFlowControl_None
        },
        
        USART3_IRQn,            // глобальное прерывание
        
        &gpioUsart3Tx,          // пин TX 
        &gpioUsart3Rx,          // пин RX 
        0,                      // пин RE 
        0,                      // пин DE 
        
        USART3_TX_BUFFER_SIZE,  // размер буфера TX
        USART3_RX_BUFFER_SIZE,  // размер буфера RX
        
        usart3TxBuffer,         // буфер TX
        usart3RxBuffer,         // буфер RX
    };
    
#endif //USE_USART3

#ifdef USE_USART4
    
    // буфер отправки USART4
    uint8_t usart4TxBuffer[USART4_TX_BUFFER_SIZE];
    
    // буфер приёма USART4
    uint8_t usart4RxBuffer[USART4_RX_BUFFER_SIZE];

    // USART4
    sUsart usart4 = 
    {
        UART4,                 // номер уарта     
        
        RCC_APB1Periph_UART4,  // источник тактирования USART     
        {
            19200,                     
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Rx | USART_Mode_Tx,
            USART_HardwareFlowControl_None
        },
        
        UART4_IRQn,             // глобальное прерывание
        
        &gpioUsart4Tx,          // пин TX 
        &gpioUsart4Rx,          // пин RX 
        0,                      // пин RE 
        &gpioUsart4De,          // пин DE 
        
        USART4_TX_BUFFER_SIZE,  // размер буфера TX
        USART4_RX_BUFFER_SIZE,  // размер буфера RX
        
        usart4TxBuffer,         // буфер TX
        usart4RxBuffer,         // буфер RX
        
        &dmaUsart4Tx,
        &dmaUsart4Rx,
        
        &SettingsPollPrivateParameter,  // внешний обработчик приёма сообщения
    };
    
#endif //USE_USART4
    
#ifdef USE_USART5

    // буфер отправки USART5
    uint8_t usart5TxBuffer[USART4_TX_BUFFER_SIZE];
    
    // буфер приёма USART5
    uint8_t usart5RxBuffer[USART4_RX_BUFFER_SIZE];

    // USART5
    sUsart usart5 = 
    {
        UART5,                  // номер уарта     
        
        RCC_APB1Periph_UART5,   // источник тактирования USART     
        {
            115200,                     
            USART_WordLength_8b,
            USART_StopBits_1,
            USART_Parity_No,
            USART_Mode_Rx | USART_Mode_Tx,
            USART_HardwareFlowControl_None
        },
        
        UART5_IRQn,             // глобальное прерывание
        
        &gpioUsart5Tx,          // пин TX 
        &gpioUsart5Rx,          // пин RX 
        0,                      // пин RE 
        0,                      // пин DE 
        
        USART5_TX_BUFFER_SIZE,  // размер буфера TX
        USART4_RX_BUFFER_SIZE,  // размер буфера RX
        
        usart5TxBuffer,         // буфер TX
        usart5RxBuffer,         // буфер RX
    };
    
#endif //USE_USART5

//==============================================================================
//                           Прототипы функций
//==============================================================================

    // Инициализация DMA интерфейса 
    void USARTInitDma (sUsart* usart);

    // Общий обработчик прерываний для всех интерфейсов
    void USART_IRQHandler(uint8_t* txByteNumber, uint8_t* rxByteCount, sUsart* usart);

//==============================================================================
//                      Инициализация интерфейса 
//------------------------------------------------------------------------------
//  usart       - USART интерфейс
//==============================================================================

void USARTInit (sUsart* usart)
{  
    // Инициализация пинов
    GPIOInit(usart->txGpio);
    GPIOInit(usart->rxGpio);
    GPIOInit(usart->reGpio);
    GPIOInit(usart->deGpio);
    
    // Тактирование USART
    if(usart->number == USART1
#ifdef USE_USART6
        || usart->number == USART6
#endif    
       )    
        RCC_APB2PeriphClockCmd (usart->rcc, ENABLE);
    else
        RCC_APB1PeriphClockCmd (usart->rcc, ENABLE);
        
    // Конфигурирование USART   
    USART_Init(usart->number, &usart->definitions); 
    
    // Включение USART    
    USART_Cmd(usart->number, ENABLE); 
    
    //Инициализация глобального прерываения USART
    if(usart->txDma)    
        USART_ITConfig(usart->number, USART_IT_TC, ENABLE);
    if(!usart->txDma)    
        USART_ITConfig(usart->number, USART_IT_RXNE, ENABLE); 
   
    USART_ITConfig(usart->number, USART_IT_IDLE, ENABLE); 
    
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel                      = usart->IRQn; 
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority    = 0; 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority           = 0;
    NVIC_InitStruct.NVIC_IRQChannelCmd                   = ENABLE; 
    NVIC_Init(&NVIC_InitStruct);     
        
    // Инициализация DMA
    DMAInit((uint32_t)usart->txBuffer, usart->txBufferSize, usart->txDma);
    USART_DMACmd(usart->number, USART_DMAReq_Tx, ENABLE);  
    DMAInit((uint32_t)usart->rxBuffer, usart->rxBufferSize, usart->rxDma);
    DMA_Cmd(usart->rxDma->channel, ENABLE); 
    USART_DMACmd(usart->number, USART_DMAReq_Rx, ENABLE); 
}

//==============================================================================
//                      Отправка данных 
//------------------------------------------------------------------------------
//  txData      - кол-во отправляемых данных
//  usart       - USART интерфейс
//==============================================================================

void USARTSendData (uint16_t txLenght, sUsart* usart)
{ 
    while(!USART_GetFlagStatus(usart->number, USART_FLAG_TXE));
    
    // Преобразователь уровня на отправку       
    GPIOSet(usart->deGpio);  
    GPIOSet(usart->reGpio);    
    
    if(usart->txDma)
    {
        // Задание длины отправляемого пакета
        DMA_SetCurrDataCounter(usart->txDma->channel, txLenght);         
        // Запуск отправки       
        DMA_Cmd(usart->txDma->channel, ENABLE);
    }
    else
    {
        usart->txByteCount = txLenght;
        USART_ITConfig(usart->number, USART_IT_TXE, ENABLE); 
    }
}

#ifdef __cplusplus
 extern "C" {
#endif
     
//==============================================================================
//                      Обработчик прерывания USART 1 
//==============================================================================

#ifdef USE_USART1
void USART1_IRQHandler (void)
{
    static uint8_t txByteNumber;
    static uint8_t rxByteCount;
    USART_IRQHandler(&txByteNumber, &rxByteCount, &usart1);
}
#endif // USE_USART1

//==============================================================================
//                      Обработчик прерывания USART 2 
//==============================================================================

#ifdef USE_USART2
void USART2_IRQHandler (void)
{
    static uint8_t txByteNumber;
    static uint8_t rxByteCount;
    USART_IRQHandler(&txByteNumber, &rxByteCount, &usart2);
}
#endif // USE_USART2

//==============================================================================
//                      Обработчик прерывания USART 3 
//==============================================================================

#ifdef USE_USART3
void USART3_IRQHandler (void)
{
    static uint8_t txByteNumber;
    static uint8_t rxByteCount;
    USART_IRQHandler(&txByteNumber, &rxByteCount, &usart3);
}
#endif // USE_USART3

//==============================================================================
//                      Обработчик прерывания UART 4 
//==============================================================================

#ifdef USE_USART4
void UART4_IRQHandler (void)
{
    static uint8_t txByteNumber;
    static uint8_t rxByteCount;
    USART_IRQHandler(&txByteNumber, &rxByteCount, &usart4);
}
#endif // USE_USART4
     
//==============================================================================
//                      Обработчик прерывания UART 4 
//==============================================================================

#ifdef USE_USART5
void UART5_IRQHandler (void)
{
    static uint8_t txByteNumber;
    static uint8_t rxByteCount;
    USART_IRQHandler(&txByteNumber, &rxByteCount, &usart5);
}
#endif // USE_USART5

#ifdef __cplusplus
 } //extern "C"
#endif

//==============================================================================
//                      Общий обработчик для всех интерфейсов 
//------------------------------------------------------------------------------
//  txByteNumber    - номер отправляемого байта в пакете
//  rxByteCount     - номер принемаемого байта в пакете
//  usart           - USART интерфейс
//==============================================================================

void USART_IRQHandler(uint8_t* txByteNumber, uint8_t* rxByteCount, sUsart* usart)
{
    // Отправлен байт (без использования ДМА TX)
    if(USART_GetFlagStatus(usart->number, USART_FLAG_TXE) && !usart->txDma)
    {  
        if(usart->txByteCount)
        {        
            usart->txByteCount--;
            USART_SendData(usart->number, usart->txBuffer[(*txByteNumber)++]); 
        }
        else
        {                   
            USART_ITConfig(usart->number, USART_IT_TXE, DISABLE);    
            while(!USART_GetFlagStatus(usart->number, USART_FLAG_TC)); 
            
            GPIOReset(usart->deGpio);  
            GPIOReset(usart->reGpio);   
            *txByteNumber = 0;
        }
    }
    
    // Отправка окончена (при использовании ДМА TX)
    if(USART_GetFlagStatus(usart->number, USART_FLAG_TC) && usart->txDma)
    {
        USART_ClearFlag(usart->number, USART_FLAG_TC);        
        // Отключение DMA отправки
        DMA_Cmd(usart->txDma->channel, DISABLE);          
        
        // Преобразователь уровня на приём
        GPIOReset(usart->deGpio);  
        GPIOReset(usart->reGpio);   
    }
    
    // Принят байт (без использования ДМА RX)
    if(USART_GetFlagStatus(usart->number, USART_IT_RXNE)  && !usart->rxDma)
    {
        USART_ClearFlag(usart->number, USART_IT_RXNE);   
        usart->txBuffer[(*rxByteCount)++] = USART_ReceiveData(usart->number);         
    }  
    
    // Принят пакет
    if(USART_GetFlagStatus(usart->number, USART_FLAG_IDLE))
    {
        USART_ReceiveData(usart->number);
        USART_ClearFlag(usart->number, USART_FLAG_IDLE);    
        // без использования ДМА RX
        if(!usart->rxDma)    
        {  
            usart->rxByteCount = *rxByteCount;  
            *rxByteCount = 0;
            if(usart->RxMessageHandler)
                usart->RxMessageHandler(usart);
        }
        // при использовании ДМА RX
        else
        {     
            usart->rxByteCount = usart->rxDma->definitions.DMA_BufferSize - DMA_GetCurrDataCounter(usart->rxDma->channel); 
            if(usart->RxMessageHandler)
                usart->RxMessageHandler(usart);
           
             // Сброс приёмного DMA             
            DMA_Cmd(usart->rxDma->channel, DISABLE);
            DMA_SetCurrDataCounter(usart->rxDma->channel, usart->rxDma->definitions.DMA_BufferSize); 
            DMA_Cmd(usart->rxDma->channel, ENABLE);
        }
    }
}


