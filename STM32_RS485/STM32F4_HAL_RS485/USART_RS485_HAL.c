#include "USART_RS485_HAL.h"


#define STM32F7_RS285
//#define STM32F4_RS285



//#define USE_USART1

#define USE_USART2

//#define USE_USART3

//#define USE_USART4

//#define USE_USART5

//#define USE_USART6


static void Error_Handler()
{
    while(1);
}


#ifdef USE_USART1

UART_HandleTypeDef huart1;

UsartRS485_t huart1Rs485;

#define USART1_RX_BUFFER_SIZE 100
static uint8_t USART1_RX_buffer[USART1_RX_BUFFER_SIZE];

#define USART1_TX_BUFFER_SIZE 100
static uint8_t USART1_TX_buffer[USART1_TX_BUFFER_SIZE];

void MX_USART1_UART_Init(void)
{
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart1) != HAL_OK)
    {
      Error_Handler();
    }

  
    huart1.pRxBuffPtr = USART1_RX_buffer;
    huart1.RxXferSize = USART1_RX_BUFFER_SIZE;
    huart1.RxXferCount = USART1_RX_BUFFER_SIZE;
    huart1.pTxBuffPtr = USART1_TX_buffer;
    huart1.TxXferSize = USART1_TX_BUFFER_SIZE;
    huart1.TxXferCount = 0;

    huart1Rs485.rx_package_size = 0;
    huart1Rs485.gpioRE_Pin = GPIO_PIN_8;
    huart1Rs485.gpioRE_Port = GPIOC;
    huart1Rs485.gpioDE_Pin = 0;
    huart1Rs485.gpioDE_Port = 0;
    huart1Rs485.huart = &huart1;
}
#endif



#ifdef USE_USART2
UART_HandleTypeDef huart2;

UsartRS485_t huart2Rs485;

#define USART2_RX_BUFFER_SIZE 100
static uint8_t USART2_RX_buffer[USART2_RX_BUFFER_SIZE];

#define USART2_TX_BUFFER_SIZE 100
static uint8_t USART2_TX_buffer[USART2_TX_BUFFER_SIZE];


void MX_USART2_UART_Init(void)
{
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart2) != HAL_OK)
    {
      Error_Handler();
    }

  
    huart2.pRxBuffPtr = USART2_RX_buffer;
    huart2.RxXferSize = USART2_RX_BUFFER_SIZE;
    huart2.RxXferCount = USART2_RX_BUFFER_SIZE;
    huart2.pTxBuffPtr = USART2_TX_buffer;
    huart2.TxXferSize = USART2_TX_BUFFER_SIZE;
    huart2.TxXferCount = 0;

    huart2Rs485.rx_package_size = 0;
    huart2Rs485.gpioRE_Pin = GPIO_PIN_3;
    huart2Rs485.gpioRE_Port = GPIOD;
    huart2Rs485.gpioDE_Pin = GPIO_PIN_4;
    huart2Rs485.gpioDE_Port = GPIOD;
    huart2Rs485.huart = &huart2;
}
#endif



#ifdef USE_USART3

UART_HandleTypeDef huart3;

UsartRS485_t huart3Rs485;

#define USART3_RX_BUFFER_SIZE 100
static uint8_t USART3_RX_buffer[USART3_RX_BUFFER_SIZE];

#define USART3_TX_BUFFER_SIZE 100
static uint8_t USART3_TX_buffer[USART3_TX_BUFFER_SIZE];

void MX_USART3_UART_Init(void)
{
    huart3.Instance = USART3;
    huart3.Init.BaudRate = 115200;
    huart3.Init.WordLength = UART_WORDLENGTH_8B;
    huart3.Init.StopBits = UART_STOPBITS_1;
    huart3.Init.Parity = UART_PARITY_NONE;
    huart3.Init.Mode = UART_MODE_TX_RX;
    huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart3.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart3) != HAL_OK)
    {
      Error_Handler();
    }

  
    huart3.pRxBuffPtr = USART3_RX_buffer;
    huart3.RxXferSize = USART3_RX_BUFFER_SIZE;
    huart3.RxXferCount = USART3_RX_BUFFER_SIZE;
    huart3.pTxBuffPtr = USART3_TX_buffer;
    huart3.TxXferSize = USART3_TX_BUFFER_SIZE;
    huart3.TxXferCount = 0;

    huart3Rs485.rx_package_size = 0;
    huart3Rs485.gpioRE_Pin = RS_495RE_Pin;
    huart3Rs485.gpioRE_Port = RS_495RE_GPIO_Port;
    huart3Rs485.gpioDE_Pin = 0;
    huart3Rs485.gpioDE_Port = 0;
    huart3Rs485.huart = &huart3;
}
#endif



#ifdef USE_USART4

UART_HandleTypeDef huart4;

UsartRS485_t huart4Rs485;

#define USART4_RX_BUFFER_SIZE 100
static uint8_t USART4_RX_buffer[USART4_RX_BUFFER_SIZE];

#define USART4_TX_BUFFER_SIZE 100
static uint8_t USART4_TX_buffer[USART4_TX_BUFFER_SIZE];

void MX_USART4_UART_Init(void)
{
    huart4.Instance = UART4;
    huart4.Init.BaudRate = 115200;
    huart4.Init.WordLength = UART_WORDLENGTH_8B;
    huart4.Init.StopBits = UART_STOPBITS_1;
    huart4.Init.Parity = UART_PARITY_NONE;
    huart4.Init.Mode = UART_MODE_TX_RX;
    huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart4.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart4) != HAL_OK)
    {
      Error_Handler();
    }

  
    huart4.pRxBuffPtr = USART4_RX_buffer;
    huart4.RxXferSize = USART4_RX_BUFFER_SIZE;
    huart4.RxXferCount = USART4_RX_BUFFER_SIZE;
    huart4.pTxBuffPtr = USART4_TX_buffer;
    huart4.TxXferSize = USART4_TX_BUFFER_SIZE;
    huart4.TxXferCount = 0;

    huart4Rs485.rx_package_size = 0;
    huart4Rs485.gpioRE_Pin = RS_495RE_Pin;
    huart4Rs485.gpioRE_Port = RS_495RE_GPIO_Port;
    huart4Rs485.gpioDE_Pin = 0;
    huart4Rs485.gpioDE_Port = 0;
    huart4Rs485.huart = &huart4;
}
#endif



#ifdef USE_USART5

UART_HandleTypeDef huart5;

UsartRS485_t huart5Rs485;

#define USART5_RX_BUFFER_SIZE 100
static uint8_t USART5_RX_buffer[USART5_RX_BUFFER_SIZE];

#define USART5_TX_BUFFER_SIZE 100
static uint8_t USART5_TX_buffer[USART5_TX_BUFFER_SIZE];


void MX_USART5_UART_Init(void)
{
    huart5.Instance = UART5;
    huart5.Init.BaudRate = 115200;
    huart5.Init.WordLength = UART_WORDLENGTH_8B;
    huart5.Init.StopBits = UART_STOPBITS_1;
    huart5.Init.Parity = UART_PARITY_NONE;
    huart5.Init.Mode = UART_MODE_TX_RX;
    huart5.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart5.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart5) != HAL_OK)
    {
      Error_Handler();
    }

  
    huart5.pRxBuffPtr = USART5_RX_buffer;
    huart5.RxXferSize = USART5_RX_BUFFER_SIZE;
    huart5.RxXferCount = USART5_RX_BUFFER_SIZE;
    huart5.pTxBuffPtr = USART5_TX_buffer;
    huart5.TxXferSize = USART5_TX_BUFFER_SIZE;
    huart5.TxXferCount = 0;

    huart5Rs485.rx_package_size = 0;
    huart5Rs485.gpioRE_Pin = RS_495RE_Pin;
    huart5Rs485.gpioRE_Port = RS_495RE_GPIO_Port;
    huart5Rs485.gpioDE_Pin = 0;
    huart5Rs485.gpioDE_Port = 0;
    huart5Rs485.huart = &huart5;
}
#endif



#ifdef USE_USART6

UART_HandleTypeDef huart6;

UsartRS485_t huart6Rs485;

#define USART6_RX_BUFFER_SIZE 100
static uint8_t USART6_RX_buffer[USART6_RX_BUFFER_SIZE];

#define USART6_TX_BUFFER_SIZE 100
static uint8_t USART6_TX_buffer[USART6_TX_BUFFER_SIZE];

void MX_USART6_UART_Init(void)
{
    huart6.Instance = UART5;
    huart6.Init.BaudRate = 115200;
    huart6.Init.WordLength = UART_WORDLENGTH_8B;
    huart6.Init.StopBits = UART_STOPBITS_1;
    huart6.Init.Parity = UART_PARITY_NONE;
    huart6.Init.Mode = UART_MODE_TX_RX;
    huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart6.Init.OverSampling = UART_OVERSAMPLING_16;
    if (HAL_UART_Init(&huart6) != HAL_OK)
    {
      Error_Handler();
    }

  
    huart6.pRxBuffPtr = USART6_RX_buffer;
    huart6.RxXferSize = USART6_RX_BUFFER_SIZE;
    huart6.RxXferCount = USART6_RX_BUFFER_SIZE;
    huart6.pTxBuffPtr = USART6_TX_buffer;
    huart6.TxXferSize = USART6_TX_BUFFER_SIZE;
    huart6.TxXferCount = 0;

    huart6Rs485.rx_package_size = 0;
    huart6Rs485.gpioRE_Pin = RS_495RE_Pin;
    huart6Rs485.gpioRE_Port = RS_495RE_GPIO_Port;
    huart6Rs485.gpioDE_Pin = 0;
    huart6Rs485.gpioDE_Port = 0;
    huart6Rs485.huart = &huart6;
}
#endif






void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    if(uartHandle->Instance == USART1)
    {
        __HAL_RCC_USART1_CLK_ENABLE();
      
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART1 GPIO Configuration    
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        
        /*re de pins initialization*/
        __HAL_RCC_GPIOC_CLK_ENABLE();
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, GPIO_PIN_RESET);

        GPIO_InitStruct.Pin = GPIO_PIN_8;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
        
        /* USART1 interrupt Init */
        HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_IDLE);

    }
    else if ( uartHandle->Instance == USART2 )
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        
        
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /**USART2 GPIO Configuration    
        PD5     ------> USART2_TX
        PD6     ------> USART2_RX 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
        
        
        /* USART2 interrupt Init */
        HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);
        
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_IDLE);
    }
    else if ( uartHandle->Instance == USART3 )
    {
        __HAL_RCC_USART3_CLK_ENABLE();
        
        
        //init rx tx pins
        
        //init re de pins
        
        /* USART3 interrupt Init */
        HAL_NVIC_SetPriority(USART3_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART3_IRQn);
        
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_IDLE);
    }
    else if ( uartHandle->Instance == UART4 )
    {
        __HAL_RCC_UART4_CLK_ENABLE();
        
        
        //init rx tx pins
        
        //init re de pins
        
        /* UART4 interrupt Init */
        HAL_NVIC_SetPriority(UART4_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
        
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_IDLE);
    }
    else if ( uartHandle->Instance == UART5 )
    {
        __HAL_RCC_UART5_CLK_ENABLE();
        
        
        //init rx tx pins
        
        //init re de pins
        
        
        /* UART5 interrupt Init */
        HAL_NVIC_SetPriority(UART5_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(UART5_IRQn);
        
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_IDLE);
    }
    else if ( uartHandle->Instance == USART6 )
    {
        __HAL_RCC_USART6_CLK_ENABLE();
        
        
        //init rx tx pins
        
        //init re de pins
        
        /* USART6 interrupt Init */
        HAL_NVIC_SetPriority(USART6_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(USART6_IRQn);
        
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_RXNE);
        __HAL_UART_ENABLE_IT(uartHandle, UART_IT_IDLE);
    }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
    if(uartHandle->Instance == USART1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_USART1_CLK_DISABLE();
      
        /**USART1 GPIO Configuration    
        PA9     ------> USART1_TX
        PA10     ------> USART1_RX 
        */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

        /* USART1 interrupt Deinit */
        HAL_NVIC_DisableIRQ(USART1_IRQn);
    }
    else if (uartHandle->Instance == USART2)
    {
        
    }
    else if (uartHandle->Instance == USART3)
    {
        
    }
    else if (uartHandle->Instance == UART4)
    {
        
    }
} 


void Usart_RS485_Send(UsartRS485_t * usart485, uint8_t * tx_buffer, int buffer_size)
{
    if ( buffer_size >= usart485->huart->RxXferSize )
        return;
    
    while(__HAL_UART_GET_FLAG(usart485->huart, UART_FLAG_TXE) == RESET );
    
    for ( int i = 0; i < buffer_size; i++ )
        usart485->huart->pTxBuffPtr[i] = tx_buffer[i];
    
    //RE DE pins to TX
    if (usart485->gpioRE_Port != 0)
        HAL_GPIO_WritePin(usart485->gpioRE_Port, usart485->gpioRE_Pin, GPIO_PIN_SET);
    if (usart485->gpioDE_Port != 0)
        HAL_GPIO_WritePin(usart485->gpioDE_Port, usart485->gpioDE_Pin, GPIO_PIN_SET);
    
    usart485->huart->TxXferCount = buffer_size + 1;
    
    __HAL_UART_ENABLE_IT(usart485->huart, UART_IT_TXE);
}


/*USART RS485 Handler*/
static void USART_RS485_Handler(UsartRS485_t * usart485)
{
    static int tx_bytes_counter = 0;
    
    if (__HAL_UART_GET_FLAG(usart485->huart, UART_FLAG_TXE) == SET)
    {
        //package transmitted
        if (usart485->huart->TxXferCount == 0)
        {
            //RE DE pins to RX
            if (usart485->gpioRE_Port != 0)
                HAL_GPIO_WritePin(usart485->gpioRE_Port, usart485->gpioRE_Pin, GPIO_PIN_RESET);
            if (usart485->gpioDE_Port != 0)
                HAL_GPIO_WritePin(usart485->gpioDE_Port, usart485->gpioDE_Pin, GPIO_PIN_RESET);
            
            __HAL_UART_DISABLE_IT(usart485->huart, UART_IT_TXE);
            while(__HAL_UART_GET_FLAG(usart485->huart, UART_FLAG_TC) == RESET);
            tx_bytes_counter = 0;
        }
        //byte transmitted
        else
        {
            usart485->huart->TxXferCount--;
#ifdef STM32F7_RS285
            usart485->huart->Instance->TDR = usart485->huart->pTxBuffPtr[tx_bytes_counter++];
#endif
#ifdef STM32F4_RS285
            usart485->huart->Instance->DR = usart485->huart->pTxBuffPtr[tx_bytes_counter++];
#endif
            
        }
    }
    
    //package received
    if ( __HAL_UART_GET_FLAG(usart485->huart, UART_FLAG_IDLE) == SET )
    {
        __HAL_UART_CLEAR_IDLEFLAG(usart485->huart);
        
        int rx_bytes_counter = usart485->huart->RxXferSize - usart485->huart->RxXferCount;
        if (rx_bytes_counter < usart485->huart->RxXferSize && rx_bytes_counter > 0)
            usart485->rx_package_size = rx_bytes_counter;
        else
            usart485->rx_package_size = 0;
        
        usart485->huart->RxXferCount = usart485->huart->RxXferSize;
        usart485->huart->pRxBuffPtr = &(usart485->huart->pRxBuffPtr[0]);
    }
    //byte received
    if (__HAL_UART_GET_FLAG(usart485->huart, UART_FLAG_RXNE) == SET)
    {
        __HAL_UART_CLEAR_FLAG(usart485->huart, UART_FLAG_RXNE);
        int byte_position = usart485->huart->RxXferSize - usart485->huart->RxXferCount;
        if ( byte_position >= 0 && byte_position < usart485->huart->RxXferSize)
        {
#ifdef STM32F7_RS285
            usart485->huart->pRxBuffPtr[byte_position] = usart485->huart->Instance->RDR;
#endif
#ifdef STM32F4_RS285
            usart485->huart->pRxBuffPtr[byte_position] = usart485->huart->Instance->DR;
#endif
            usart485->huart->RxXferCount--;
        }
    }
}


extern "C"
{
#ifdef USE_USART1
    void USART1_IRQHandler(void)
    {
        USART_RS485_Handler(&huart1Rs485);
    }
#endif
    
#ifdef USE_USART2
    void USART2_IRQHandler(void)
    {
        USART_RS485_Handler(&huart2Rs485);
    }
#endif
    
    
#ifdef USE_USART3
    void USART3_IRQHandler(void)
    {
        USART_RS485_Handler(&huart3Rs485);
    }
#endif
    
#ifdef USE_USART4
    void UART4_IRQHandler(void)
    {
        USART_RS485_Handler(&huart4Rs485);
    }
#endif
    
#ifdef USE_USART5
    void UART5_IRQHandler(void)
    {
        USART_RS485_Handler(&huart5Rs485);
    }
#endif
    
#ifdef USE_USART6
    void USART6_IRQHandler(void)
    {
        USART_RS485_Handler(&huart6Rs485);
    }
#endif
}
