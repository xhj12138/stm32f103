/**
 ****************************************************************************************************
 * @file        mpu6050_iic.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       MPU6050模块IIC接口驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车软件实现IIC，用以驱动MPU6050
 *
<<<<<<< HEAD
 *
 * 修改说明
 * V1.0 20230813
 * 第一次发布
 *
 *
=======
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 ****************************************************************************************************
 */

#include "./BSP/MPU6050/mpu6050_iic.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       IIC接口延时函数，用于控制IIC读写速度
 * @param       无
 * @retval      无
 */
static inline void mpu6050_iic_delay(void)
{
<<<<<<< HEAD
    delay_us(1);
=======
    delay_us(2);
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
}

/**
 * @brief       产生IIC起始信号
 * @param       无
 * @retval      无
 */
void mpu6050_iic_start(void)
{
    MPU6050_IIC_SDA(1);
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
}

/**
 * @brief       产生IIC停止信号
 * @param       无
 * @retval      无
 */
void mpu6050_iic_stop(void)
{
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
}

/**
 * @brief       等待IIC应答信号
 * @param       无
 * @retval      0: 应答信号接收成功
 *              1: 应答信号接收失败
 */
uint8_t mpu6050_iic_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;
    
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    
    while (MPU6050_IIC_READ_SDA())
    {
        waittime++;
        
        if (waittime > 250)
        {
            mpu6050_iic_stop();
            rack = 1;
            break;
        }
    }
    
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
    
    return rack;
}

/**
 * @brief       产生ACK应答信号
 * @param       无
 * @retval      无
 */
void mpu6050_iic_ack(void)
{
    MPU6050_IIC_SDA(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
}

/**
 * @brief       不产生ACK应答信号
 * @param       无
 * @retval      无
 */
void mpu6050_iic_nack(void)
{
    MPU6050_IIC_SDA(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(1);
    mpu6050_iic_delay();
    MPU6050_IIC_SCL(0);
    mpu6050_iic_delay();
}

/**
 * @brief       IIC发送一个字节
 * @param       dat: 要发送的数据
 * @retval      无
 */
void mpu6050_iic_send_byte(uint8_t dat)
{
    uint8_t t;
    
    for (t=0; t<8; t++)
    {
        MPU6050_IIC_SDA((dat & 0x80) >> 7);
        mpu6050_iic_delay();
        MPU6050_IIC_SCL(1);
        mpu6050_iic_delay();
        MPU6050_IIC_SCL(0);
        dat <<= 1;
    }
    MPU6050_IIC_SDA(1);
}

/**
 * @brief       IIC接收一个字节
 * @param       ack: ack=1时，发送ack; ack=0时，发送nack
 * @retval      接收到的数据
 */
uint8_t mpu6050_iic_read_byte(uint8_t ack)
{
    uint8_t i;
    uint8_t dat = 0;
    
    for (i = 0; i < 8; i++ )
    {
        dat <<= 1;
        MPU6050_IIC_SCL(1);
        mpu6050_iic_delay();
        
        if (MPU6050_IIC_READ_SDA())
        {
            dat++;
        }
        
        MPU6050_IIC_SCL(0);
        mpu6050_iic_delay();
    }
    
    if (ack == 0)
    {
        mpu6050_iic_nack();
    }
    else
    {
        mpu6050_iic_ack();
    }

    return dat;
}

/**
 * @brief       初始化IIC接口
 * @param       无
 * @retval      无
 */
void mpu6050_iic_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能SCL、SDA引脚GPIO的时钟 */
    MPU6050_IIC_SCL_GPIO_CLK_ENABLE();
    MPU6050_IIC_SDA_GPIO_CLK_ENABLE();
    
    /* 初始化SCL引脚 */
    gpio_init_struct.Pin    = MPU6050_IIC_SCL_GPIO_PIN;      /* SCL引脚 */
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;           /* 推挽输出 */
    gpio_init_struct.Pull   = GPIO_PULLUP;                   /* 上拉 */
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(MPU6050_IIC_SCL_GPIO_PORT, &gpio_init_struct);
    
    /* 初始化SDA引脚 */
    gpio_init_struct.Pin    = MPU6050_IIC_SDA_GPIO_PIN;      /* SDA引脚 */
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_OD;           /* 开漏输出 */
    HAL_GPIO_Init(MPU6050_IIC_SDA_GPIO_PORT, &gpio_init_struct);
    
    mpu6050_iic_stop();
}
