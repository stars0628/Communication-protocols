#include "soft_spi.h"

#if SPI_MODE == 0
/**************************************************************************************
 * 描  述 : 模拟SPI写入一个数据
 * 入  参 : unsigned char date
 * 返回值 : 无
 **************************************************************************************/
void SPI_Write(unsigned char TxData) {
  unsigned char temp = TxData, i;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_L;
    if (temp & SPI_MSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_SCK_H;
    temp <<= 1;
  }
  SPI_SCK_L;
}

/**************************************************************************************
 * 描  述 : 模拟SPI读取一个数据
 * 入  参 : 无
 * 返回值 : 读取unsigned char数据
 **************************************************************************************/
unsigned char SPI_Read(void) {
  unsigned char i, temp = 0;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    temp <<= 1;
    SPI_SCK_L;
    if (MISO_READ) {
      temp++;
    }
    SPI_SCK_H;
  }
  SPI_SCK_L;
  return temp;
}

/**************************************************************************************
 * 描  述 : 模拟SPI读写一个数据
 * 入  参 : unsigned char TxData, unsigned char *RdData
 * 返回值 : 无
 **************************************************************************************/
void SPI_WriteRead(unsigned char TxData, unsigned char *RxData) {
  unsigned char i, temp = 0;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_L;
    if (TxData & SPI_MSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    TxData <<= 1;
    SPI_SCK_H;
    temp <<= 1;
    if (MISO_READ) {
      temp |= 0x01;
    }
  }
  SPI_SCK_L;
  *RxData = temp;
}

#elif SPI_MODE == 1
/**************************************************************************************
 * 描  述 : 模拟SPI写入一个数据
 * 入  参 : unsigned char date
 * 返回值 : 无
 **************************************************************************************/
void SPI_Write(unsigned char TxData) {
  unsigned char temp = TxData, i;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_H;
    if (temp & SPI_MSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_SCK_L;
    temp <<= 1;
  }
}

/**************************************************************************************
 * 描  述 : 模拟SPI读取一个数据
 * 入  参 : 无
 * 返回值 : 读取unsigned char数据
 **************************************************************************************/
unsigned char SPI_Read(void) {
  unsigned char i, temp = 0;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    temp <<= 1;
    SPI_SCK_H;
    SPI_SCK_L;
    if (MISO_READ) {
      temp++;
    }
  }
  return temp;
}

/**************************************************************************************
 * 描  述 : 模拟SPI读写一个数据
 * 入  参 : unsigned char TxData, unsigned char *RdData
 * 返回值 : 无
 **************************************************************************************/
void SPI_WriteRead(unsigned char TxData, unsigned char *RxData) {
  unsigned char i, temp = 0;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_H;
    if (TxData & SPI_MSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    TxData <<= 1;
    SPI_SCK_L;
    temp <<= 1;
    if (MISO_READ) {
      temp |= 0x01;
    }
  }
  *RxData = temp;
}

#elif SPI_MODE == 2
/**************************************************************************************
 * 描  述 : 模拟SPI写入一个数据
 * 入  参 : unsigned char date
 * 返回值 : 无
 **************************************************************************************/
void SPI_Write(unsigned char TxData) {
  unsigned char temp = TxData, i;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_H;
    if (temp & SPI_MSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_SCK_L;
    temp <<= 1;
  }
  SPI_SCK_H;
}

/**************************************************************************************
 * 描  述 : 模拟SPI读取一个数据
 * 入  参 : 无
 * 返回值 : 读取unsigned char数据
 **************************************************************************************/
unsigned char SPI_Read(void) {
  unsigned char i, temp = 0;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    temp <<= 1;
    SPI_SCK_H;
    SPI_SCK_L;
    if (MISO_READ) {
      temp++;
    }
  }
  SPI_SCK_H;
  return temp;
}

/**************************************************************************************
 * 描  述 : 模拟SPI读写一个数据
 * 入  参 : unsigned char TxData, unsigned char *RdData
 * 返回值 : 无
 **************************************************************************************/
void SPI_WriteRead(unsigned char TxData, unsigned char *RxData) {
  unsigned char i, temp = 0;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_H;
    if (TxData & SPI_MSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    TxData <<= 1;
    SPI_SCK_L;
    temp <<= 1;
    if (MISO_READ) {
      temp |= 0x01;
    }
  }
  SPI_SCK_H;
  *RxData = temp;
}
#elif SPI_MODE == 3
/**************************************************************************************
 * 描  述 : 模拟SPI写入一个数据
 * 入  参 : unsigned char date
 * 返回值 : 无
 **************************************************************************************/
void SPI_Write(unsigned char TxData) {
  unsigned char temp = TxData, i;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_L;
    if (temp & SPI_MSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_SCK_H;
    temp <<= 1;
  }
}

/**************************************************************************************
 * 描  述 : 模拟SPI读取一个数据
 * 入  参 : 无
 * 返回值 : 读取unsigned char数据
 **************************************************************************************/
unsigned char SPI_Read(void) {
  unsigned char i, temp = 0;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    temp <<= 1;
    SPI_SCK_L;
    SPI_SCK_H;
    if (MISO_READ) {
      temp++;
    }
  }
  return temp;
}

/**************************************************************************************
 * 描  述 : 模拟SPI读写一个数据
 * 入  参 : unsigned char TxData, unsigned char *RdData
 * 返回值 : 无
 **************************************************************************************/
void SPI_WriteRead(unsigned char TxData, unsigned char *RxData) {
  unsigned char i, temp = 0;
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_L;
    if (TxData & SPI_MSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    TxData <<= 1;
    SPI_SCK_H;
    temp <<= 1;
    if (MISO_READ) {
      temp |= 0x01;
    }
  }
  *RxData = temp;
}
#endif
