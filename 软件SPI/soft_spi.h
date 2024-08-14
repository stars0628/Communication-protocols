#ifndef __SOFT_SPI_H__
#define __SOFT_SPI_H__
#include "gpio.h"//有关GPIO的头文件

// 相关GPIO操作宏定义
#define MISO_READ HAL_GPIO_ReadPin(SPI1_MISO_GPIO_Port, SPI1_MISO_Pin)
#define SPI_SCK_H \
  HAL_GPIO_WritePin(SPI1_SCK_GPIO_Port, SPI1_SCK_Pin, GPIO_PIN_SET)
#define SPI_SCK_L \
  HAL_GPIO_WritePin(SPI1_SCK_GPIO_Port, SPI1_SCK_Pin, GPIO_PIN_RESET)
#define SPI_MOSI_H \
  HAL_GPIO_WritePin(SPI1_MOSI_GPIO_Port, SPI1_MOSI_Pin, GPIO_PIN_SET)
#define SPI_MOSI_L \
  HAL_GPIO_WritePin(SPI1_MOSI_GPIO_Port, SPI1_MOSI_Pin, GPIO_PIN_RESET)

// SPI数据数据帧位数
#define SPI_DATA_SIZE 8

// SPI高低位优先（0:MSB优先、other:LSB优先）
#define MSB_LSB 0

// SPI模式（0、1、2、3）
#define SPI_MODE 0

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
// 对读取数据的操作
#define RX_TEMP_GET rx_temp |= SPI_LSB_MASK;
#else
// 发送过程中间值的操作
#define TX_TEMP_MOVE tx_temp >>= 1
#define RX_TEMP_MOVE rx_temp >>= 1
// 判断低位为1
#define MSB_OR_LSB_MASK SPI_LSB_MASK
// 对读取数据的操作
#define RX_TEMP_GET rx_temp |= SPI_MSB_MASK;
#endif


// SPI函数
void SPI_Write(const unsigned char *TxData);
void SPI_Read(unsigned char *RxData);
void SPI_WriteRead(unsigned char *TxData, unsigned char *RxData);

#endif
