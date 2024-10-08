#include "soft_spi.h"

/**************************************************************************************
 * 描  述 : 模拟SPI写入一个数据
 * 入  参 : TxData : 待发送的数据地址
 * 返回值 : 无
 **************************************************************************************/
void SPI_Write(const unsigned char *TxData) {
  unsigned char i;
  unsigned short *tx_ptr;
  unsigned short tx_temp;
  tx_ptr = (unsigned short *)TxData;
  tx_temp = *tx_ptr;
#if SPI_MODE == 0
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_L;
    SPI_Delay;
    if (tx_temp & MSB_OR_LSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_Delay;
    SPI_SCK_H;
    SPI_Delay;
    TX_TEMP_MOVE;
  }
  SPI_SCK_L;
#elif SPI_MODE == 1
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_H;
    SPI_Delay;
    if (tx_temp & MSB_OR_LSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_Delay;
    SPI_SCK_L;
    SPI_Delay;
    TX_TEMP_MOVE;
  }
  SPI_SCK_L;
#elif SPI_MODE == 2
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_H;
    SPI_Delay;
    if (tx_temp & MSB_OR_LSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_Delay;
    SPI_SCK_L;
    SPI_Delay;
    TX_TEMP_MOVE;
  }
  SPI_SCK_H;
#elif SPI_MODE == 3
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_L;
    SPI_Delay;
    if (tx_temp & MSB_OR_LSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_Delay;
    SPI_SCK_H;
    SPI_Delay;
    TX_TEMP_MOVE;
  }
  SPI_SCK_H;
#endif
}

/**************************************************************************************
 * 描  述 : 模拟SPI读取一个数据
 * 入  参 : RxData : 接收数据的地址
 * 返回值 : 无
 **************************************************************************************/
void SPI_Read(unsigned char *RxData) {
  unsigned char i;
  unsigned short rx_temp;
#if SPI_MODE == 0
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    RX_TEMP_MOVE;
    SPI_SCK_L;
    SPI_Delay;
    SPI_SCK_H;
    SPI_Delay;
    if (MISO_READ) {
      RX_TEMP_GET;
    }
  }
  SPI_SCK_L;
#elif SPI_MODE == 1
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    RX_TEMP_MOVE;
    SPI_SCK_H;
    SPI_Delay;
    SPI_SCK_L;
    SPI_Delay;
    if (MISO_READ) {
      RX_TEMP_GET;
    }
  }
  SPI_SCK_L;
#elif SPI_MODE == 2
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    RX_TEMP_MOVE;
    SPI_SCK_H;
    SPI_Delay;
    SPI_SCK_L;
    SPI_Delay;
    if (MISO_READ) {
      RX_TEMP_GET;
    }
  }
  SPI_SCK_H;
#elif SPI_MODE == 3
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    RX_TEMP_MOVE;
    SPI_SCK_L;
    SPI_Delay;
    SPI_SCK_H;
    SPI_Delay;
    if (MISO_READ) {
      RX_TEMP_GET;
    }
  }
  SPI_SCK_H
#endif
  *(uint16_t *)RxData = rx_temp;
}

/**************************************************************************************
 * 描  述 : 模拟SPI读写一个数据
 * 入  参 : TxData : 待发送的数据地址
            RxData : 接收数据的地址
 * 返回值 : 无
 **************************************************************************************/
void SPI_WriteRead(const unsigned char *TxData, unsigned char *RxData) {
  unsigned char i;
  unsigned short *tx_ptr;
  unsigned short tx_temp, rx_temp;
  tx_ptr = (unsigned short *)TxData;
  tx_temp = *tx_ptr;
#if SPI_MODE == 0
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_L;
    SPI_Delay;
    if (tx_temp & MSB_OR_LSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_Delay;
    TX_TEMP_MOVE;
    SPI_SCK_H;
    SPI_Delay;
    RX_TEMP_MOVE;
    if (MISO_READ) {
      RX_TEMP_GET;
    }
  }
  SPI_SCK_L;
#elif SPI_MODE == 1
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_H;
    SPI_Delay;
    if (tx_temp & MSB_OR_LSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_Delay;
    TX_TEMP_MOVE;
    SPI_SCK_L;
    SPI_Delay;
    RX_TEMP_MOVE;
    if (MISO_READ) {
      RX_TEMP_GET;
    }
  }
  SPI_SCK_L;
#elif SPI_MODE == 2
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_H;
    SPI_Delay;
    if (tx_temp & MSB_OR_LSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_Delay;
    TX_TEMP_MOVE;
    SPI_SCK_L;
    SPI_Delay;
    RX_TEMP_MOVE;
    if (MISO_READ) {
      RX_TEMP_GET;
    }
  }
  SPI_SCK_H;
#elif SPI_MODE == 3
  for (i = 0; i < SPI_DATA_SIZE; i++) {
    SPI_SCK_L;
    SPI_Delay;
    if (tx_temp & MSB_OR_LSB_MASK) {
      SPI_MOSI_H;
    } else {
      SPI_MOSI_L;
    }
    SPI_Delay;
    TX_TEMP_MOVE;
    SPI_SCK_H;
    SPI_Delay;
    RX_TEMP_MOVE;
    if (MISO_READ) {
      RX_TEMP_GET;
    }
  }
  SPI_SCK_H;
#endif
  *(uint16_t *)RxData = rx_temp;
}

/**************************************************************************************
 * 描  述 : 模拟SPI写入多个数据
 * 入  参 : TxData : 待发送的数据地址
            length : 数据长度
 * 返回值 : 无
 **************************************************************************************/
void SPI_Transmit(const unsigned char *TxData, unsigned short length) {
  while (length--) {
    SPI_Write(TxData);
    TxData += PTR_MOVE;
  }
}

/**************************************************************************************
 * 描  述 : 模拟SPI读取多个数据
 * 入  参 : RxData : 接收数据的地址
            length : 数据长度
 * 返回值 : 无
 **************************************************************************************/
void SPI_Receive(unsigned char *RxData, unsigned short length) {
  while (length--) {
    SPI_Read(RxData);
    RxData += PTR_MOVE;
  }
}

/**************************************************************************************
 * 描  述 : 模拟SPI读写多个数据
 * 入  参 : TxData : 待发送的数据地址
            RxData : 接收数据的地址
            length : 数据长度
 * 返回值 : 无
 **************************************************************************************/
void SPI_TransmitReceive(const unsigned char *TxData, unsigned char *RxData,
                         unsigned short length) {
  while (length--) {
    SPI_WriteRead(TxData, RxData);
    TxData += PTR_MOVE;
    RxData += PTR_MOVE;
  }
}
