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
void bsp_analog_i2c_init(void)//未在CubeMX配置才需要用
{
//    GPIO_InitTypeDef GPIO_InitStruct = {0};

//    __HAL_RCC_GPIOC_CLK_ENABLE();

//    /*Configure GPIO pins*/
//    GPIO_InitStruct.Pin = sda_pin|scl_pin;
//    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
//    GPIO_InitStruct.Pull = GPIO_NOPULL;
//    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
//    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
//    bsp_analog_i2c_stop();
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

    i2c_sda_high();
    analog_i2c_delay();
    i2c_scl_high();
    analog_i2c_delay();
    while(i2c_read_sda())
    {
        timeout++;
        if(timeout > 2000)
        {
            return 0;
        }
    }
    i2c_scl_low();
    analog_i2c_delay();
    return 1;
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
    i2c_sda_low();
    analog_i2c_delay();
    i2c_scl_high();
    analog_i2c_delay();
    i2c_scl_low();
    analog_i2c_delay();
    i2c_sda_high();
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

    for(i = 0; i < 8; i++)
    {
        if(data & 0x80)
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
            i2c_sda_high();
        }
        data <<= 1;
        analog_i2c_delay();
    }
}

/**
 * @brief I2C 读一个字节数据
 * @retval none
 * @author Mr.W
 * @date 2020-10-12
 */
uint8_t bsp_analog_i2c_read_byte(void)
{
    uint8_t i, data = 0;

    for(i = 0; i < 8; i++ )
    {
        data <<= 1;
        i2c_scl_high();
        analog_i2c_delay();
        if(i2c_read_sda())
        {
            data++;
        }
        i2c_scl_low();
        analog_i2c_delay();
    }

    return data;
}
