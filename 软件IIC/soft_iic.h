#ifndef __SOFT_IIC_H__
#define __SOFT_IIC_H__
#include "gpio.h"//有关GPIO的头文件

#define sda_gpio GPIOC //配置SDA和SCL引脚
#define sda_pin GPIO_PIN_14
#define scl_gpio GPIOC
#define scl_pin GPIO_PIN_13

#define i2c_sda_high() HAL_GPIO_WritePin(sda_gpio,sda_pin,GPIO_PIN_SET) //配置SDA和SCL高低电平
#define i2c_sda_low() HAL_GPIO_WritePin(sda_gpio,sda_pin,GPIO_PIN_RESET)

#define i2c_scl_high() HAL_GPIO_WritePin(scl_gpio,scl_pin,GPIO_PIN_SET)
#define i2c_scl_low() HAL_GPIO_WritePin(scl_gpio,scl_pin,GPIO_PIN_RESET)

#define i2c_read_sda() HAL_GPIO_ReadPin(sda_gpio,sda_pin)

static void analog_i2c_delay(void);//延时
void bsp_analog_i2c_init(void);//iic初始化，配置端口
void bsp_analog_i2c_start(void);//起始信号
void bsp_analog_i2c_stop(void);//结束信号
uint8_t bsp_analog_i2c_wait_ack(void);//等待应达
void bsp_analog_i2c_ack(void);//应答信号
void bsp_analog_i2c_nack(void);//否定应答信号
void bsp_analog_i2c_send_byte(uint8_t data);//发送一个字节
uint8_t bsp_analog_i2c_read_byte(uint8_t ack);//读一个字节
void I2Cx_SDA_OUT(void);//配置SDA为输出模式
void I2Cx_SDA_IN(void);//配置SDA为输入模式
#endif
