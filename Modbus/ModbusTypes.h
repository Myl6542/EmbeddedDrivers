#ifndef MODBUS_TYPES_H_
#define MODBUS_TYPES_H_

typedef struct
{
    uint16_t value;
    uint16_t min;
    uint16_t max;
}sHoldingRegister_t;

typedef enum
{
    INPUT_REGISTER,
    HOLDING_REGISTER,
}eREGISTER_TYPE_t;

//UNUSED!!!
typedef enum
{
    OK_MDB_SLAVE                  = 0,
    NO_PACKAGE_RECEIVED_MDB_SLAVE = -1,
    CRC_ERROR_MDB_SLAVE           = -2,
    ADDRESS_ERROR_MDB_SLAVE       = -3,
    ERROR_CONFIGURATION_MDB_SLAVE = -5,
}MODBUS_SLAVE_ERROR_CODES_t;

typedef enum
{
    // команда чтени€ значений из нескольких регистров флагов
    READ_COIL_STATUS_COMMAND_MBS        = 0x01,    
    // команда чтени€ значений из нескольких дискретных входов
     READ_DISCRETE_INPUTS_COMMAND_MBS   = 0x02,
    // команда чтени€ значений из нескольких регистров хранени€
     READ_MULT_HOLDING_REG_COMMAND_MBS  = 0x03,
    // команда чтени€ значений из нескольких регистров ввода
     READ_MULT_INPUT_REG_COMMAND_MBS    = 0x04,
    // команда записи значени€ одного флага
     WRITE_ONE_COIL_COMMAND_MBS         = 0x05,
    // команда записи значени€ в один регистр хранени€
     WRITE_ONE_HOLDING_REG_COMMAND_MBS  = 0x06,
    // команда записи значений в несколько регистров флагов
     WRITE_MULT_COILS_COMMAND_MBS       = 0x0F,
    // команда записи значений в несколько регистров хранени€
     WRITE_MULT_HOLDING_REG_COMMAND_MBS = 0x10,
}eMODBUS_COMMANDS_t;

typedef enum 
{
    // ошибка: ѕрин€тый код функции не может быть обработан
    ILLEGAL_FUNCTION_ERROR_MBS            =  0x01,  
    // ошибка: јдрес данных, указанный в запросе, не доступен
    ILLEGAL_DATA_ADDRESS_ERROR_MBS        =  0x02,   
    // ошибка: ¬еличина устанавливаема€ в регистр недопустима
    ILLEGAL_DATA_VALUE                    =  0x03,        
}eERROR_CODES_t;


typedef enum
{
    MODBUS_ERROR = 0,
    MODBUS_OK = 1, 
}eMODBUS_RESULT_t;

#endif