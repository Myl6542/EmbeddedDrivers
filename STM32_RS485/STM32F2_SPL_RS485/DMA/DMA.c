//******************************************************************************
// Имя файла    :  'DMA.c'
// заголовок    :  Модул DMA (F4)
// Автор        :  Маньянов Р.Р.
// Контакты     :  manianov.rus@gmail.com
// Дата         :  28.07.2015
//******************************************************************************

#include "DMA.h"

//==============================================================================
//                           Константы и макросы
//==============================================================================

//    #define DMA1_STREAM1_USE

//    #define DMA1_STREAM2_USE

//    #define DMA1_STREAM3_USE

//    #define DMA1_STREAM4_USE

    #define DMA1_STREAM5_USE

    #define DMA1_STREAM6_USE

//    #define DMA1_STREAM7_USE

//    #define DMA2_STREAM1_USE

    #define DMA2_STREAM2_USE

//    #define DMA2_STREAM3_USE

//    #define DMA2_STREAM4_USE

//    #define DMA2_STREAM5_USE

//    #define DMA2_STREAM6_USE

    #define DMA2_STREAM7_USE


//==============================================================================
//                          Глобальные переменные
//==============================================================================

#ifdef DMA1_STREAM5_USE    
    // DMA приема USART2
    sDma dma1Stream5 = 
    {
        RCC_AHB1Periph_DMA1,
        DMA1_Stream5,
        {
            .DMA_Channel = DMA_Channel_4,
            .DMA_PeripheralBaseAddr = 0,
            .DMA_Memory0BaseAddr = 0,
            .DMA_DIR = DMA_DIR_PeripheralToMemory,
            .DMA_BufferSize = 0,
            .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
            .DMA_MemoryInc = DMA_MemoryInc_Enable,
            .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
            .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
            .DMA_Mode = DMA_Mode_Circular,
            .DMA_Priority = DMA_Priority_High,
            .DMA_FIFOMode = DMA_FIFOMode_Disable,
            .DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull,
            .DMA_MemoryBurst = DMA_MemoryBurst_Single,
            .DMA_PeripheralBurst = DMA_PeripheralBurst_Single,           
        },
    };
#endif //DMA2_STREAM5_USE

#ifdef DMA1_STREAM6_USE    
    // DMA отправления USART2
    sDma dma1Stream6 = 
    {
        RCC_AHB1Periph_DMA1,
        DMA1_Stream6,
        {
            .DMA_Channel = DMA_Channel_4,
            .DMA_PeripheralBaseAddr = 0,
            .DMA_Memory0BaseAddr = 0,
            .DMA_DIR = DMA_DIR_MemoryToPeripheral,
            .DMA_BufferSize = 0,
            .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
            .DMA_MemoryInc = DMA_MemoryInc_Enable,
            .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
            .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
            .DMA_Mode = DMA_Mode_Normal,
            .DMA_Priority = DMA_Priority_High,
            .DMA_FIFOMode = DMA_FIFOMode_Disable,
            .DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull,
            .DMA_MemoryBurst = DMA_MemoryBurst_Single,
            .DMA_PeripheralBurst = DMA_PeripheralBurst_Single,           
        },
    };

#endif //DMA2_STREAM7_USE

   
   
    
    
    
#ifdef DMA2_STREAM2_USE    
    // DMA приема USART2
    sDma dma2Stream2 = 
    {
        RCC_AHB1Periph_DMA2,
        DMA2_Stream2,
        {
            .DMA_Channel = DMA_Channel_4,
            .DMA_PeripheralBaseAddr = 0,
            .DMA_Memory0BaseAddr = 0,
            .DMA_DIR = DMA_DIR_PeripheralToMemory,
            .DMA_BufferSize = 0,
            .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
            .DMA_MemoryInc = DMA_MemoryInc_Enable,
            .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
            .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
            .DMA_Mode = DMA_Mode_Circular,
            .DMA_Priority = DMA_Priority_High,
            .DMA_FIFOMode = DMA_FIFOMode_Disable,
            .DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull,
            .DMA_MemoryBurst = DMA_MemoryBurst_Single,
            .DMA_PeripheralBurst = DMA_PeripheralBurst_Single,           
        },
    };
#endif //DMA2_STREAM5_USE

#ifdef DMA2_STREAM7_USE    
    // DMA отправления USART2
    sDma dma2Stream7 = 
    {
        RCC_AHB1Periph_DMA2,
        DMA2_Stream7,
        {
            .DMA_Channel = DMA_Channel_4,
            .DMA_PeripheralBaseAddr = 0,
            .DMA_Memory0BaseAddr = 0,
            .DMA_DIR = DMA_DIR_MemoryToPeripheral,
            .DMA_BufferSize = 0,
            .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
            .DMA_MemoryInc = DMA_MemoryInc_Enable,
            .DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte,
            .DMA_MemoryDataSize = DMA_MemoryDataSize_Byte,
            .DMA_Mode = DMA_Mode_Normal,
            .DMA_Priority = DMA_Priority_High,
            .DMA_FIFOMode = DMA_FIFOMode_Disable,
            .DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull,
            .DMA_MemoryBurst = DMA_MemoryBurst_Single,
            .DMA_PeripheralBurst = DMA_PeripheralBurst_Single,           
        },
    };

#endif //DMA2_STREAM7_USE
    
    
    sDma dmaAdc3 = 
    {
        RCC_AHB1Periph_DMA2,
        DMA2_Stream0,
        {
            .DMA_Channel = DMA_Channel_2,
            .DMA_PeripheralBaseAddr = 0,
            .DMA_Memory0BaseAddr = 0,
            .DMA_DIR = DMA_DIR_PeripheralToMemory,
            .DMA_BufferSize = 0,
            .DMA_PeripheralInc = DMA_PeripheralInc_Disable,
            .DMA_MemoryInc = DMA_MemoryInc_Enable,
            .DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord,
            .DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord,
            .DMA_Mode = DMA_Mode_Circular,
            .DMA_Priority = DMA_Priority_High,
            .DMA_FIFOMode = DMA_FIFOMode_Disable,
            .DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull,
            .DMA_MemoryBurst = DMA_MemoryBurst_Single,
            .DMA_PeripheralBurst = DMA_PeripheralBurst_Single,           
        },
    };
    
    
//==============================================================================
//                      Инициализация DMA
//  buffer  - буфер DMA
//  size    - размер буфера
//  dma     - DMA
//==============================================================================

void DMAInit (uint32_t buffer, uint32_t size, uint32_t peripheral, sDma* dma)
{
    if(dma)
    {
        // Тактирование DMA 
        RCC_AHB1PeriphClockCmd(dma->rcc, ENABLE);    
        
        dma->definitions.DMA_PeripheralBaseAddr = peripheral;
        dma->definitions.DMA_Memory0BaseAddr = buffer;
        dma->definitions.DMA_BufferSize = size;
        
        // Конфигурирование DMA      
        DMA_Init(dma->channelStream, &dma->definitions); 
    }
}

//==============================================================================
//                     Управление DMA
//------------------------------------------------------------------------------   
//  NewState    - новое состояние 
//  size        - размер буфера
//  dma         - DMA
//==============================================================================

void DMACmd (FunctionalState NewState, sDma* dma)
{
    if(dma)
        DMA_Cmd(dma->channelStream, NewState);
}
uint16_t DMAGetCurrDataCounter (sDma* dma);
uint16_t DMAGetCurrDataCounter (sDma* dma)
{
    if(dma)
        return DMA_GetCurrDataCounter(dma->channelStream);
    return 0;
}
void DMASetCurrDataCounter (uint32_t dataCounter, sDma* dma);
void DMASetCurrDataCounter (uint32_t dataCounter, sDma* dma)
{
    if(dma)
        DMA_SetCurrDataCounter(dma->channelStream, dataCounter);
}    

void DMAConfigInterupt(uint32_t irqMask, FunctionalState NewState, sDma* dma)
{
    if(dma)   
    {
        DMA_ITConfig(dma->channelStream, irqMask, NewState);    
        dma->nvicStruct.NVIC_IRQChannelCmd = NewState; 
        NVIC_Init(&dma->nvicStruct);            
    }
}

void DMASetExternalIrqHandler(void (*handler)(void *subj), void* handlerSubject, sDma* dma)
{
    dma->IrqHandler = handler;
    dma->IrqHandlerSubject = handlerSubject;
}

void DMAClearFlag (sDmaFlag flag, sDma* dma)
{
    uint32_t splFlag;
    switch(flag)
    {
        case(DMA_FLAG_FEIF):
        {
            break;        
        }
        case(DMA_FLAG_DMEIF):
        {
            break;        
        }
        case(DMA_FLAG_TEIF):
        {
            break;        
        }
        case(DMA_FLAG_HTIF):
        {
            break;        
        }
        case(DMA_FLAG_TCIF):
        {
            if(dma->channelStream == DMA1_Stream0 || dma->channelStream == DMA2_Stream0)
                splFlag = DMA_FLAG_TCIF0;
            else if(dma->channelStream == DMA1_Stream1 || dma->channelStream == DMA2_Stream1)
                splFlag = DMA_FLAG_TCIF1;
            else if(dma->channelStream == DMA1_Stream2 || dma->channelStream == DMA2_Stream2)
                splFlag = DMA_FLAG_TCIF2;
            else if(dma->channelStream == DMA1_Stream3 || dma->channelStream == DMA2_Stream3)
                splFlag = DMA_FLAG_TCIF3;
            else if(dma->channelStream == DMA1_Stream4 || dma->channelStream == DMA2_Stream4)
                splFlag = DMA_FLAG_TCIF4;
            else if(dma->channelStream == DMA1_Stream5 || dma->channelStream == DMA2_Stream5)
                splFlag = DMA_FLAG_TCIF5;
            else if(dma->channelStream == DMA1_Stream6 || dma->channelStream == DMA2_Stream6)
                splFlag = DMA_FLAG_TCIF6;
            else if(dma->channelStream == DMA1_Stream7 || dma->channelStream == DMA2_Stream7)
                splFlag = DMA_FLAG_TCIF7;
            break;        
        }
        default:
            return;
    }
    DMA_ClearFlag(dma->channelStream, splFlag);
}

#ifdef DMA1_STREAM1_USE  
void DMA1_Stream1_IRQHandler()
{
   dma1Stream1.IrqHandler(dma1Stream1.IrqHandlerSubject);
}
#endif //DMA1_STREAM1_USE 

#ifdef DMA1_STREAM2_USE  
void DMA1_Stream2_IRQHandler()
{
   dma1Stream2.IrqHandler(dma1Stream2.IrqHandlerSubject);
}
#endif //DMA1_STREAM1_USE 

#ifdef DMA1_STREAM3_USE  
void DMA1_Stream3_IRQHandler()
{
   dma1Stream3.IrqHandler(dma1Stream3.IrqHandlerSubject);
}
#endif //DMA1_STREAM3_USE 

#ifdef DMA1_STREAM4_USE  
void DMA1_Stream4_IRQHandler()
{
   dma1Stream4.IrqHandler(dma1Stream4.IrqHandlerSubject);
}
#endif //DMA1_STREAM4_USE 

#ifdef DMA1_STREAM5_USE  
void DMA1_Stream5_IRQHandler()
{
   dma1Stream5.IrqHandler(dma1Stream5.IrqHandlerSubject);
}
#endif //DMA1_STREAM5_USE 

#ifdef DMA1_STREAM6_USE  
void DMA1_Stream6_IRQHandler()
{
   dma1Stream6.IrqHandler(dma1Stream6.IrqHandlerSubject);
}
#endif //DMA1_STREAM6_USE 

#ifdef DMA1_STREAM7_USE  
void DMA1_Stream7_IRQHandler()
{
   dma1Stream7.IrqHandler(dma1Stream7.IrqHandlerSubject);
}
#endif //DMA1_STREAM7_USE 

#ifdef DMA2_STREAM1_USE  
void DMA1_Stream1_IRQHandler()
{
   dma2Stream1.IrqHandler(dma2Stream1.IrqHandlerSubject);
}
#endif //DMA2_STREAM1_USE 

#ifdef DMA2_STREAM2_USE  
void DMA2_Stream2_IRQHandler()
{
   dma2Stream2.IrqHandler(dma2Stream2.IrqHandlerSubject);
}
#endif //DMA2_STREAM1_USE 

#ifdef DMA2_STREAM3_USE  
void DMA2_Stream3_IRQHandler()
{
   dma2Stream3.IrqHandler(dma2Stream3.IrqHandlerSubject);
}
#endif //DMA2_STREAM3_USE 

#ifdef DMA2_STREAM4_USE  
void DMA2_Stream4_IRQHandler()
{
   dma2Stream4.IrqHandler(dma2Stream4.IrqHandlerSubject);
}
#endif //DMA1_STREAM4_USE 

#ifdef DMA2_STREAM5_USE  
void DMA2_Stream5_IRQHandler()
{
   dma2Stream5.IrqHandler(dma2Stream5.IrqHandlerSubject);
}
#endif //DMA2_STREAM5_USE 

#ifdef DMA2_STREAM6_USE  
void DMA2_Stream6_IRQHandler()
{
   dma2Stream6.IrqHandler(dma2Stream6.IrqHandlerSubject);
}
#endif //DMA2_STREAM6_USE 

#ifdef DMA2_STREAM7_USE  
void DMA2_Stream7_IRQHandler()
{
   dma2Stream7.IrqHandler(dma2Stream7.IrqHandlerSubject);
}
#endif //DMA2_STREAM7_USE 

