//******************************************************************************
// ��� �����    :  'M25P128.h'
// ���������    :  ������� ����-������ M25P128
// �����        :
// ��������     :  
// ����         :  16.04.2019
//******************************************************************************

#ifndef __M25P128_H
#define __M25P128_H

#include <stdint.h>

//==============================================================================
//                      ��������� � ����
//==============================================================================

	typedef enum
	{
		DRIVER_NAME_1 = 0,
		DRIVER_NAME_2 = 1,
		DRIVER_NAME_3 = 2,
		DRIVER_NAME_4 = 3,
		DRIVER_NAME_5 = 4,
		DRIVER_NAME_6 = 5,
	};

    // ��������� ����-������
    typedef struct 
    {   
        uint8_t             (*ReceiveByte) (void);
        void                (*SendByte) (uint8_t byte);
        
        void                (*SetPinCs) (void);
        void                (*ResetPinCs) (void);
        
        void                (*SetPinHold) (void);
        void                (*ResetPinHold) (void);
        
        void                (*SetPinWr) (void);
        void                (*ResetPinWr) (void);
        
        uint32_t            *pTimerMs;
    }sM25P128;

//==============================================================================
//                  ��������� �������
//==============================================================================
    void M25P128DrvInit(sM25P128 * drv, DRIVER_ID_t); 
	 
    // ������������� ����-������
    void M25P128Init (sM25P128* flash
	
	// ������������� ����-������
    void M25P128InitAll (sM25P128* flash);
    
    // ������� �������
    void M25P128EraseSector (uint32_t address, sM25P128* flash, uint8_t needCheck);
    
    // ������� �����
    void M25P128EraseBulk (sM25P128* flash);
        
    // ������ ����
    void M25P128ReadBytes (uint8_t* buffer, uint32_t address, uint16_t bytesCount, sM25P128* flash);
    
    // ������ ����
    void M25P128WriteBytes (uint8_t* buffer, uint32_t address, uint16_t bytesCount, sM25P128* flash);
          
    // ������ ��������
    void M25P128ReadHalfwords (uint16_t* buffer, uint32_t address, uint16_t halfwordsCount, sM25P128* flash);
        
    // ������ ��������
    void M25P128WriteHalfwords (uint16_t* buffer, uint32_t address, uint16_t halfwordsCount, sM25P128* flash);     
          
    // ������ ��������������
    uint32_t M25P128ReadID (sM25P128* flash);
    
    // ���������� ������ �� ������
    void M25P128SetWriteProtected (sM25P128 * flash);
    
    // ������ ������ �� ������
    void M25P128ResetWriteProtected (sM25P128 * flash);
    
#endif //__M25P128_H