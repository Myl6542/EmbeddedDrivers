//******************************************************************************
// ��� �����    :  'DMA.h'
// ���������    :  ����� DMA (F1)
// �����        :  �������� �.�.
// ��������     :  manianov.rus@gmail.com
// ����         :  27.07.2015
//******************************************************************************

#ifndef __DMA_H
#define __DMA_H

#include "stm32F10x.h" 

    typedef struct DMA
    {
        uint32_t                rcc;    
        DMA_Channel_TypeDef*    channel; 
        DMA_InitTypeDef         definitions;    
    } sDma;

void DMAInit (uint32_t buffer, uint32_t size, sDma* dma);

#endif // __DMA_H 