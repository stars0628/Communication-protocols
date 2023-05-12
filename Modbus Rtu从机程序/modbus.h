
#ifndef _MODBUS_H_
#define _MODBUS_H_
// 串口相关头文件

// 定义从机地址
#define Addr_Slave 0x03
/* 类型定义 ------------------------------------------------------------------*/
typedef struct {
    __IO uint8_t Code;                // 功能码
    __IO uint8_t byteNums;            // 字节数
    __IO uint16_t Addr;               // 操作内存的起始地址
    __IO uint16_t Num;                // 寄存器或者线圈的数量
    __IO uint16_t _CRC;               // CRC校验码
    __IO uint8_t *ValueReg;           // 10H功能码的数据
    __IO uint8_t *PtrCoilbase;        // Coil和Input内存首地址
    __IO uint8_t *PtrCoilOffset;      // Coil和Input偏移内存首地址
    __IO uint16_t *PtrHoldingbase;    // HoldingReg内存首地址
    __IO uint16_t *PtrHoldingOffset;  // HoldingReg内存首地址
} PDUData_TypeDef;
/* 宏定义 --------------------------------------------------------------------*/
#define MB_SLAVEADDR    0x0001
#define MB_ALLSLAVEADDR 0x00FF
#define FUN_CODE_01H    0x01  // 功能码01H
#define FUN_CODE_02H    0x02  // 功能码02H
#define FUN_CODE_03H    0x03  // 功能码03H
#define FUN_CODE_04H    0x04  // 功能码04H
#define FUN_CODE_05H    0x05  // 功能码05H
#define FUN_CODE_06H    0x06  // 功能码06H
#define FUN_CODE_10H    0x10  // 功能码10H
/* 本例程所支持的功能码,需要添加新功能码还需要在.c文件里面添加 */
#define IS_NOT_FUNCODE(code) (!((code == FUN_CODE_01H) || \
                                (code == FUN_CODE_02H) || \
                                (code == FUN_CODE_03H) || \
                                (code == FUN_CODE_04H) || \
                                (code == FUN_CODE_05H) || \
                                (code == FUN_CODE_06H) || \
                                (code == FUN_CODE_10H)))
#define EX_CODE_NONE 0x00  // 异常码 无异常
#define EX_CODE_01H  0x01  // 异常码
#define EX_CODE_02H  0x02  // 异常码 校验错误
#define EX_CODE_03H  0x03  // 异常码
#define EX_CODE_04H  0x04  // 异常码 寄存器越界
/* ----------------------- modbus reg lengh Defines ------------------------------------------*/
/* ----------------------- modbus 各个寄存器数据长度，允许用户调用的数据----------------------*/
#define DISCRETE_INPUT_START      1
#define DISCRETE_INPUT_NDISCRETES 96
#define COIL_START                1
#define COIL_NCOILS               96
#define REG_INPUT_START           1
#define REG_INPUT_NREGS           100
#define REG_HOLDING_START         1
#define REG_HOLDING_NREGS         100
#define MAX_Reg_Addr              100  // 最大的寄存器地址
/* ----------------------- modbus Static variables defines------------------------------------*/
extern uint16_t usDiscreteInputStart;
extern uint8_t usDiscreteInputBuf[DISCRETE_INPUT_NDISCRETES / 8];
extern uint16_t usCoilStart;
extern uint8_t usCoilBuf[COIL_NCOILS / 8];
extern uint16_t usRegInputStart;
extern uint16_t usRegInputBuf[REG_INPUT_NREGS];
extern uint16_t usRegHoldingStart;
extern uint16_t usRegHoldingBuf[REG_HOLDING_NREGS];
extern __IO uint8_t Tx_Buf[256];  // 发送缓存,最大256字节
extern PDUData_TypeDef PduData;
void MB_Parse_Data(uint8_t *data, uint32_t count);
void UART_Transmit(uint8_t *data, uint32_t length);
uint8_t MB_Analyze_Execute(uint8_t *data, uint32_t count);
#endif /* INC_CUS_MODBUS_H_ */
