# modbus RTU从机程序
1. 在串口接收完数据后调用MB_Analyze_Execute()函数，传入接收到的数据和数据长度即可
2. 注意根据需求修改每个buff缓存大小，否则可能在后面出现数组越界导致错误的情况
3. 如果需要用到从机地址，可以将接收到的第二个数据与你想要的地址进行判断，即可实现类似效果
4. 注意在UART_Transmit()完善你都串口传输，传入要发送的数据，和长度，在函数中完成发送buff的复制和发送

## 注意事项：
1. 此程序为自定义协议程序，模仿modbus协议进行通信，并非标准的modbus
2. 完成了01 02 03 04 05 06 10等功能码
