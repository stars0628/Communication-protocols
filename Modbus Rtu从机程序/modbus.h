
#ifndef _MODBUS_H_
#define _MODBUS_H_

// 相关头文件
#include "stm32g4xx_hal.h"
#include "usart.h"

/* 类型定义 ------------------------------------------------------------------*/
typedef struct {
  __IO unsigned char SlaveAddr;          // 从机地址
  __IO unsigned char Code;               // 功能码
  __IO unsigned char byteNums;           // 字节数
  __IO unsigned short Addr;              // 操作内存的起始地址
  __IO unsigned short Num;               // 寄存器或者线圈的数量
  __IO unsigned short _CRC;              // CRC校验码
  __IO unsigned char *ValueReg;          // 10H功能码的数据
  __IO unsigned char *PtrCoilbase;       // Coil和Input内存首地址
  __IO unsigned char *PtrCoilOffset;     // Coil和Input偏移内存首地址
  __IO unsigned short *PtrHoldingbase;   // HoldingReg内存首地址
  __IO unsigned short *PtrHoldingOffset; // HoldingReg内存首地址
} PDUData_TypeDef;

/* 地址和功能码宏定义  */
#define MB_ALLSLAVEADDR 0x00FF

#define FUN_CODE_01H 0x01 // 功能码01H
#define FUN_CODE_02H 0x02 // 功能码02H
#define FUN_CODE_03H 0x03 // 功能码03H
#define FUN_CODE_04H 0x04 // 功能码04H
#define FUN_CODE_05H 0x05 // 功能码05H
#define FUN_CODE_06H 0x06 // 功能码06H
#define FUN_CODE_10H 0x10 // 功能码10H

/* 本例程所支持的功能码,需要添加新功能码还需要在.c文件里面添加 */
#define IS_NOT_FUNCODE(code)                                                   \
  (!((code == FUN_CODE_01H) || (code == FUN_CODE_02H) ||                       \
     (code == FUN_CODE_03H) || (code == FUN_CODE_04H) ||                       \
     (code == FUN_CODE_05H) || (code == FUN_CODE_06H) ||                       \
     (code == FUN_CODE_10H)))

/* 异常码枚举 */
enum ModbusExceptionCode {
  EX_CODE_NONE,
  EX_CODE_01H,
  EX_CODE_02H,
  EX_CODE_03H,
  EX_CODE_04H,
  EX_CODE_05H,
  // ... 其他异常码
};

/* ----------------------- modbus
 * 各个寄存器数据长度，允许用户调用的数据----------------------*/
#define DISCRETE_INPUT_START 0       // 离散输入起始地址
#define DISCRETE_INPUT_NDISCRETES 96 // 表示有n个离散寄存器
#define COIL_START 0                 // 线圈起始地址
#define COIL_NCOILS 96               // 表示有n个线圈寄存器
#define REG_INPUT_START 0            // 输入寄存器起始地址
#define REG_INPUT_NREGS 100          // 表示有n个输入寄存器
#define REG_HOLDING_START 0          // 保持寄存器起始地址
#define REG_HOLDING_NREGS 100        // 表示有n个保持寄存器
#define MAX_Reg_Addr 100             // 最大的寄存器地址

/* ----------------------- modbus Static variables
 * defines------------------------------------*/
extern unsigned short usDiscreteInputStart;
extern unsigned char usDiscreteInputBuf[DISCRETE_INPUT_NDISCRETES / 8];
extern unsigned short usCoilStart;
extern unsigned char usCoilBuf[COIL_NCOILS / 8];
extern unsigned short usRegInputStart;
extern unsigned short usRegInputBuf[REG_INPUT_NREGS];
extern unsigned short usRegHoldingStart;
extern unsigned short usRegHoldingBuf[REG_HOLDING_NREGS];
extern __IO unsigned char MB_TxBuf[256]; // 发送缓存,最大256字节
extern PDUData_TypeDef PduData;

unsigned char MB_Analyze_Execute(unsigned char *data, unsigned short count);
void MB_UartSend(unsigned char *data, unsigned short length);

#endif /* INC_CUS_MODBUS_H_ */
