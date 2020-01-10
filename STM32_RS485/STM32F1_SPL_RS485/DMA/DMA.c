//******************************************************************************
// ��� �����    :  'DMA.c'
// ���������    :  ����� DMA (F1)
// �����        :  �������� �.�.
// ��������     :  manianov.rus@gmail.com
// ����         :  27.07.2015
//******************************************************************************


#include "DMA.h"

//==============================================================================
//                           ��������� � �������
//==============================================================================

    //#define DMA_USART1_TX_USE

    //#define DMA_USART1_RX_USE

 //   #define DMA_USART2_TX_USE

    #define DMA_USART2_RX_USE

//    #define DMA_USART3_TX_USE

//    #define DMA_USART3_RX_USE

    //#define DMA_USART4_TX_USE

    //#define DMA_USART4_RX_USE

//==============================================================================
//                          ���������� ����������
//==============================================================================

#ifdef DMA_USART1_TX_USE
    
    // DMA ����������� USART1
    sDma dmaUsart1Tx = 
    {
        RCC_AHBPeriph_DMA1,
        DMA1_Channel4,
        {
            (uint32_t)&(USART1->DR),
            0,
            DMA_DIR_PeripheralDST,
            0,
            DMA_PeripheralInc_Disable,
            DMA_MemoryInc_Enable,
            DMA_PeripheralDataSize_Byte,
            DMA_MemoryDataSize_Byte,
            DMA_Mode_Normal,
            DMA_Priority_VeryHigh,
            DMA_M2M_Disable,
        }
    };
#endif //DMA_USART1_TX_USE
 
#ifdef DMA_USART1_RX_USE
    
    // DMA ����������� USART1
    sDma dmaUsart1Rx = 
    {
        RCC_AHBPeriph_DMA1,
        DMA1_Channel5,
        {
            (uint32_t)&(USART1->DR),
            0,
            DMA_DIR_PeripheralSRC,
            0,
            DMA_PeripheralInc_Disable,
            DMA_MemoryInc_Enable,
            DMA_PeripheralDataSize_Byte,
            DMA_MemoryDataSize_Byte,
            DMA_Mode_Normal,
            DMA_Priority_VeryHigh,
            DMA_M2M_Disable,
        }
    };
        
#endif //DMA_USART1_RX_USE
     
#ifdef DMA_USART2_TX_USE
    
    // DMA ����������� USART2
    sDma dmaUsart2Tx = 
    {
        RCC_AHBPeriph_DMA1,
        DMA1_Channel7,
        {
            (uint32_t)&(USART2->DR),
            0,
            DMA_DIR_PeripheralDST,
            0,
            DMA_PeripheralInc_Disable,
            DMA_MemoryInc_Enable,
            DMA_PeripheralDataSize_Byte,
            DMA_MemoryDataSize_Byte,
            DMA_Mode_Normal,
            DMA_Priority_VeryHigh,
            DMA_M2M_Disable,
        }
    };
#endif //DMA_USART2_TX_USE
 
#ifdef DMA_USART2_RX_USE
    
    // DMA ����������� USART2
    sDma dmaUsart2Rx = 
    {
        RCC_AHBPeriph_DMA1,
        DMA1_Channel6,
        {
            (uint32_t)&(USART2->DR),
            0,
            DMA_DIR_PeripheralSRC,
            0,
            DMA_PeripheralInc_Disable,
            DMA_MemoryInc_Enable,
            DMA_PeripheralDataSize_Byte,
            DMA_MemoryDataSize_Byte,
            DMA_Mode_Normal,
            DMA_Priority_VeryHigh,
            DMA_M2M_Disable,
        }
    };
        
#endif //DMA_USART2_RX_USE
          
#ifdef DMA_USART3_TX_USE
    
    // DMA ����������� USART3
    sDma dmaUsart3Tx = 
    {
        RCC_AHBPeriph_DMA1,
        DMA1_Channel2,
        {
            (uint32_t)&(USART3->DR),
            0,
            DMA_DIR_PeripheralDST,
            0,
            DMA_PeripheralInc_Disable,
            DMA_MemoryInc_Enable,
            DMA_PeripheralDataSize_Byte,
            DMA_MemoryDataSize_Byte,
            DMA_Mode_Normal,
            DMA_Priority_VeryHigh,
            DMA_M2M_Disable,
        }
    };
#endif //DMA_USART3_TX_USE
 
#ifdef DMA_USART3_RX_USE
    
    // DMA ����������� USART2
    sDma dmaUsart3Rx = 
    {
        RCC_AHBPeriph_DMA1,
        DMA1_Channel3,
        {
            (uint32_t)&(USART3->DR),
            0,
            DMA_DIR_PeripheralSRC,
            0,
            DMA_PeripheralInc_Disable,
            DMA_MemoryInc_Enable,
            DMA_PeripheralDataSize_Byte,
            DMA_MemoryDataSize_Byte,
            DMA_Mode_Normal,
            DMA_Priority_VeryHigh,
            DMA_M2M_Disable,
        }
    };        
#endif //DMA_USART3_RX_USE

#ifdef DMA_USART4_TX_USE
    
    // DMA ����������� USART4
    sDma dmaUsart4Tx = 
    {
        RCC_AHBPeriph_DMA2,
        DMA2_Channel5,
        {
            (uint32_t)&(UART4->DR),
            0,
            DMA_DIR_PeripheralDST,
            0,
            DMA_PeripheralInc_Disable,
            DMA_MemoryInc_Enable,
            DMA_PeripheralDataSize_Byte,
            DMA_MemoryDataSize_Byte,
            DMA_Mode_Normal,
            DMA_Priority_VeryHigh,
            DMA_M2M_Disable,
        }
    };
#endif //DMA_USART4_TX_USE
 
#ifdef DMA_USART4_RX_USE
    
    // DMA ����������� USART2
    sDma dmaUsart4Rx = 
    {
        RCC_AHBPeriph_DMA2,
        DMA2_Channel3,
        {
            (uint32_t)&(UART4->DR),
            0,
            DMA_DIR_PeripheralSRC,
            0,
            DMA_PeripheralInc_Disable,
            DMA_MemoryInc_Enable,
            DMA_PeripheralDataSize_Byte,
            DMA_MemoryDataSize_Byte,
            DMA_Mode_Normal,
            DMA_Priority_VeryHigh,
            DMA_M2M_Disable,
        }
    };
        
#endif //DMA_USART4_RX_USE

void DMAInit (uint32_t buffer, uint32_t size, sDma* dma)
{
    if(dma)
    {
        // ������������ DMA TX
        RCC_AHBPeriphClockCmd(dma->rcc, ENABLE);    
        
        dma->definitions.DMA_MemoryBaseAddr = buffer;
        dma->definitions.DMA_BufferSize = size;
        
        // ���������������� DMA TX        
        DMA_Init(dma->channel, &dma->definitions); 
    }
}



