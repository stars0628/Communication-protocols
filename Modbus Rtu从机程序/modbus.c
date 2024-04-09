
// modbus-rtu标准的从机程序
#include "modbus.h"
unsigned char MB_SLAVEADDR = 0x0001;//设备地址
unsigned char usDiscreteInputBuf[DISCRETE_INPUT_NDISCRETES / 8];//离散输入寄存器
unsigned char usCoilBuf[COIL_NCOILS / 8];//线圈
unsigned short usRegInputBuf[REG_INPUT_NREGS];//输入寄存器
unsigned short usRegHoldingBuf[REG_HOLDING_NREGS];//保持寄存器
__IO unsigned char MB_TxBuf[256];  // 发送缓存,最大256字节
PDUData_TypeDef PduData;//Modbus数据解析的结构体

const static unsigned char mbCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1,
    0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,
    0x80, 0x41, 0x00, 0xC1, 0x81, 0x40};
static const char mbCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06,
    0x07, 0xC7, 0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD,
    0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,
    0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A,
    0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC, 0x14, 0xD4,
    0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3,
    0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
    0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,
    0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29,
    0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED,
    0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60,
    0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67,
    0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,
    0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
    0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E,
    0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71,
    0x70, 0xB0, 0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92,
    0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,
    0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B,
    0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B,
    0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42,
    0x43, 0x83, 0x41, 0x81, 0x80, 0x40};

static unsigned short MB_CRC16(unsigned char *puchMsg, unsigned short usDataLen);
static void MB_Parse_Data(unsigned char *data, unsigned short count);
static unsigned char MB_Data_Check(unsigned char *data, unsigned short count);


/* 函数体 --------------------------------------------------------------------*/
/**
 * 函数功能: Modbus CRC16 校验计算函数
 * 输入参数: pushMsg:待计算的数据首地址,usDataLen:数据长度
 * 返 回 值: CRC16 计算结果
 * 说    明: 计算结果是高位在前,需要转换才能发送
 */
static unsigned short MB_CRC16(unsigned char *puchMsg, unsigned short usDataLen)
{
    unsigned char uchCRCHi = 0xFF; /* high byte of CRC initialized */
    unsigned char uchCRCLo = 0xFF; /* low byte of CRC initialized */
    unsigned uIndex;               /* will index into CRC lookup table */
    while (usDataLen--)            /* pass through message buffer */
    {
        uIndex = uchCRCLo ^ *puchMsg++; /* calculate the CRC */
        uchCRCLo = uchCRCHi ^ mbCRCHi[uIndex];
        uchCRCHi = mbCRCLo[uIndex];
    }
    // 根据需要对校验值处理（高低位不同）
    // return (uchCRCLo << 8 | uchCRCHi) ;//低位在左高位在右
    return (uchCRCHi << 8 | uchCRCLo);  // 高位在左低位在右
}

/* 提取数据帧,进行解析数据帧 */
static void MB_Parse_Data(unsigned char *data, unsigned short count)
{
    PduData.SlaveAddr = data[0];
    PduData.Code = data[1];                                            // 功能码
    PduData.Addr = ((data[2] << 8) | data[3]);                         // 寄存器起始地址
    PduData.Num = ((data[4] << 8) | data[5]);                          // 数量(Coil,Input,Holding Reg,Input Reg)
    PduData._CRC = MB_CRC16((unsigned char *)data, count - 2);               // CRC校验码
    PduData.byteNums = data[6];                                        // 获得字节数
    PduData.ValueReg = (unsigned char *)&data[7];                            // 寄存器值起始地址
    PduData.PtrCoilOffset = PduData.PtrCoilbase + PduData.Addr;        // 离散量的内存起始地址
    PduData.PtrHoldingOffset = PduData.PtrHoldingbase + PduData.Addr;  // 保持寄存器的起始地址
}

/* 校验收到的数据是否合法 */
static unsigned char MB_Data_Check(unsigned char *data, unsigned short count)
{
    unsigned short ExCode = EX_CODE_NONE;
    /* 检查地址 */
    if (PduData.SlaveAddr != MB_SLAVEADDR && PduData.SlaveAddr != MB_ALLSLAVEADDR) {
        ExCode = EX_CODE_03H;  // 异常码03H
        return ExCode;
    }
    /* 校验功能码 */
    if (IS_NOT_FUNCODE(PduData.Code))  // 不支持的功能码
    {
        /* Modbus异常响应 */
        ExCode = EX_CODE_01H;  // 异常码01H
        return ExCode;
    }
    if (PduData._CRC != ((data[count - 1]) << 8 | data[count - 2])) {
        /* Modbus异常响应 */
        ExCode = EX_CODE_02H;  // 异常码02H
        return ExCode;
    }
    if (PduData.Addr > MAX_Reg_Addr) {
        ExCode = EX_CODE_04H;
        return ExCode;
    }
    return ExCode;
}

/* Modbus功能码1和功能码2 */
static void MB_Fun1_2(unsigned char* buffer)
{
    unsigned short tem_crc;
    
    MB_TxBuf[0] = PduData.SlaveAddr;       // 从机地址
    MB_TxBuf[1] = PduData.Code;  // 功能码
    if (PduData.Num % 8 == 0)  // 如果读取线圈的数量是8的整数倍，则返回字节数MB_TxBuf[2] = PduData.Num / 8
        MB_TxBuf[2] = PduData.Num / 8;
    else  // 如果不是8的整数倍，则加一
        MB_TxBuf[2] = PduData.Num / 8 + 1;
    for (int i = 0; i < MB_TxBuf[2]; i++) {
        MB_TxBuf[3 + i] = (buffer[PduData.Addr + 7 + i * 8] << 7) | 
                        (buffer[PduData.Addr + 6 + i * 8] << 6) | 
                        (buffer[PduData.Addr + 5 + i * 8] << 5) | 
                        (buffer[PduData.Addr + 4 + i * 8] << 4) | 
                        (buffer[PduData.Addr + 3 + i * 8] << 3) | 
                        (buffer[PduData.Addr + 2 + i * 8] << 2) | 
                        (buffer[PduData.Addr + 1 + i * 8] << 1) | 
                        (buffer[PduData.Addr + 0 + i * 8] << 0);
    }
    tem_crc = MB_CRC16((unsigned char *)MB_TxBuf, MB_TxBuf[2] + 3);  // CRC校验码
    MB_TxBuf[MB_TxBuf[2] + 3] = (unsigned char)tem_crc;
    MB_TxBuf[MB_TxBuf[2] + 4] = (unsigned char)(tem_crc >> 8);
    MB_UartSend((unsigned char *)MB_TxBuf, MB_TxBuf[2] + 5);
}

/* Modbus功能码3和功能码4 */
static void MB_Fun3_4(unsigned short *buffer)
{
    unsigned short tem_crc;
    MB_TxBuf[0] = PduData.SlaveAddr;
    MB_TxBuf[1] = PduData.Code;
    MB_TxBuf[2] = PduData.Num * 2;
    for (unsigned char i = 0; i < PduData.Num; i++) {
        MB_TxBuf[i * 2 + 3] = (unsigned char)(buffer[PduData.Addr + i] >> 8);
        MB_TxBuf[i * 2 + 4] = (unsigned char)(buffer[PduData.Addr + i] >> 0);
    }
    tem_crc = MB_CRC16((unsigned char *)MB_TxBuf, PduData.Num * 2 + 3);  // CRC校验码
    MB_TxBuf[PduData.Num * 2 + 3] = (unsigned char)tem_crc;
    MB_TxBuf[PduData.Num * 2 + 4] = (unsigned char)(tem_crc >> 8);
    MB_UartSend((unsigned char *)MB_TxBuf, PduData.Num * 2 + 5);
}


/**
 * 函数功能: 对接收到的数据进行分析并执行
 * 输入参数: 无
 * 返 回 值: 异常码或0x00
 * 说    明: 判断功能码,验证地址是否正确.数值内容是否溢出,数据没错误就发送响应信号
 */
unsigned char MB_Analyze_Execute(unsigned char *data, unsigned short count)
{
    unsigned short ExCode = EX_CODE_NONE;
    unsigned short tem_crc;
    MB_Parse_Data(data, count);//解析数据帧

    if(MB_Data_Check(data,count) != EX_CODE_NONE) { //判断数据是否合法
        return ExCode;
    }
    
    /* 根据功能码分别做判断 */
    switch (PduData.Code) {
    case FUN_CODE_01H:             // 读线圈寄存器
        MB_Fun1_2(usCoilBuf);
        break;
    case FUN_CODE_02H:             // 读离散输入寄存器，其实读离散输入寄存器和读线圈寄存器类似，不过离散输入寄存器是只读的
        MB_Fun1_2(usDiscreteInputBuf);
        break;
    case FUN_CODE_03H:  // 响应读保持寄存器
        MB_Fun3_4(usRegHoldingBuf);
        break;
    case FUN_CODE_04H:  // 响应读输入寄存器
        MB_Fun3_4(usRegInputBuf);
        break;
    case FUN_CODE_05H:
        /* 写入一个线圈值 */
        if (PduData.Num == 0xFF00) {
            usCoilBuf[PduData.Addr] = 1;
        } else {
            usCoilBuf[PduData.Addr] = 0;
        }
        MB_UartSend(data, count);  // 返回发送的指令作为响应
        break;
    case FUN_CODE_06H:  // 写单个保持寄存器
        usRegHoldingBuf[PduData.Addr] = (data[4] << 8) | (data[5] << 0);
        MB_UartSend(data, count);  // 返回发送的指令作为响应
        break;
    case FUN_CODE_10H:  // 写入多个保持寄存器
        for (int i = 0; i < PduData.Num; i++) {
            usRegHoldingBuf[PduData.Addr + i] = (data[i * 2 + 6] << 8) | (data[i * 2 + 7] << 0);
        }
        // 响应写多个保持寄存器
        MB_TxBuf[0] = PduData.SlaveAddr;  // 从机地址
        MB_TxBuf[1] = data[1];  // 功能码
        MB_TxBuf[2] = data[2];  // 起始地址高位
        MB_TxBuf[3] = data[3];  // 起始地址低位
        MB_TxBuf[4] = data[4];  // 数量高位
        MB_TxBuf[5] = data[5];  // 数量低位
        tem_crc = MB_CRC16((unsigned char *)MB_TxBuf, 6);  // CRC校验码
        MB_TxBuf[6] = (unsigned char)tem_crc;              // CRC高位
        MB_TxBuf[7] = (unsigned char)(tem_crc >> 8);       // CRC低位
        MB_UartSend((unsigned char *)MB_TxBuf, 8);
        break;
    }
    /* 数据帧没有异常 */
    return ExCode;  //   EX_CODE_NONE
}

/**
 * 函数功能: 串口发送函数
 * 输入参数: data:要发送的buff,length:要发送的长度
 * 返 回 值:
 * 说    明: 发送指定长度的串口数据
 */
void MB_UartSend(unsigned char *data, unsigned short length)
{
    // 在此处将data的数据传入串口发送buff，并通过串口发送出去
    HAL_UART_Transmit_DMA(&huart1,data,length);
}

