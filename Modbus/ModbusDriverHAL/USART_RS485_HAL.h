#ifndef __usart_H
#define __usart_H


#ifdef __cplusplus
 extern "C" {
#endif

     

#include "stm32f4xx_hal.h"     

typedef struct
{
    int rx_package_size;
    GPIO_TypeDef * gpioRE_Port;
    uint16_t gpioRE_Pin;
    GPIO_TypeDef * gpioDE_Port;
    uint16_t gpioDE_Pin;
    UART_HandleTypeDef * huart;
}UsartRS485_t;


extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;



void MX_USART1_UART_Init(void);
//void MX_USART2_UART_Init(void);
//void MX_USART3_UART_Init(void);
//void MX_USART4_UART_Init(void);
//void MX_USART5_UART_Init(void);
//void MX_USART6_UART_Init(void);

/* USER CODE BEGIN Prototypes */
void Usart_RS485_Send(UsartRS485_t * usart485, uint8_t * tx_buffer, int buffer_size);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif


/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
