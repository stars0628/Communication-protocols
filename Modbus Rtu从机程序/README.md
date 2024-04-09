# modbus RTU从机程序
1. 在串口接收完数据后调用unsigned char MB_Analyze_Execute(unsigned char *data, unsigned short count)函数
2. 注意根据需求修改每个buff缓存大小，否则可能在后面出现数组越界导致错误的情况
3. 默认定义了unsigned char MB_SLAVEADDR = 0x0001作为设备地址
4. 注意在void MB_UartSend(unsigned char *data, unsigned short length)完善串口发送函数

## 注意事项：
1. 此程序为自定义协议程序，模仿modbus协议进行通信，并非标准的modbus
2. 完成了01 02 03 04 05 06 10等功能码
