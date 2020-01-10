//******************************************************************************
// ��� �����    :  'GPIO.c'
// ���������    :  ������� ������ �����-������ (F4)
// �����        :  �������� �.�.
// ��������     :  manianov.rus@gmail.com
// ����         :  25.07.2015
//******************************************************************************

#include "GPIO.h"

//==============================================================================
//                  ���������� ����������
//==============================================================================


    //������������� �����
    sGpio gpioMode = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_10,   
            GPIO_Mode_IN,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource10,
        0,        
    };



    //������ ����
    sGpio gpioStop = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_9,   
            GPIO_Mode_IN,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource9,
        0,        
    };



    // ��� RX ����� USART1
    sGpio gpioUsart1Rx = 
    {
        GPIOB,     
        RCC_AHB1Periph_GPIOB, 
        {
            GPIO_Pin_7,   
            GPIO_Mode_AF,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource7,
        GPIO_AF_USART1,        
    };

    // ��� TX ����� USART1
    sGpio gpioUsart1Tx = 
    {
        GPIOB,     
        RCC_AHB1Periph_GPIOB, 
        {
            GPIO_Pin_6,   
            GPIO_Mode_AF,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource6,
        GPIO_AF_USART1,        
    };
    
    // ��� RE ����� USART1
    sGpio gpioUsart1Re = 
    {
        GPIOB,     
        RCC_AHB1Periph_GPIOB, 
        {
            GPIO_Pin_8,   
            GPIO_Mode_OUT,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource8,
        0,        
    };
    // ��� DE ����� USART1
    sGpio gpioUsart1De = 
    {
        GPIOB,     
        RCC_AHB1Periph_GPIOB, 
        {
            GPIO_Pin_9,   
            GPIO_Mode_OUT,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource9,
        0,        
    }; 























    // ��� RX ����� USART2
    sGpio gpioUsart2Rx = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_3,   
            GPIO_Mode_AF,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource3,
        GPIO_AF_USART2,        
    };

    // ��� TX ����� USART2
    sGpio gpioUsart2Tx = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_2,   
            GPIO_Mode_AF,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource2,
        GPIO_AF_USART2,        
    };
    
    // ��� RE ����� USART2
    sGpio gpioUsart2Re = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_0,   
            GPIO_Mode_OUT,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource0,
        0,        
    };
    // ��� DE ����� USART2
    sGpio gpioUsart2De = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_1,   
            GPIO_Mode_OUT,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource1,
        0,        
    };    
    
    
    /*************************/
    /****USART6*/
    /*************************/
    // ��� RX ����� USART6
    sGpio gpioUsart6Rx = 
    {
        GPIOC,     
        RCC_AHB1Periph_GPIOC, 
        {
            GPIO_Pin_7,   
            GPIO_Mode_AF,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource7,
        GPIO_AF_USART6,        
    };

    // ��� TX ����� USART6
    sGpio gpioUsart6Tx = 
    {
        GPIOC,     
        RCC_AHB1Periph_GPIOC, 
        {
            GPIO_Pin_6,   
            GPIO_Mode_AF,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_UP,
        },
        GPIO_PinSource6,
        GPIO_AF_USART6,        
    };
    // ��� RE ����� USART6
    sGpio gpioUsart6Re = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_9,   
            GPIO_Mode_OUT,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource9,
        0,        
    };
    // ��� DE ����� USART6
    sGpio gpioUsart6De = 
    {
        GPIOA,     
        RCC_AHB1Periph_GPIOA, 
        {
            GPIO_Pin_8,   
            GPIO_Mode_OUT,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource8,
        0,        
    }; 
    
    
    
    
    
    
    
    
    //�������
    sGpio gpioBeeper = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_11,   
            GPIO_Mode_OUT,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_DOWN,
        },
        GPIO_PinSource11,
        0,        
    }; 
    
    
    
    
    
    
    
    
    
    
    
    
    
    sGpio gpioButton1 = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_6,   
            GPIO_Mode_AN,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource6,
        0, 
    };
    sGpio gpioButton2 = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_7,   
            GPIO_Mode_AN,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource7,
        0, 
    };
    sGpio gpioButton3 = 
    {
        GPIOF,     
        RCC_AHB1Periph_GPIOF, 
        {
            GPIO_Pin_8,   
            GPIO_Mode_AN,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource8,
        0, 
    };
    
    sGpio STBLPin = 
    {
        GPIOC,     
        RCC_AHB1Periph_GPIOC, 
        {
            GPIO_Pin_0,   
            GPIO_Mode_OUT,
            GPIO_Speed_100MHz,
            GPIO_OType_PP, 
            GPIO_PuPd_NOPULL,
        },
        GPIO_PinSource8,
        0, 
    };
    
//==============================================================================
//              ������������� ����
//------------------------------------------------------------------------------
//  gpio    - ���
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
//              ��������� �� ���� �������
//------------------------------------------------------------------------------
//  gpio    - ���
//==============================================================================

void GPIOSet (sGpio* gpio)
{
    if(gpio)
        GPIO_SetBits(gpio->port, gpio->definition.GPIO_Pin);
}

//==============================================================================
//              ��������� �� ���� ����
//------------------------------------------------------------------------------
//  gpio    - ���
//==============================================================================

void GPIOReset (sGpio* gpio)
{
    if(gpio)
        GPIO_ResetBits(gpio->port, gpio->definition.GPIO_Pin);
}

//==============================================================================
//              ������������ ��������� ����
//------------------------------------------------------------------------------
//  gpio    - ���
//==============================================================================

void GPIOToggle (sGpio* gpio)
{
    if(gpio)
        GPIO_ToggleBits(gpio->port, gpio->definition.GPIO_Pin);
}

//==============================================================================
//              ��������� �� ���� ��������
//------------------------------------------------------------------------------
//  value   - ��������
//  gpio    - ���
//==============================================================================

void GPIOWrite (uint8_t value, sGpio* gpio)
{
    if(gpio)
        GPIO_WriteBit(gpio->port, gpio->definition.GPIO_Pin, (BitAction)value);
}

//==============================================================================
//              ������ �������� ����� ����
//------------------------------------------------------------------------------
//  gpio    - ���
//==============================================================================

uint8_t GPIOReadIn (sGpio* gpio)
{
    if(gpio)
        return GPIO_ReadInputDataBit(gpio->port, gpio->definition.GPIO_Pin);
    return 0;
}

//==============================================================================
//              ������ �������� ������ ����
//------------------------------------------------------------------------------
//  gpio    - ���
//==============================================================================

uint8_t GPIOReadOut (sGpio* gpio)
{
    if(gpio)
        return GPIO_ReadOutputDataBit(gpio->port, gpio->definition.GPIO_Pin);
    return 0;
}

