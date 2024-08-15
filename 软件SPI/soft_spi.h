#ifndef __SOFT_SPI_H__
#define __SOFT_SPI_H__
#include "gpio.h" //有关GPIO的头文件

// 相关GPIO操作宏定义
#define MISO_READ HAL_GPIO_ReadPin(SPI1_MISO_GPIO_Port, SPI1_MISO_Pin)
#define SPI_SCK_H                                                              \
  HAL_GPIO_WritePin(SPI1_SCK_GPIO_Port, SPI1_SCK_Pin, GPIO_PIN_SET)
#define SPI_SCK_L                                                              \
  HAL_GPIO_WritePin(SPI1_SCK_GPIO_Port, SPI1_SCK_Pin, GPIO_PIN_RESET)
#define SPI_MOSI_H                                                             \
  HAL_GPIO_WritePin(SPI1_MOSI_GPIO_Port, SPI1_MOSI_Pin, GPIO_PIN_SET)
#define SPI_MOSI_L                                                             \
  HAL_GPIO_WritePin(SPI1_MOSI_GPIO_Port, SPI1_MOSI_Pin, GPIO_PIN_RESET)

// SPI数据数据帧位数
#define SPI_DATA_SIZE 16

// SPI高低位优先（0:MSB优先、其它:LSB优先）
#define MSB_LSB 0

// SPI模式（0、1、2、3）
#define SPI_MODE 1

// 引脚电平变换后延时
#define SPI_Delay

// MSB、LSB掩码
#define SPI_MSB_MASK (1 << (SPI_DATA_SIZE - 1))
#define SPI_LSB_MASK (1)

#if MSB_LSB == 0
// 发送过程中间值的操作
#define TX_TEMP_MOVE tx_temp <<= 1
#define RX_TEMP_MOVE rx_temp <<= 1
// 判断高位为1
#define MSB_OR_LSB_MASK SPI_MSB_MASK
// 对读取中间值的操作
#define RX_TEMP_GET rx_temp |= 1
#else
// 发送过程中间值的操作
#define TX_TEMP_MOVE tx_temp >>= 1
#define RX_TEMP_MOVE rx_temp >>= 1
// 判断低位为1
#define MSB_OR_LSB_MASK SPI_LSB_MASK
// 对读取中间值的操作
#define RX_TEMP_GET rx_temp |= (1 << (SPI_DATA_SIZE - 1))
#endif

// 读写多个数据时指针的自增
#if SPI_DATA_SIZE <= 8
#define PTR_MOVE 1
#else
#define PTR_MOVE 2
#endif

void SPI_Write(const unsigned char *TxData); // SPI写1个数据函数
void SPI_Read(unsigned char *RxData);        // SPI读1个数据函数
void SPI_WriteRead(const unsigned char *TxData,
                   unsigned char *RxData); // SPI同时读写1个数据函数
void SPI_Transmit(const unsigned char *TxData,
                  unsigned short length); // SPI写多个数据函数
void SPI_Receive(unsigned char *RxData,
                 unsigned short length); // SPI读多个数据函数
void SPI_TransmitReceive(const unsigned char *TxData, unsigned char *RxData,
                         unsigned short length); // SPI读写多个数据函数

#endif
