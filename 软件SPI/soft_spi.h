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
// SPI工作模式（允许值0、1、2、3）
#define SPI_MODE 3
// SPI数据高位判断条件
#define SPI_MSB_MASK (1 << (SPI_DATA_SIZE - 1))

// SPI函数
void SPI_Write(unsigned char TxData);
unsigned char SPI_Read(void);
void SPI_WriteRead(unsigned char TxData, unsigned char *RxData);
