
# 软件SPI程序
1. SCK、MOSI配置成推挽输出，MIOS配置成输入，在相应spi头文件中修改GPIO操作的宏定义
2. 注意在头文件中修改SPI数据大小、模式、高位优先还是低位优先等
3. 可在头文件的SPI_Delay宏定义中定义一个延时函数


## 注意
1. 程序中不包含CS片选引脚
2. 可以在电平变换时适当增加延时
3. 依照时序图写的程序,目前此程序只验证了模式1