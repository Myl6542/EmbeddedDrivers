#ifndef MODBUS_SLAVE_DEVICE_H_
#define MODBUS_SLAVE_DEVICE_H_

#include "IModbusRTU_CRC.h"
#include "IModbusRTUDriver.h"
#include "ModbusDriver/ModbusDriver.h"
#include "ModbusTypes.h"

#define MAX_INPUT_REGISTERS   100
#define MAX_HOLDING_REGISTERS 100

class ModbusSlaveDevice
{
public:
    ModbusSlaveDevice(uint16_t slave_id, int input_regs, int hold_regs);
    //���������� �������� ����� ��������
    int set_input_reg(uint16_t reg_num, uint16_t value);
    //���������� �������� ������� ��������
    int set_holding_reg(uint16_t reg_num, uint16_t value);
    //���������� ������
    int modbus_handler();
    //������� �������� ������� ��������
    uint16_t get_holding_reg_value (uint16_t reg_num);
    //���������� �������
    void set_driver (IModbusRTU_Driver * drv);
    //���������� �������� ����������� �����
    void set_crc (IModbusRTU_CRC * c);
private:
    //�������������� ��������� �������� ������
    IModbusRTU_Driver * interface;
    //�������� ������� crc
    IModbusRTU_CRC * crc;
    
    //����� ����� ����������
    uint16_t id;
    //������� ��������
    sHoldingRegister_t holdings_registers[MAX_HOLDING_REGISTERS];
    //���-�� ���������
    int hold_regs_quantity;
    //����� ��������
    uint16_t input_registers[MAX_INPUT_REGISTERS];
    //���-�� �������
    int input_regs_quantity;

    //��������� slave
    int mdb_slave_status;
    
    //��������� ��� ������
    void send_error(eERROR_CODES_t code, uint8_t * rx_buffer);
    //������� �������( ��������� ������� �������� �������� )
    void read_register(eREGISTER_TYPE_t type, uint8_t * rx_buffer);
    //�������� � ������� ( ������� �� �������  )
    void write_one_holding_reg(uint8_t * rx_buffer);
    //�������� � ��������� ��������� ( ������� �� �������  )
    void write_multi_holding_reg(uint8_t * rx_buffer);
};


#endif