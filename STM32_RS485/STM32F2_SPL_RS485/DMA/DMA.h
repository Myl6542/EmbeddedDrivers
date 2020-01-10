//******************************************************************************
// Имя файла    :  'DMA.h'
// заголовок    :  Модул DMA (F4)
// Автор        :  Маньянов Р.Р.
// Контакты     :  manianov.rus@gmail.com
// Дата         :  28.07.2015
//******************************************************************************

#ifndef __DMA_H
#define __DMA_H

#include "stm32F2xx.h" 

    typedef enum
    {
        DMA_FLAG_FEIF,                 
        DMA_FLAG_DMEIF,                 
        DMA_FLAG_TEIF,                    
        DMA_FLAG_HTIF,                   
        DMA_FLAG_TCIF,                   
    } sDmaFlag;

    typedef struct DMA
    {
        uint32_t                rcc;   
        DMA_Stream_TypeDef*     channelStream;
        DMA_InitTypeDef         definitions;    
        NVIC_InitTypeDef        nvicStruct;
        void                    (*IrqHandler)(void * subject);    // внешний обработчик прерывания приёма пакета
        void*                   IrqHandlerSubject;
    } sDma;

    void DMAInit (uint32_t buffer, uint32_t peripheral, uint32_t size, sDma* dma);
    void DMACmd (FunctionalState NewState, sDma* dma);
    uint16_t DMAGetCurrDataCounter (sDma* dma);
    void DMASetCurrDataCounter (uint32_t dataCounter, sDma* dma);
    void DMAConfigInterupt(uint32_t irqMask, FunctionalState NewState, sDma* dma);
    void DMASetExternalIrqHandler(void (*handler)(), void* handlerSubject, sDma* dma);
    void DMAClearFlag (sDmaFlag flag, sDma* dma);
    
#endif // __DMA_H 