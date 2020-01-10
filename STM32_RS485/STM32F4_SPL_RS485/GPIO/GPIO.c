//******************************************************************************
// Имя файла    :  'GPIO.c'
// заголовок    :  Драйвер портов ввода-вывода (F4)
// Автор        :  Маньянов Р.Р.
// Контакты     :  manianov.rus@gmail.com
// Дата         :  25.07.2015
//******************************************************************************

#include "GPIO.h"

//==============================================================================
//                  Глобальные переменные
//==============================================================================
    // пин RX линии USART3
    sGpio gpioUsart3Rx = 
    {
        GPIOB,     
        RCC_AHB1Periph_GPIOB, 
        {
            GPIO_Pin_11,   
            GPIO_Mode_AF,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource11,
        GPIO_AF_USART3,        
    };

    // пин TX линии USART3
    sGpio gpioUsart3Tx = 
    {
        GPIOB,     
        RCC_AHB1Periph_GPIOB, 
        {
            GPIO_Pin_10,   
            GPIO_Mode_AF,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource10,
        GPIO_AF_USART3,        
    };
    
    // пин RE линии USART3
    sGpio gpioUsart3Re = 
    {
        GPIOE,     
        RCC_AHB1Periph_GPIOE, 
        {
            GPIO_Pin_15,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource15,
        0,        
    };
    // пин DE линии USART3
    sGpio gpioUsart3De = 
    {
        GPIOE,     
        RCC_AHB1Periph_GPIOE, 
        {
            GPIO_Pin_14,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource14,
        0,        
    };    
    
    
      // пин RX линии USART4
    sGpio gpioUsart4Rx = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_1,   
            GPIO_Mode_AF,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource1,
        GPIO_AF_UART4,        
    };

    // пин TX линии USART4
    sGpio gpioUsart4Tx = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_0,   
            GPIO_Mode_AF,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource0,
        GPIO_AF_UART4,        
    };
    
    // пин RE линии USART4
    sGpio gpioUsart4Re = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_2,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource2,
        0,        
    };
    // пин RE линии USART4
    sGpio gpioUsart4De = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_3,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource3,
        0,        
    };    
    
    
    













    // пин RX линии USART1
    sGpio gpioUsart1Rx = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_10,   
            GPIO_Mode_AF,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource10,
        GPIO_AF_USART1,        
    };

    // пин TX линии USART1
    sGpio gpioUsart1Tx = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_9,   
            GPIO_Mode_AF,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource9,
        GPIO_AF_USART1,        
    };
    
    // пин RE линии USART1
    sGpio gpioUsart1Re = 
    {
        GPIOC,     
        RCC_AHB1Periph_GPIOC, 
        {
            GPIO_Pin_8,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource8,
        0,        
    };

    
    sGpio gpioLedWork = 
    {
        GPIOE,     
        RCC_AHB1Periph_GPIOE, 
        {
            GPIO_Pin_4,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource3,
        0,        
    };
    
    sGpio gpioLedConnect = 
    {
        GPIOE,     
        RCC_AHB1Periph_GPIOE, 
        {
            GPIO_Pin_3,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource0,
        0,        
    };

    
    
    
    sGpio gpioUsart6Tx = 
    {
        GPIOC,     
        RCC_AHB1Periph_GPIOC, 
        {
            GPIO_Pin_6,   
            GPIO_Mode_AF,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource6,
        GPIO_AF_USART6,         
    };
    
    sGpio gpioUsart6Rx = 
    {
        GPIOC,     
        RCC_AHB1Periph_GPIOC, 
        {
            GPIO_Pin_7,   
            GPIO_Mode_AF,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource7,
        GPIO_AF_USART6,
    };
    
//    // пин RE линии USART6
//    sGpio gpioUsart6Re = 
//    {
//        GPIOG,     
//        RCC_AHB1Periph_GPIOG, 
//        {
//            GPIO_Pin_8,   
//            GPIO_Mode_OUT,
//            GPIO_High_Speed,
//            GPIO_OType_PP, 
//            GPIO_PuPd_DOWN,
//        },
//        GPIO_PinSource8,
//        0,        
//    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    //пин Реле OSK1
    sGpio gpioK1 = 
    {
        GPIOG,     
        RCC_AHB1Periph_GPIOG, 
        {
            GPIO_Pin_9,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource8,
        0,        
    };
    //пин Реле OSK2
    sGpio gpioK2 = 
    {
        GPIOD,     
        RCC_AHB1Periph_GPIOD, 
        {
            GPIO_Pin_7,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource7,
        0,        
    };
    
    
    
    //пин STBL
    sGpio gpioSTBL = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_11,   
            GPIO_Mode_OUT,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource11,
        0,        
    };  
    
    //каналы АЦП
    sGpio gpioButton1 = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_4,   
            GPIO_Mode_AN,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource4,
        0,        
    };    
    sGpio gpioButton2 = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_5,   
            GPIO_Mode_AN,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource5,
        0,        
    };    
    sGpio gpioButton3 = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_6,   
            GPIO_Mode_AN,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource6,
        0,        
    };    
    sGpio gpioButton4 = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_7,   
            GPIO_Mode_AN,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource7,
        0,        
    };    
    sGpio gpioButton5 = 
    {
        GPIOC,     
        RCC_AHB1Periph_GPIOC, 
        {
            GPIO_Pin_1,   
            GPIO_Mode_AN,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource5,
        0,        
    };  
    
    
    
    //кнопка стоп
    sGpio stopButton = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_3,   
            GPIO_Mode_IN,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource3,
        0,        
    };
    //кнопка режим
    sGpio modeButton = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_4,   
            GPIO_Mode_IN,
            GPIO_High_Speed,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource4,
        0,        
    };
//==============================================================================
//              Инициализация пина
//------------------------------------------------------------------------------
//  gpio    - пин
//==============================================================================

void GPIOInit (sGpio* gpio) 
{
    if(gpio)
    {
        RCC_AHB1PeriphClockCmd(gpio->rcc, ENABLE);  
        GPIO_Init(gpio->port, &gpio->definition);
        
        if(gpio->altFunc)
            GPIO_PinAFConfig(gpio->port, gpio->pinSource, gpio->altFunc);        
    }
}

//==============================================================================
//              Установка на пине единицы
//------------------------------------------------------------------------------
//  gpio    - пин
//==============================================================================

void GPIOSet (sGpio* gpio)
{
    if(gpio)
        GPIO_SetBits(gpio->port, gpio->definition.GPIO_Pin);
}

//==============================================================================
//              Установка на пине нуля
//------------------------------------------------------------------------------
//  gpio    - пин
//==============================================================================

void GPIOReset (sGpio* gpio)
{
    if(gpio)
        GPIO_ResetBits(gpio->port, gpio->definition.GPIO_Pin);
}

//==============================================================================
//              Переключение состояния пина
//------------------------------------------------------------------------------
//  gpio    - пин
//==============================================================================

void GPIOToggle (sGpio* gpio)
{
    if(gpio)
        GPIO_ToggleBits(gpio->port, gpio->definition.GPIO_Pin);
}

//==============================================================================
//              Установка на пине значения
//------------------------------------------------------------------------------
//  value   - значение
//  gpio    - пин
//==============================================================================

void GPIOWrite (uint8_t value, sGpio* gpio)
{
    if(gpio)
        GPIO_WriteBit(gpio->port, gpio->definition.GPIO_Pin, (BitAction)value);
}

//==============================================================================
//              Чтение значения входа пина
//------------------------------------------------------------------------------
//  gpio    - пин
//==============================================================================

uint8_t GPIOReadIn (sGpio* gpio)
{
    if(gpio)
        return GPIO_ReadInputDataBit(gpio->port, gpio->definition.GPIO_Pin);
    return 0;
}

//==============================================================================
//              Чтение значения выхода пина
//------------------------------------------------------------------------------
//  gpio    - пин
//==============================================================================

uint8_t GPIOReadOut (sGpio* gpio)
{
    if(gpio)
        return GPIO_ReadOutputDataBit(gpio->port, gpio->definition.GPIO_Pin);
    return 0;
}

