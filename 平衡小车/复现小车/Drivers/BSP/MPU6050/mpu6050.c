/**
 ****************************************************************************************************
 * @file        mpu6050.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       MPU6050模块驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车完成MPU6050的初始化与读数据
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

#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/mpu6050_iic.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       MPU6050硬件初始化
 * @param       无
 * @retval      无
 */
static void mpu6050_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* 使能AD0引脚GPIO的时钟 */
    MPU6050_AD0_GPIO_CLK_ENABLE();
    
    /* 初始化AD0引脚 */
    gpio_init_struct.Pin    = MPU6050_AD0_GPIO_PIN;     /* AD0引脚 */
    gpio_init_struct.Mode   = GPIO_MODE_IT_FALLING;     /* 下降沿触发检测的外部中断模式 */
    gpio_init_struct.Pull   = GPIO_PULLUP;              /* 上拉 */
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;     /* 高速 */
    HAL_GPIO_Init(MPU6050_AD0_GPIO_PORT, &gpio_init_struct);
    
    /* 控制MPU6050的AD0引脚为低电平
     * 设置其IIC的从机地址为0x68
     */
    MPU6050_AD0(0);
}

/**
 * @brief       往MPU6050的指定寄存器连续写入指定数据
 * @param       addr: MPU6050的IIC通讯地址
 *              reg : MPU6050寄存器地址
 *              len : 写入的长度
 *              dat : 写入的数据
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_write(uint8_t addr,uint8_t reg, uint8_t len, uint8_t *dat)
{
    uint8_t i;
    
    mpu6050_iic_start();
    mpu6050_iic_send_byte((addr << 1) | 0);
    if (mpu6050_iic_wait_ack() == 1)
    {
        mpu6050_iic_stop();
        return MPU6050_EACK;
    }
    mpu6050_iic_send_byte(reg);
    if (mpu6050_iic_wait_ack() == 1)
    {
        mpu6050_iic_stop();
        return MPU6050_EACK;
    }
    for (i=0; i<len; i++)
    {
        mpu6050_iic_send_byte(dat[i]);
        if (mpu6050_iic_wait_ack() == 1)
        {
            mpu6050_iic_stop();
            return MPU6050_EACK;
        }
    }
    mpu6050_iic_stop();
    return MPU6050_EOK;
}

/**
 * @brief       往MPU6050的指定寄存器写入一字节数据
 * @param       addr: MPU6050的IIC通讯地址
 *              reg : MPU6050寄存器地址
 *              dat : 写入的数据
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_write_byte(uint8_t addr, uint8_t reg, uint8_t dat)
{
    return mpu6050_write(addr, reg, 1, &dat);
}

/**
 * @brief       连续读取MPU6050指定寄存器的值
 * @param       addr: MPU6050的IIC通讯地址
 *              reg : MPU6050寄存器地址
 *              len: 读取的长度
 *              dat: 存放读取到的数据的地址
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_read(uint8_t addr, uint8_t reg, uint8_t len, uint8_t *dat)
{
    mpu6050_iic_start();
    mpu6050_iic_send_byte((addr << 1) | 0);
    if (mpu6050_iic_wait_ack() == 1)
    {
        mpu6050_iic_stop();
        return MPU6050_EACK;
    }
    mpu6050_iic_send_byte(reg);
    if (mpu6050_iic_wait_ack() == 1)
    {
        mpu6050_iic_stop();
        return MPU6050_EACK;
    }
    mpu6050_iic_start();
    mpu6050_iic_send_byte((addr << 1) | 1);
    if (mpu6050_iic_wait_ack() == 1)
    {
        mpu6050_iic_stop();
        return MPU6050_EACK;
    }
    while (len)
    {
        *dat = mpu6050_iic_read_byte((len > 1) ? 1 : 0);
        len--;
        dat++;
    }
    mpu6050_iic_stop();
    return MPU6050_EOK;
}

/**
 * @brief       读取MPU6050指定寄存器的值
 * @param       addr: MPU6050的IIC通讯地址
 *              reg : MPU6050寄存器地址
 *              dat: 读取到的寄存器的值
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_read_byte(uint8_t addr, uint8_t reg, uint8_t *dat)
{
    return mpu6050_read(addr, reg, 1, dat);
}

/**
 * @brief       MPU6050软件复位
 * @param       无
 * @retval      无
 */
void mpu6050_sw_reset(void)
{
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT1_REG, 0x80);
    delay_ms(100);
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT1_REG, 0x00);
}

/**
 * @brief       MPU6050设置陀螺仪传感器量程范围
 * @param       frs: 0 --> ±250dps
 *                   1 --> ±500dps
 *                   2 --> ±1000dps
 *                   3 --> ±2000dps
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_set_gyro_fsr(uint8_t fsr)
{
    return mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_GYRO_CFG_REG, fsr << 3);
}

/**
 * @brief       MPU6050设置加速度传感器量程范围
 * @param       frs: 0 --> ±2g
 *                   1 --> ±4g
 *                   2 --> ±8g
 *                   3 --> ±16g
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_set_accel_fsr(uint8_t fsr)
{
    return mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_ACCEL_CFG_REG, fsr << 3);
}

/**
 * @brief       MPU6050设置数字低通滤波器频率
 * @param       lpf: 数字低通滤波器的频率（Hz）
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_set_lpf(uint16_t lpf)
{
    uint8_t dat;
    
    if (lpf >= 188)
    {
        dat = 1;
    }
    else if (lpf >= 98)
    {
        dat = 2;
    }
    else if (lpf >= 42)
    {
        dat = 3;
    }
    else if (lpf >= 20)
    {
        dat = 4;
    }
    else if (lpf >= 10)
    {
        dat = 5;
    }
    else
    {
        dat = 6;
    }
    
    return mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_CFG_REG, dat);
}

/**
 * @brief       MPU6050设置采样率
 * @param       rate: 采样率（4~1000Hz）
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_set_rate(uint16_t rate)
{
    uint8_t ret;
    uint8_t dat;
    
    if (rate > 1000)
    {
        rate = 1000;
    }
    
    if (rate < 4)
    {
        rate = 4;
    }
    
    dat = 1000 / rate - 1;
    ret = mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_SAMPLE_RATE_REG, dat);
    if (ret != MPU6050_EOK)
    {
        return ret;
    }
    
    ret = mpu6050_set_lpf(rate >> 1);
    if (ret != MPU6050_EOK)
    {
        return ret;
    }
    
    return MPU6050_EOK;
}

/**
 * @brief       MPU6050获取温度值
 * @param       temperature: 获取到的温度值（扩大了10倍）
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_get_temperature(int16_t *temp)
{
    uint8_t dat[2];
    uint8_t ret;
    int16_t raw = 0;
    
    ret = mpu6050_read(MPU6050_IIC_ADDR, MPU_TEMP_OUTH_REG, 2, dat);
    if (ret == MPU6050_EOK)
    {
        raw = ((uint16_t)dat[0] << 8) | dat[1];
        *temp = (int16_t)((36.53f + ((float)raw / 340)) * 10);
    }
    
    return ret;
}

/**
 * @brief       MPU6050获取陀螺仪值
 * @param       gx，gy，gz: 陀螺仪x、y、z轴的原始度数（带符号）
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_get_gyroscope(int16_t *gx, int16_t *gy, int16_t *gz)
{
    uint8_t dat[6];
    uint8_t ret;
    
    ret =  mpu6050_read(MPU6050_IIC_ADDR, MPU_GYRO_XOUTH_REG, 6, dat);
    if (ret == MPU6050_EOK)
    {
        *gx = ((uint16_t)dat[0] << 8) | dat[1];
        *gy = ((uint16_t)dat[2] << 8) | dat[3];
        *gz = ((uint16_t)dat[4] << 8) | dat[5];
    }
    
    return ret;
}

/**
 * @brief       MPU6050获取加速度值
 * @param       ax，ay，az: 加速度x、y、z轴的原始度数（带符号）
 * @retval      MPU6050_EOK : 函数执行成功
 *              MPU6050_EACK: IIC通讯ACK错误，函数执行失败
 */
uint8_t mpu6050_get_accelerometer(int16_t *ax, int16_t *ay, int16_t *az)
{
    uint8_t dat[6];
    uint8_t ret;
    
    ret =  mpu6050_read(MPU6050_IIC_ADDR, MPU_ACCEL_XOUTH_REG, 6, dat);
    if (ret == MPU6050_EOK)
    {
        *ax = ((uint16_t)dat[0] << 8) | dat[1];
        *ay = ((uint16_t)dat[2] << 8) | dat[3];
        *az = ((uint16_t)dat[4] << 8) | dat[5];
    }
    
    return ret;
}

/**
 * @brief       MPU6050初始化
 * @param       无
 * @retval      MPU6050_EOK: 函数执行成功
 *              MPU6050_EID: 获取ID错误，函数执行失败
 */
uint8_t mpu6050_init(void)
{
    uint8_t id;
    
    mpu6050_hw_init();                                                   /* MPU6050硬件初始化 */
    mpu6050_iic_init();                                                  /* 初始化IIC接口 */
    mpu6050_sw_reset();                                                  /* MPU050软件复位 */
    mpu6050_set_gyro_fsr(3);                                             /* 陀螺仪传感器，±2000dps */
    mpu6050_set_accel_fsr(0);                                            /* 加速度传感器，±2g */
<<<<<<< HEAD
    //mpu6050_set_rate(50);                                                /* 采样率，50Hz */
=======
    mpu6050_set_rate(50);                                                /* 采样率，50Hz */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_INT_EN_REG, 0X00);          /* 关闭所有中断 */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_USER_CTRL_REG, 0X00);       /* 关闭IIC主模式 */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_FIFO_EN_REG, 0X00);         /* 关闭FIFO */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_INTBP_CFG_REG, 0X80);       /* INT引脚低电平有效 */
    mpu6050_read_byte(MPU6050_IIC_ADDR, MPU_DEVICE_ID_REG, &id);         /* 读取设备ID */
    if (id != MPU6050_IIC_ADDR)
    {
        return MPU6050_EID;
    }
<<<<<<< HEAD
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT1_REG, 0x01);       /* 设置CLKSEL，PLL X轴为参考 */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT2_REG, 0x00);       /* 加速度与陀螺仪都工作 */
    //mpu6050_set_rate(50);                                                /* 采样率，50Hz */
=======
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT1_REG, 0x02);       /* 设置CLKSEL，PLL Y轴为参考 */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT2_REG, 0x00);       /* 加速度与陀螺仪都工作 */
    mpu6050_set_rate(50);                                                /* 采样率，50Hz */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    
    return MPU6050_EOK;
}
