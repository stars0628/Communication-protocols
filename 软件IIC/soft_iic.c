#include "soft_iic.h"

/**
 * @brief 模拟I2C延时
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
static void analog_i2c_delay(void)//出现异常或延时较大需适当增减延时
{
    volatile uint8_t i;

    for (i = 0; i < 3; i++);
}

/**
 * @brief 软件模拟I2C初始化
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
void bsp_analog_i2c_init(void)
{
    /* ------配置SDA和SCL为输出模式begin------------ */



    /* ------配置SDA和SCL为输出模式end------------ */
    bsp_analog_i2c_stop();//配置完SDA和SCL后将引脚设为高电平，即IIC空闲状态
}

/**
 * @brief SDA输出配置
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
void I2Cx_SDA_OUT(void)
{
    //配置SDA为输出
}

/**
 * @brief SDA输入配置
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
void I2Cx_SDA_IN(void)
{
    //配置SDA为输入
}

/**
 * @brief I2C 开始,SCL为高电平的时候SDA产生一个下降沿信号
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
void bsp_analog_i2c_start(void)
{
    /*    _____
     *SDA      \_____________
     *    __________
     *SCL           \________
     */
    I2Cx_SDA_OUT();
    i2c_sda_high();
    i2c_scl_high();
    analog_i2c_delay();
    i2c_sda_low();
    analog_i2c_delay();
    i2c_scl_low();
    analog_i2c_delay();
}

/**
 * @brief I2C 停止,SCL为高电平的时候SDA产生一个上升沿信号
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
void bsp_analog_i2c_stop(void)
{
    /*               _______
     *SDA __________/
     *          ____________
     *SCL _____/
     */
    I2Cx_SDA_OUT();
    i2c_sda_low();
    i2c_scl_high();
    analog_i2c_delay();
    i2c_sda_high();
    analog_i2c_delay();
}

/**
 * @brief I2C 等待响应
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
uint8_t bsp_analog_i2c_wait_ack(void)
{
    uint32_t timeout = 0;
    I2Cx_SDA_IN();
    i2c_sda_high();
    analog_i2c_delay();
    i2c_scl_high();
    analog_i2c_delay();
    while(i2c_read_sda())
    {
        timeout++;
        if(timeout > 2000)
        {
            bsp_analog_i2c_stop();
            return 0;//返回0无应答
        }
    }
    i2c_scl_low();
    analog_i2c_delay();
    return 1;//返回1有应答
}

/**
 * @brief I2C 响应
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
void bsp_analog_i2c_ack(void)
{
    /*           ____
     *SCL ______/    \______
     *    ____         _____
     *SDA     \_______/
     */
    I2Cx_SDA_OUT();
    i2c_scl_low();
    analog_i2c_delay();
    i2c_sda_low();
    analog_i2c_delay();
    i2c_scl_high();
    analog_i2c_delay();
    i2c_scl_low();
    analog_i2c_delay();
    i2c_sda_high();
    analog_i2c_delay();
}

/**
 * @brief I2C 不响应
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
void bsp_analog_i2c_nack(void)
{
    /*           ____
     *SCL ______/    \______
     *    __________________
     *SDA
     */
    I2Cx_SDA_OUT();
    i2c_scl_low();
    analog_i2c_delay();
    i2c_sda_high();
    analog_i2c_delay();
    i2c_scl_high();
    analog_i2c_delay();
    i2c_scl_low();
    analog_i2c_delay();
}

/**
 * @brief I2C 发送一个字节数据
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
void bsp_analog_i2c_send_byte(uint8_t data)
{
    uint8_t i;
    I2Cx_SDA_OUT();
    i2c_scl_low();
    analog_i2c_delay();
    for(i = 0; i < 8; i++)
    {
        if(data & 0x80)//判断高位是不是1
        {
            i2c_sda_high();
        }
        else
        {
            i2c_sda_low();
        }

        analog_i2c_delay();
        i2c_scl_high();
        analog_i2c_delay();
        i2c_scl_low();
        if(i == 7)
        {
            i2c_sda_high();//发送最后一位之后，释放SDA总线，方便接收来自接收端的应答信号
        }
        data <<= 1;
    }
}

/**
 * @brief I2C 读一个字节数据
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t bsp_analog_i2c_read_byte(uint8_t ack)
{
    uint8_t i, data = 0;
    I2Cx_SDA_IN();//SDA设置为输入
    for(i = 0; i < 8; i++ )
    {
        i2c_scl_low();
        analog_i2c_delay();
        i2c_scl_high();
        data <<= 1;
        analog_i2c_delay();
        if(i2c_read_sda())
        {
            data++;
        }
        analog_i2c_delay();
    }
    if (!ack)
        bsp_analog_i2c_nack();//发送nACK
    else
        bsp_analog_i2c_ack(); //发送ACK
    return data;
}
