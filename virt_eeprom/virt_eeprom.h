#ifndef VIRTUAL_EEPROM_H_
#define VIRTUAL_EEPROM_H_


#include "stdint.h"
#include "stddef.h"

//размер слова
typedef uint32_t DWORD_t;



/*максимальное кол-во используемых flash*/
#define MAX_FLASH_DRIVERS 3



typedef struct
{
    int (*write_word) (uint32_t address, uint32_t word);
    int (*write_half_word) (uint32_t address, uint16_t word);
    uint32_t ( *read_word )(uint32_t virt_address);
    uint32_t ( *read_half_word )(uint32_t virt_address);
    //очистка младшей страницы/сектора
    int (*erase_page_0)( );
    //очистка старшей страницы/сектора
    int (*erase_page_1)( );    
}FlashDrv_t;
typedef struct
{
    //реальный размер страницы сектора
    uint32_t real_page_size;
    //размер страницы
    uint32_t page_size;
    //стартовый адрес 1
    uint32_t start_address_1;
    //конечный адрес страницы 1
    //uint32_t end_address_1;
    //стартовый адрес 2
    uint32_t start_address_2;
    //конечный адрес страницы 2
    //uint32_t end_address_2;
    //кол-во вирутальных ардесов
    uint32_t virt_addresses_quantity;
    //буфер с виртуальными адресами
    uint16_t *VirtAddressesTab;
}FlashConfiguration_t;


typedef struct
{
    int id;
    FlashDrv_t drv;
    FlashConfiguration_t conf;
}FlashVirtualMem_t;


// "0" успешно
// "-1" не успешно
//добавить драйвер
int V_EE_AddDriver(FlashVirtualMem_t * f);
//проинициализировать драйвер с заданным id
int V_EE_InitDriver( int drv_id );
//проинициализировать все драйвера
int V_EE_InitAllDrivers(void);
//считать переменную по виртуальному адресу
int V_EE_ReadVar(uint16_t VirtAddress, uint16_t* Data, int drv_id);
//записать переменную по виртуальному адресу
int V_EE_WriteVar(uint16_t virt_address, uint16_t data, int drv_id);




#if 0
/******************************************/
//EXAMPLE OF USING VIRTUAL EEPROM DRIVER
/******************************************/
/*Virtual Flash Memory Functions*/
static int flash_write_half_word(uint32_t address, uint16_t value)
{
    FLASH_Unlock();
    FLASH_Status rc = FLASH_BUSY;
    rc = FLASH_ProgramHalfWord(address, value);
    FLASH_Lock();
    if (rc != FLASH_COMPLETE)
        return -1;
    return 0;
}
static DWORD_t flash_read_half_word( uint32_t address )
{
    return (uint32_t) (*(__IO uint16_t*)address);
}
static uint32_t flash_read_word ( uint32_t address )
{
    return (uint32_t) (*(__IO uint32_t*)address);
}
int erase_page_0()
{
    FLASH_Unlock();
    FLASH_Status rc = FLASH_BUSY;
    rc = FLASH_EraseSector(FLASH_Sector_10, (uint8_t)VoltageRange_3);
    FLASH_Lock();
    if (rc != FLASH_COMPLETE)
        return -1;
    return 0;
}
int erase_page_1()
{
    FLASH_Unlock();
    FLASH_Status rc = FLASH_BUSY;
    rc = FLASH_EraseSector(FLASH_Sector_11, (uint8_t)VoltageRange_3);
    FLASH_Lock();
    if (rc != FLASH_COMPLETE)
        return -1;
    return 0;
}
/**********************************/

/*external flash memory drv*/
static int flash_write_half_word_m25p128(uint32_t address, uint16_t value)
{
    uint8_t write_buffer[2];
    write_buffer[0] = (uint8_t) (value & 0xFF);
    write_buffer[1] = (uint8_t) ((((uint16_t)value) >>8) & 0xFF );
    WriteBytesM25P128(write_buffer, address, 2, &DD11Flash);
    return 0;
}
static DWORD_t flash_read_half_word_m25p128( uint32_t address )
{
    uint8_t read_buffer[2];
    ReadBytesM25P128(read_buffer, address, 2, &DD11Flash);
    uint32_t value = read_buffer[0] | ( ((uint16_t)read_buffer[1]) << 8);
    return value;
}
static uint32_t flash_read_word_m25p128 ( uint32_t address )
{
    uint8_t read_buffer[4];
    ReadBytesM25P128(read_buffer, address, 4, &DD11Flash);
    uint32_t value = read_buffer[0];
    value |= (((uint32_t)read_buffer[1]) << 8);
    value |= (((uint32_t)read_buffer[2]) << 16);
    value |= (((uint32_t)read_buffer[3]) << 24);
    return value;
}
int erase_page_0_m25p128()
{
    EraseSectorM25P128(0, &DD11Flash, 1);
    return 0;
}
int erase_page_1_m25p128()
{
    EraseSectorM25P128(0x040000, &DD11Flash, 1);
    return 0;
}
/***************************/

void DemoFunction()
{
    erase_page_0();
    erase_page_1();
    uint16_t VirtAddresses[10] = {1,2,3,4,5,6,7,8,9,10};
    FlashVirtualMem_t MemDrv;
    MemDrv.drv.erase_page_0 = &erase_page_0;
    MemDrv.drv.erase_page_1 = &erase_page_1;
    MemDrv.drv.read_half_word = &flash_read_half_word;
    MemDrv.drv.read_word = &flash_read_word;
    MemDrv.drv.write_half_word = &flash_write_half_word;
    MemDrv.drv.write_word = NULL;
    MemDrv.conf.real_page_size = 0x20000;
    MemDrv.conf.page_size = 0x14;
    MemDrv.conf.start_address_1 = 0x080C0000;
    MemDrv.conf.start_address_2 = MemDrv.conf.start_address_1 + MemDrv.conf.real_page_size;
    MemDrv.conf.VirtAddressesTab = VirtAddresses;
    MemDrv.conf.virt_addresses_quantity = 3;
    MemDrv.id = 1;
    
    //добавл€ем драйвер
    V_EE_AddDriver(&MemDrv);

    
    FlashVirtualMem_t externalMemDrv;
    uint16_t VirtAddresses_m25p128[10] = {1,2,3,4,5,6,7,8,9,10};
    externalMemDrv.drv.erase_page_0 = &erase_page_0_m25p128;
    externalMemDrv.drv.erase_page_1 = &erase_page_1_m25p128;
    externalMemDrv.drv.read_half_word = &flash_read_half_word_m25p128;
    externalMemDrv.drv.read_word = &flash_read_word_m25p128;
    externalMemDrv.drv.write_half_word = &flash_write_half_word_m25p128;
    externalMemDrv.drv.write_word = NULL;
    externalMemDrv.conf.real_page_size = 0x040000;
    externalMemDrv.conf.page_size = 0x14;
    externalMemDrv.conf.start_address_1 = 0x00;
    externalMemDrv.conf.start_address_2 = 0x040000;
    externalMemDrv.conf.VirtAddressesTab = VirtAddresses_m25p128;
    externalMemDrv.conf.virt_addresses_quantity = 3;
    externalMemDrv.id = 2;
    
    //добавл€ем драйвер
    V_EE_AddDriver(&externalMemDrv);
    //инициализируем все добавленнные драйвера
    V_EE_InitAllDrivers();
    
    //запись значений по умолчанию id драйвера 1(при первом запуске)
    for (int i = 0; i < externalMemDrv.conf.virt_addresses_quantity; i++)
    {
        V_EE_WriteVar(VirtAddresses[i], 0, 1);
    }
    
    //запись значений по умолчанию id драйвера 2(при первом запуске)
    for (int i = 0; i < externalMemDrv.conf.virt_addresses_quantity; i++)
    {
        V_EE_WriteVar(VirtAddresses_m25p128[i], 0, 2);
    }
    
    /*внутренн€ flash*/
    //записать по виртуальному адресу (используетс€ драйвер с id = 1)
    V_EE_WriteVar(VirtAddresses[0], 36, 1);
    V_EE_WriteVar(VirtAddresses[1], 25, 1);
    V_EE_WriteVar(VirtAddresses[2], 14, 1);
    
    int rc = 0;
    static uint16_t value1 = 0;
    static uint16_t value2 = 0;
    static uint16_t value3 = 0;
    
    //считать по виртуальному адресу (используетс€ драйвер с id = 1)
    rc = V_EE_ReadVar(VirtAddresses[0], &value1, 1);
    rc = V_EE_ReadVar(VirtAddresses[1], &value2, 1);
    rc = V_EE_ReadVar(VirtAddresses[2], &value3, 1);
    
    //записать по виртуальному адресу (используетс€ драйвер с id = 1)
    V_EE_WriteVar(VirtAddresses[0], 111, 1);
    V_EE_WriteVar(VirtAddresses[1], 222, 1);
    V_EE_WriteVar(VirtAddresses[2], 333, 1);
    
    //считать по виртуальному адресу (используетс€ драйвер с id = 1)
    rc = V_EE_ReadVar(VirtAddresses[0], &value1, 1);
    rc = V_EE_ReadVar(VirtAddresses[1], &value2, 1);
    rc = V_EE_ReadVar(VirtAddresses[2], &value3, 1);
    
    
    
    
    
    
    
    
    
    /*внешн€€ flash (m25p128) (используетс€ драйвер с id = 2)*/
    V_EE_WriteVar(VirtAddresses_m25p128[0], 36, 2);
    V_EE_WriteVar(VirtAddresses_m25p128[1], 25, 2);
    V_EE_WriteVar(VirtAddresses_m25p128[2], 14, 2);
    
    static uint16_t value1_m25p128 = 0;
    static uint16_t value2_m25p128 = 0;
    static uint16_t value3_m25p128 = 0;
    
    //считать по виртуальному адресу (используетс€ драйвер с id = 2)
    rc = V_EE_ReadVar(VirtAddresses_m25p128[0], &value1_m25p128, 2);
    rc = V_EE_ReadVar(VirtAddresses_m25p128[1], &value2_m25p128, 2);
    rc = V_EE_ReadVar(VirtAddresses_m25p128[2], &value3_m25p128, 2);
    //записать по виртуальному адресу (используетс€ драйвер с id = 2)
    V_EE_WriteVar(VirtAddresses_m25p128[0], 111, 2);
    V_EE_WriteVar(VirtAddresses_m25p128[1], 222, 2);
    V_EE_WriteVar(VirtAddresses_m25p128[2], 333, 2);
    //считать по виртуальному адресу (используетс€ драйвер с id = 2)
    rc = V_EE_ReadVar(VirtAddresses_m25p128[0], &value1_m25p128, 2);
    rc = V_EE_ReadVar(VirtAddresses_m25p128[1], &value2_m25p128, 2);
    rc = V_EE_ReadVar(VirtAddresses_m25p128[2], &value3_m25p128, 2);
}


#endif


#endif