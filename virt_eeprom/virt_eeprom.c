#include "virt_eeprom.h"


uint16_t * VirtAddressesTab = NULL;

static uint16_t VDataVar = 0;


static FlashDrv_t * current_drv;

enum
{
    DRIVER_INITED = 0,
    DRIVER_NOT_INITED = 1,
}DRIVER_STATE_t;

static FlashVirtualMem_t FlashMemoryDrv[MAX_FLASH_DRIVERS] = 
{
    NULL,
};

static int drivers_quantity = 0;





/*динамические настройки*/
static uint32_t VEEPROM_PAGE_SIZE =  0x00;
static uint32_t VEEPROM_START_ADDRESS = 0x00;

/* Pages 0 and 1 base and end addresses */
static uint32_t VPAGE0_BASE_ADDRESS =   0x00;//((uint32_t)(VEEPROM_START_ADDRESS + 0x0000));
static uint32_t VPAGE0_END_ADDRESS  =   0x00;//((uint32_t)(VEEPROM_START_ADDRESS + (VEEPROM_PAGE_SIZE - 1)));

static uint32_t VPAGE1_BASE_ADDRESS =   0x00;//((uint32_t)(VEEPROM_START_ADDRESS + VEEPROM_PAGE_SIZE));
static uint32_t VPAGE1_END_ADDRESS  =   0x00;//((uint32_t)(VEEPROM_START_ADDRESS + (2 * VEEPROM_PAGE_SIZE - 1)));

//реальный размер страницы
static uint32_t VEEPROM_REAL_PAGE_SIZE = 0x00;

/* максимальное кол-во виртуальных адресов */
static uint32_t VNB_OF_VAR = 0x00;//((uint8_t)10);









/*статичные настройки*/
/*состояние страницы*/
#define VERASED                ((uint16_t)0xFFFF)     /* страница чистая */
#define VRECEIVE_DATA          ((uint16_t)0xEEEE)     /* страница принимает данные */
#define VVALID_PAGE            ((uint16_t)0x0000)     /* страница сожержит правильные данные */


/* Used Flash pages for EEPROM emulation */
#define VPAGE0                 ((uint16_t)0x0000)
#define VPAGE1                 ((uint16_t)0x0001)

/*Идентификаторы страниц*/
#define VPAGE1_ID               0x00
#define VPAGE0_ID               0x01

/* Нет правильной страницы */
#define VNO_VALID_PAGE         ((uint16_t)0x00AB)


/* Valid pages in read and write defines */
#define VREAD_FROM_VALID_PAGE  ((uint8_t)0x00)
#define VWRITE_IN_VALID_PAGE   ((uint8_t)0x01)

/* Страница заполнена */
#define VPAGE_FULL             ((uint8_t)0x80)






static uint16_t VEE_FindValidPage(uint8_t Operation);

static uint16_t VEE_VerifyPageFullWriteVariable(uint16_t VirtAddress, uint16_t Data)
{
  int FlashStatus = 0;
  uint16_t ValidPage = VPAGE0;
  uint32_t Address = VEEPROM_START_ADDRESS, PageEndAddress = VEEPROM_START_ADDRESS+VEEPROM_PAGE_SIZE;

  /* Get valid Page for write operation */
  ValidPage = VEE_FindValidPage(VWRITE_IN_VALID_PAGE);

  /* Check if there is no valid page */
  if (ValidPage == VNO_VALID_PAGE)
  {
    return  VNO_VALID_PAGE;
  }

  if ( ValidPage == 0 )
  {
      /* Get the valid Page start Address */
      Address = (uint32_t)VPAGE0_BASE_ADDRESS;
      /* Get the valid Page end Address */
      PageEndAddress = (uint32_t)(VPAGE0_BASE_ADDRESS + VEEPROM_PAGE_SIZE - 2);//((VEEPROM_START_ADDRESS - 2) + (uint32_t)(VEEPROM_PAGE_SIZE));
  }
  else if ( ValidPage == 1 )
  {
      /* Get the valid Page start Address */
      Address = (uint32_t)(VPAGE1_BASE_ADDRESS);
      /* Get the valid Page end Address */
      PageEndAddress = (uint32_t)(VPAGE1_BASE_ADDRESS + VEEPROM_PAGE_SIZE - 2);
  }
  
  
  /* Check each active page address starting from begining */
  while (Address < PageEndAddress)
  {
    uint32_t w = current_drv->read_word(Address);
    /* Verify if Address and Address+2 contents are 0xFFFFFFFF */
    if ( w == 0xFFFFFFFF )
    {
      /* Set variable data */
      FlashStatus = current_drv->write_half_word(Address, Data); //FLASH_ProgramHalfWord(Address, Data);
      /* If program operation was failed, a Flash error code is returned */
      if (FlashStatus != 0)
      {
        return FlashStatus;
      }
      /* Set variable virtual address */
      FlashStatus = current_drv->write_half_word(Address + 2, VirtAddress);//FLASH_ProgramHalfWord(Address + 2, VirtAddress);
      /* Return program operation status */
      return FlashStatus;
    }
    else
    {
      /* Next address location */
      Address = Address + 4;
    }
  }

  /* Return PAGE_FULL in case the valid page is full */
  return VPAGE_FULL;
}










static uint16_t VEE_FindValidPage(uint8_t Operation)
{
  uint16_t PageStatus0 = 6, PageStatus1 = 6;

  /* Get Page0 actual status */
  PageStatus0 = (uint16_t)current_drv->read_half_word(VPAGE0_BASE_ADDRESS); //(*(__IO uint16_t*)PAGE0_BASE_ADDRESS);

  /* Get Page1 actual status */
  PageStatus1 = (uint16_t)current_drv->read_half_word(VPAGE1_BASE_ADDRESS);//(*(__IO uint16_t*)PAGE1_BASE_ADDRESS);

  /* Write or read operation */
  switch (Operation)
  {
    case VWRITE_IN_VALID_PAGE:   /* ---- Write operation ---- */
      if (PageStatus1 == VVALID_PAGE)
      {
        /* Page0 receiving data */
        if (PageStatus0 == VRECEIVE_DATA)
        {
          return VPAGE0;         /* Page0 valid */
        }
        else
        {
          return VPAGE1;         /* Page1 valid */
        }
      }
      else if (PageStatus0 == VVALID_PAGE)
      {
        /* Page1 receiving data */
        if (PageStatus1 == VRECEIVE_DATA)
        {
          return VPAGE1;         /* Page1 valid */
        }
        else
        {
          return VPAGE0;         /* Page0 valid */
        }
      }
      else
      {
        return VNO_VALID_PAGE;   /* No valid Page */
      }

    case VREAD_FROM_VALID_PAGE:  /* ---- Read operation ---- */
      if (PageStatus0 == VVALID_PAGE)
      {
        return VPAGE0;           /* Page0 valid */
      }
      else if (PageStatus1 == VVALID_PAGE)
      {
        return VPAGE1;           /* Page1 valid */
      }
      else
      {
        return VNO_VALID_PAGE ;  /* No valid Page */
      }

    default:
      return VPAGE0;             /* Page0 valid */
  }
}




static int VEE_ReadVariable(uint16_t VirtAddress, uint16_t* Data)
{
  uint16_t ValidPage = VPAGE0;
  uint16_t AddressValue = 0x5555, ReadStatus = -1;
  uint32_t Address = VEEPROM_START_ADDRESS, PageStartAddress = VEEPROM_START_ADDRESS;

  /* Get active Page for read operation */
  ValidPage = VEE_FindValidPage(VREAD_FROM_VALID_PAGE);

  /* Check if there is no valid page */
  if (ValidPage == VNO_VALID_PAGE)
  {
    return  VNO_VALID_PAGE;
  }

  if ( ValidPage == 0 )
  {
      /* Get the valid Page start Address */
      PageStartAddress = (uint32_t)VPAGE0_BASE_ADDRESS;
      /* Get the valid Page end Address */
      Address = (uint32_t)(VPAGE0_BASE_ADDRESS + VEEPROM_PAGE_SIZE - 2);//((VEEPROM_START_ADDRESS - 2) + (uint32_t)(VEEPROM_PAGE_SIZE));
  }
  else if ( ValidPage == 1 )
  {
      /* Get the valid Page start Address */
      PageStartAddress = (uint32_t)(VPAGE1_BASE_ADDRESS);
      /* Get the valid Page end Address */
      Address = (uint32_t)(VPAGE1_BASE_ADDRESS + VEEPROM_PAGE_SIZE - 2);
  }
  
  /* Check each active page address starting from end */
  while (Address > (PageStartAddress + 2))
  {
    /* Get the current location content to be compared with virtual address */
    AddressValue = (uint16_t)current_drv->read_half_word(Address);//(*(__IO uint16_t*)Address);

    /* Compare the read address with the virtual address */
    if (AddressValue == VirtAddress)
    {
      /* Get content of Address-2 which is variable value */
      *Data = (uint16_t)current_drv->read_half_word(Address - 2);//(*(__IO uint16_t*)(Address - 2));

      /* In case variable value is read, reset ReadStatus flag */
      ReadStatus = 0;

      break;
    }
    else
    {
      /* Next address location */
      Address = Address - 4;
    }
  }

  /* Return ReadStatus value: (0: variable exist, 1: variable doesn't exist) */
  return ReadStatus;
}






static int VEE_Format(void)
{
  int FlashStatus = 0;

  /* Erase Page0 */
  FlashStatus = current_drv->erase_page_0( );

  /* If erase operation was failed, a Flash error code is returned */
  if (FlashStatus != 0)
  {
    return FlashStatus;
  }

  /* Set Page0 as valid page: Write VALID_PAGE at Page0 base address */
  FlashStatus = current_drv->write_half_word( VPAGE0_BASE_ADDRESS, VVALID_PAGE); //FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, VALID_PAGE);

  /* If program operation was failed, a Flash error code is returned */
  if (FlashStatus != 0)
  {
    return FlashStatus;
  }

  /* Erase Page1 */
  FlashStatus = current_drv->erase_page_1( );//FLASH_EraseSector(PAGE1_ID, VOLTAGE_RANGE);

  /* Return Page1 erase operation status */
  return FlashStatus;
}










//инициализация виртуальной памяти
static int V_EE_Init(void)
{
  uint16_t PageStatus0 = 6, PageStatus1 = 6;
  uint16_t VarIdx = 0;
  uint16_t EepromStatus = 0, ReadStatus = 0;
  int16_t x = -1;
  uint16_t  FlashStatus;

  /* Get Page0 status */
  PageStatus0 = (uint16_t)current_drv->read_half_word(VPAGE0_BASE_ADDRESS);//(*(__IO uint16_t*)PAGE0_BASE_ADDRESS);
  /* Get Page1 status */
  PageStatus1 = (uint16_t)current_drv->read_half_word(VPAGE1_BASE_ADDRESS);//(*(__IO uint16_t*)PAGE1_BASE_ADDRESS);

  /* Check for invalid header states and repair if necessary */
  switch (PageStatus0)
  {
    case VERASED:
    {
        if (PageStatus1 == VVALID_PAGE) /* Page0 erased, Page1 valid */
        {
          /* Erase Page0 */
          FlashStatus = current_drv->erase_page_0();//FLASH_EraseSector(PAGE0_ID,VOLTAGE_RANGE);
          /* If erase operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        else if (PageStatus1 == VRECEIVE_DATA) /* Page0 erased, Page1 receive */
        {
          /* Erase Page0 */
          FlashStatus = current_drv->erase_page_0();//FLASH_EraseSector(PAGE0_ID, VOLTAGE_RANGE);
          /* If erase operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
          /* Mark Page1 as valid */
          FlashStatus = current_drv->write_half_word(VPAGE1_BASE_ADDRESS, VVALID_PAGE); //FLASH_ProgramHalfWord(PAGE1_BASE_ADDRESS, VALID_PAGE);
          /* If program operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        else /* First EEPROM access (Page0&1 are erased) or invalid state -> format EEPROM */
        {
          /* Erase both Page0 and Page1 and set Page0 as valid page */
          FlashStatus = VEE_Format();
          /* If erase/program operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        break;

    }
    
    case VRECEIVE_DATA:
    {
        if (PageStatus1 == VVALID_PAGE) /* Page0 receive, Page1 valid */
        {
          /* Transfer data from Page1 to Page0 */
          for (VarIdx = 0; VarIdx < VNB_OF_VAR; VarIdx++)
          {
            uint16_t data = (uint16_t)current_drv->read_half_word(VPAGE0_BASE_ADDRESS + 6); //*(__IO uint16_t*)(PAGE0_BASE_ADDRESS + 6);
            if (data == VirtAddressesTab[VarIdx])
            {
              x = VarIdx;
            }
            if (VarIdx != x)
            {
              /* Read the last variables' updates */
              ReadStatus = VEE_ReadVariable(VirtAddressesTab[VarIdx], &VDataVar);
              /* In case variable corresponding to the virtual address was found */
              if (ReadStatus != 0x1)
              {
                /* Transfer the variable to the Page0 */
                EepromStatus = VEE_VerifyPageFullWriteVariable(VirtAddressesTab[VarIdx], VDataVar);
                /* If program operation was failed, a Flash error code is returned */
                if (EepromStatus != 0)
                {
                  return EepromStatus;
                }
              }
            }
          }
          /* Mark Page0 as valid */
          FlashStatus = current_drv->read_half_word( VPAGE0_BASE_ADDRESS );//FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, VALID_PAGE);
          /* If program operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
          /* Erase Page1 */
          FlashStatus = current_drv->erase_page_1();//FLASH_EraseSector(PAGE1_ID, VOLTAGE_RANGE);
          /* If erase operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        else if (PageStatus1 == VERASED) /* Page0 receive, Page1 erased */
        {
          /* Erase Page1 */
          FlashStatus = current_drv->erase_page_1();//FLASH_EraseSector(PAGE1_ID, VOLTAGE_RANGE);
          /* If erase operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
          /* Mark Page0 as valid */
          FlashStatus = current_drv->write_half_word(VPAGE0_BASE_ADDRESS, VVALID_PAGE);//FLASH_ProgramHalfWord(PAGE0_BASE_ADDRESS, VALID_PAGE);
          /* If program operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        else /* Invalid state -> format eeprom */
        {
          /* Erase both Page0 and Page1 and set Page0 as valid page */
          FlashStatus = VEE_Format();
          /* If erase/program operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        break;
    }
    case VVALID_PAGE:
    {
        if (PageStatus1 == VVALID_PAGE) /* Invalid state -> format eeprom */
        {
          /* Erase both Page0 and Page1 and set Page0 as valid page */
          FlashStatus = VEE_Format();
          /* If erase/program operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        else if (PageStatus1 == VERASED) /* Page0 valid, Page1 erased */
        {
          /* Erase Page1 */
          FlashStatus = current_drv->erase_page_1();//FLASH_EraseSector(PAGE1_ID, VOLTAGE_RANGE);
          /* If erase operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        else /* Page0 valid, Page1 receive */
        {
          /* Transfer data from Page0 to Page1 */
          for (VarIdx = 0; VarIdx < VNB_OF_VAR; VarIdx++)
          {
            uint16_t data = current_drv->read_half_word(VPAGE1_BASE_ADDRESS + 6);
            if ( data == VirtAddressesTab[VarIdx] )
            {
              x = VarIdx;
            }
            if (VarIdx != x)
            {
              /* Read the last variables' updates */
              ReadStatus = VEE_ReadVariable(VirtAddressesTab[VarIdx], &VDataVar);
              /* In case variable corresponding to the virtual address was found */
              if (ReadStatus != 0x1)
              {
                /* Transfer the variable to the Page1 */
                EepromStatus = VEE_VerifyPageFullWriteVariable(VirtAddressesTab[VarIdx], VDataVar);
                /* If program operation was failed, a Flash error code is returned */
                if (EepromStatus != 0)
                {
                  return EepromStatus;
                }
              }
            }
          }
          /* Mark Page1 as valid */
          FlashStatus = current_drv->write_half_word(VPAGE1_BASE_ADDRESS, VVALID_PAGE);
          /* If program operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
          /* Erase Page0 */
          FlashStatus = current_drv->erase_page_0();//FLASH_EraseSector(PAGE0_ID, VOLTAGE_RANGE);
          /* If erase operation was failed, a Flash error code is returned */
          if (FlashStatus != 0)
          {
            return FlashStatus;
          }
        }
        break;
    }
    default:
    {
         /* Any other state -> format eeprom */
        /* Erase both Page0 and Page1 and set Page0 as valid page */
        FlashStatus =VEE_Format();
        /* If erase/program operation was failed, a Flash error code is returned */
        if (FlashStatus != 0)
        {
          return FlashStatus;
        }
        break;
    }
  }

  return 0;
}



static uint16_t VEE_PageTransfer(uint16_t VirtAddress, uint16_t Data)
{
  int FlashStatus = 0;
  uint32_t NewPageAddress = VEEPROM_START_ADDRESS;
  uint16_t OldPageId = 0;
  uint16_t ValidPage = VPAGE0, VarIdx = 0;
  uint16_t EepromStatus = 0, ReadStatus = 0;

  /* Get active Page for read operation */
  ValidPage = VEE_FindValidPage(VREAD_FROM_VALID_PAGE);

  if (ValidPage == VPAGE1)       /* Page1 valid */
  {
    /* New page address where variable will be moved to */
    NewPageAddress = VPAGE0_BASE_ADDRESS;

    /* Old page ID where variable will be taken from */
    OldPageId = VPAGE1_ID;
  }
  else if (ValidPage == VPAGE0)  /* Page0 valid */
  {
    /* New page address  where variable will be moved to */
    NewPageAddress = VPAGE1_BASE_ADDRESS;

    /* Old page ID where variable will be taken from */
    OldPageId = VPAGE0_ID;
  }
  else
  {
    return VNO_VALID_PAGE;       /* No valid Page */
  }

  /* Set the new Page status to RECEIVE_DATA status */
  FlashStatus = current_drv->write_half_word(NewPageAddress, VRECEIVE_DATA);//FLASH_ProgramHalfWord(NewPageAddress, RECEIVE_DATA);
  /* If program operation was failed, a Flash error code is returned */
  if (FlashStatus != 0)
  {
    return FlashStatus;
  }

  /* Write the variable passed as parameter in the new active page */
  EepromStatus = VEE_VerifyPageFullWriteVariable(VirtAddress, Data);
  /* If program operation was failed, a Flash error code is returned */
  if (EepromStatus != 0)
  {
    return EepromStatus;
  }

  /* Transfer process: transfer variables from old to the new active page */
  for (VarIdx = 0; VarIdx < VNB_OF_VAR; VarIdx++)
  {
    if (VirtAddressesTab[VarIdx] != VirtAddress)  /* Check each variable except the one passed as parameter */
    {
      /* Read the other last variable updates */
      ReadStatus = VEE_ReadVariable(VirtAddressesTab[VarIdx], &VDataVar);
      /* In case variable corresponding to the virtual address was found */
      if (ReadStatus != 0x1)
      {
        /* Transfer the variable to the new active page */
        EepromStatus = VEE_VerifyPageFullWriteVariable(VirtAddressesTab[VarIdx], VDataVar);
        /* If program operation was failed, a Flash error code is returned */
        if (EepromStatus != 0)
        {
          return EepromStatus;
        }
      }
    }
  }

  /* Erase the old Page: Set old Page status to ERASED status */
  //FLASH_EraseSector(OldPageId, VOLTAGE_RANGE);
  if ( OldPageId == VPAGE1_ID )
      FlashStatus = current_drv->erase_page_1();
  else if ( OldPageId == VPAGE0_ID )
      FlashStatus = current_drv->erase_page_0();
  /* If erase operation was failed, a Flash error code is returned */
  if (FlashStatus != 0)
  {
    return FlashStatus;
  }

  /* Set new Page status to VALID_PAGE status */
//  if ( NewPageAddress == VPAGE1_ID )
//      FlashStatus = current_drv->erase_page_1();
//  else if ( NewPageAddress == VPAGE0_ID )
//      FlashStatus = current_drv->erase_page_0();
  current_drv->write_half_word(NewPageAddress, VVALID_PAGE);//FLASH_ProgramHalfWord(NewPageAddress, VALID_PAGE);
  
  
  /* If program operation was failed, a Flash error code is returned */
  if (FlashStatus != 0)
  {
    return FlashStatus;
  }

  /* Return last operation flash status */
  return FlashStatus;
}



static int V_EE_WriteVariable(uint16_t VirtAddress, uint16_t Data)
{
      uint16_t Status = 0;

    /* Write the variable virtual address and value in the EEPROM */
    Status = VEE_VerifyPageFullWriteVariable(VirtAddress, Data);

    /* In case the EEPROM active page is full */
    if (Status == VPAGE_FULL)
    {
      /* Perform Page transfer */
      Status = VEE_PageTransfer(VirtAddress, Data);
    }

    /* Return last operation status */
    return Status;
}












static FlashVirtualMem_t * get_current_drv(int id)
{
    for (int i = 0; i < drivers_quantity; i++)
    {
        if ( FlashMemoryDrv[i].id == id )
            return &(FlashMemoryDrv[i]);
    }
    return NULL;
}


//проинициализировать конфгурацию
static int init_mem_conf(FlashConfiguration_t * conf)
{
    VirtAddressesTab = conf->VirtAddressesTab;
    
    VEEPROM_PAGE_SIZE = conf->page_size;
    VEEPROM_START_ADDRESS = conf->start_address_1;
    
    VNB_OF_VAR = conf->virt_addresses_quantity;
    
    VEEPROM_REAL_PAGE_SIZE = conf->real_page_size;
    
    VPAGE0_BASE_ADDRESS =   ((uint32_t)(conf->start_address_1));
    //VPAGE0_END_ADDRESS  =   ((uint32_t)(conf->end_address_1));
    
    VPAGE1_BASE_ADDRESS =   ((uint32_t)(conf->start_address_2));
    //VPAGE1_END_ADDRESS  =   ((uint32_t)(conf->end_address_2));  
    
//    VPAGE0_BASE_ADDRESS =   ((uint32_t)(VEEPROM_START_ADDRESS + 0x0000));
//    VPAGE0_END_ADDRESS  =   ((uint32_t)(VEEPROM_START_ADDRESS + (VEEPROM_PAGE_SIZE - 1)));
//    
//    VPAGE1_BASE_ADDRESS =   ((uint32_t)(VEEPROM_START_ADDRESS + VEEPROM_PAGE_SIZE));
//    VPAGE1_END_ADDRESS  =   ((uint32_t)(VEEPROM_START_ADDRESS + (2 * VEEPROM_PAGE_SIZE - 1)));
}


//добавить драйвер в список драйверов
int V_EE_AddDriver(FlashVirtualMem_t * f)
{
    if ( drivers_quantity >= MAX_FLASH_DRIVERS )
        return -1;
    if (f->conf.real_page_size < f->conf.page_size)
        return -1;
    drivers_quantity++;
    FlashMemoryDrv[drivers_quantity - 1].conf = f->conf;
    FlashMemoryDrv[drivers_quantity - 1].drv = f->drv;
    FlashMemoryDrv[drivers_quantity - 1].id = f->id;
    return 0;
}
//проинициализировать драйвер с заданным id
int V_EE_InitDriver( int drv_id )
{
    FlashVirtualMem_t * d = get_current_drv( drv_id );
    if ( d == NULL )
        return -1;
    current_drv = &(d->drv);
    init_mem_conf( &(d->conf) );
    V_EE_Init();
}
//проинициализировать все драйвера
int V_EE_InitAllDrivers(void)
{
    for ( int i = 0; i < drivers_quantity; i++ )
    {
        FlashVirtualMem_t * d = &(FlashMemoryDrv[i]);
        if ( d == NULL )
            return -1;
        current_drv = &(d->drv);
        init_mem_conf( &(d->conf) );
        V_EE_Init();
    }
}
//считать переменную по виртуальному адресу
int V_EE_ReadVar(uint16_t VirtAddress, uint16_t* Data, int drv_id)
{
    FlashVirtualMem_t * d = get_current_drv( drv_id );
    if ( d == NULL )
        return -1;
    current_drv = &(d->drv);
    init_mem_conf( &(d->conf) );
    int rc = VEE_ReadVariable(VirtAddress, Data);
    return rc;
}
//записать переменную по виртуальному адресу
int V_EE_WriteVar(uint16_t virt_address, uint16_t data, int drv_id)
{
    FlashVirtualMem_t * d = get_current_drv( drv_id );
    if ( d == NULL )
        return -1;
    current_drv = &(d->drv);
    init_mem_conf( &(d->conf) );
    int rc = V_EE_WriteVariable (virt_address, data);
    return rc;
}