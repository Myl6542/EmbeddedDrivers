//******************************************************************************
// ��� �����    :  'M25P128.�'
// ���������    :  ������� ����-������ M25P128
// �����        :  
// ��������     :  
// ����         :  16.04.2019
//******************************************************************************

#include <stdlib.h> 
#include "M25P128.h"

#define MAX_DRIVERS 10

typedef struct
{
	int drv_id;
	sM25P128 drv_buffer;
}sDrv_t;

typedef struct
{
	int drivers_quantity;
	sDrv_t drivers[MAX_DRIVERS]
}sDrivers_t;

static sDrivers_t drv;

//==============================================================================
//                  ���������
//==============================================================================

    #define     CMD_WRITE       0x02
    #define     CMD_READ        0x03
    #define     CMD_RDSR        0x05   
    #define     CMD_WREN        0x06
    #define     CMD_SE          0xD8  
    #define     CMD_BE          0xC7

//�������� ���������� �� ����� ������������� ��������
static int check_drv_id(DRIVER_ID_t id)
{
	
}
//���������� �������
static sM25P128 * get_drv(DRIVER_ID_t id)
{
	
}	
//������������� ��������
int M25P128DrvInit(sM25P128 * drv, int id)
{
	if (check_drv_id(id) != 0)
		return -1;
	drv.drivers_quantity++;
	drv.drivers = drv;
}
//==============================================================================
//                 ���������� ������ 
//------------------------------------------------------------------------------
// flash        - ����-������
//==============================================================================   

inline static void WriteEnable (sM25P128* flash)
{
        flash->ResetPinCs();
        flash->SendByte(CMD_WREN);
        flash->SetPinCs();
}

//==============================================================================
//                 �������� ���������� ������
//------------------------------------------------------------------------------
// flash        - ����-������
//============================================================================== 

inline static void WaitEndWrite (sM25P128* flash)
{
    flash->ResetPinCs();
    
    flash->SendByte(CMD_RDSR);
    
    uint8_t flashStatus = 0;
    uint32_t endWriteTimer = *flash->pTimerMs;
    do
    {
        flashStatus = flash->ReceiveByte();
    }
    while((flashStatus & 0x01) && ((*flash->pTimerMs - endWriteTimer) < 5000));
    
    flash->SetPinCs();    
}
    
//==============================================================================
//                          ������� ����������
//------------------------------------------------------------------------------
// cmd          - �������
// address      - �����
// flash        - ����-������
//============================================================================== 

inline static void SendInstruction (uint8_t cmd, uint32_t address, sM25P128 * flash)
{
    flash->SendByte(cmd);
    flash->SendByte((address & 0xFF0000) >> 16);
    flash->SendByte((address & 0xFF00) >> 8);
    flash->SendByte(address & 0xFF);
}
    
//==============================================================================
//                  �������������
//------------------------------------------------------------------------------
// flash        - ����-������
//==============================================================================   
    
void InitM25P128 (sM25P128 * flash)
{
    flash->SetPinCs();
    
    if(flash->SetPinHold)
        flash->SetPinHold();
    
    if(flash->SetPinWr)
        flash->SetPinWr();    
}

//==============================================================================
//                  ������ ����
//------------------------------------------------------------------------------
// buffer       - �����
// address      - ����� � ������
// bytesCount   - ���-�� �������� ����
// flash        - ����-������
//==============================================================================  

void M25P128ReadBytes (uint8_t* buffer, uint32_t address, uint16_t bytesCount, sM25P128 * flash)
{
    flash->ResetPinCs();
    
    SendInstruction(CMD_READ, address, flash);
    
    for(uint8_t i = 0; i < bytesCount; i++)
        buffer[i] = flash->ReceiveByte(); 
    
    flash->SetPinCs();   
}

//==============================================================================
//                  ������ ����
//------------------------------------------------------------------------------
// buffer       - �����
// address      - ����� � ������
// bytesCount   - ���-�� ������������ ����
// flash        - ����-������
//==============================================================================  

void M25P128WriteBytes (uint8_t* buffer, uint32_t address, uint16_t bytesCount, sM25P128 * flash)
{   
    WriteEnable(flash);
    flash->ResetPinCs();
    
    SendInstruction(CMD_WRITE, address, flash);
    
    for(uint16_t i = 0; i < bytesCount; i++)
        flash->SendByte(buffer[i]);
    
    flash->SetPinCs();
    
    WaitEndWrite(flash);   
    
    uint8_t* temp;
    temp = calloc(bytesCount, sizeof(uint8_t)); 
    M25P128ReadBytes(temp, address, bytesCount, flash);
    
    uint8_t succses = 1;
    for(uint8_t i = 0; i < bytesCount; i++)
        if(buffer[i] != temp[i])
            succses = 0;
    
    free(temp); 
    
    if(!succses)
        M25P128WriteBytes (buffer, address, bytesCount, flash); 
}

//==============================================================================
//                  ������ �������� (16 bit)
//------------------------------------------------------------------------------
// buffer       - �����
// address      - ����� � ������
// bytesCount   - ���-�� �������� ��������
// flash        - ����-������
//==============================================================================  

void M25P128ReadHalfwords (uint16_t* buffer, uint32_t address, uint16_t halfwordsCount, sM25P128* flash)
{
    flash->ResetPinCs();
    
    SendInstruction(CMD_READ, address, flash);
    
    for(uint8_t i = 0; i < halfwordsCount; i++)
    {
        uint8_t highByte = flash->ReceiveByte(); 
        uint8_t lowByte  = flash->ReceiveByte(); 
        buffer[i] = (((uint16_t)(highByte << 8)) | lowByte);  
    }
    
    flash->SetPinCs();     
    
}

//==============================================================================
//                  ������ �������� (16 bit)
//------------------------------------------------------------------------------
// buffer       - �����
// address      - ����� � ������
// bytesCount   - ���-�� ������������ ��������
// flash        - ����-������
//==============================================================================  

void M25P128WriteHalfwords (uint16_t* buffer, uint32_t address, uint16_t halfwordsCount, sM25P128* flash)
{   
    WriteEnable(flash);
    flash->ResetPinCs();
    
    SendInstruction(CMD_WRITE, address, flash);
    
    for(uint16_t i = 0; i < halfwordsCount; i++)
    {
        uint8_t highByte = buffer[i] >> 8;
        uint8_t lowByte  = buffer[i] & 0xFF;
        flash->SendByte(highByte);
        flash->SendByte(lowByte);        
    }
    
    flash->SetPinCs();
    
    WaitEndWrite(flash);  
    
    uint16_t* temp;
    temp = calloc(halfwordsCount, sizeof(uint16_t)); 
    M25P128ReadHalfwords(temp, address, halfwordsCount, flash);
    
    uint8_t succses = 1;
    for(uint8_t i = 0; i < halfwordsCount; i++)
        if(buffer[i] != temp[i])
            succses = 0;
    
    free(temp);
    
    if(!succses)
        M25P128WriteHalfwords(buffer, address, halfwordsCount, flash); 
}

//==============================================================================
//                 ������ �������������� 
//------------------------------------------------------------------------------
// flash        - ����-������
//==============================================================================   

uint32_t M25P128ReadID (sM25P128* flash)
{
    uint32_t id;
  
    flash->ResetPinCs();
    
    flash->SendByte(0x9F);
    
    id = flash->ReceiveByte() << 16;
    id |= flash->ReceiveByte() << 8;
    id |= flash->ReceiveByte();
    
    flash->SetPinCs();
    
    return id;
}

//==============================================================================
//                  ������� �����
//------------------------------------------------------------------------------
// flash        - ����-������
//==============================================================================   

void M25P128EraseBulk (sM25P128* flash)
{  
    WriteEnable(flash);
   
    flash->ResetPinCs();
    
    flash->SendByte(CMD_BE);
    
    flash->SetPinCs();
    
    WaitEndWrite(flash);
}
    
//==============================================================================
//                  ������� �������
//------------------------------------------------------------------------------
// address      - ����� �������
// flash        - ����-������
// needCheck    true - ��������� �������� ��������
//==============================================================================   

void M25P128EraseSector (uint32_t address, sM25P128* flash, uint8_t needCheck)
{       
    WriteEnable(flash);
    
    flash->ResetPinCs();
    
    SendInstruction(CMD_SE, address, flash);
    
    flash->SetPinCs();
    
    if(needCheck)
        WaitEndWrite(flash);   
}

//==============================================================================
//                  ���������� ������ �� ������
//------------------------------------------------------------------------------
// flash        - ����-������
//==============================================================================  
void M25P128SetWriteProtected (sM25P128 * flash)
{
    flash->ResetPinWr();
}

//==============================================================================
//                  ������ ������ �� ������
//------------------------------------------------------------------------------
// flash        - ����-������
//==============================================================================  
void M25P128ResetWriteProtected (sM25P128 * flash)
{
    flash->SetPinWr();
}