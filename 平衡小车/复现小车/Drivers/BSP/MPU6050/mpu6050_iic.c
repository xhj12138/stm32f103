/**
 ****************************************************************************************************
 * @file        mpu6050_iic.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       MPU6050ģ��IIC�ӿ���������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС�����ʵ��IIC����������MPU6050
 *
<<<<<<< HEAD
 *
 * �޸�˵��
 * V1.0 20230813
 * ��һ�η���
 *
 *
=======
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 ****************************************************************************************************
 */

#include "./BSP/MPU6050/mpu6050_iic.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       IIC�ӿ���ʱ���������ڿ���IIC��д�ٶ�
 * @param       ��
 * @retval      ��
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
 * @brief       ����IIC��ʼ�ź�
 * @param       ��
 * @retval      ��
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
 * @brief       ����IICֹͣ�ź�
 * @param       ��
 * @retval      ��
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
 * @brief       �ȴ�IICӦ���ź�
 * @param       ��
 * @retval      0: Ӧ���źŽ��ճɹ�
 *              1: Ӧ���źŽ���ʧ��
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
 * @brief       ����ACKӦ���ź�
 * @param       ��
 * @retval      ��
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
 * @brief       ������ACKӦ���ź�
 * @param       ��
 * @retval      ��
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
 * @brief       IIC����һ���ֽ�
 * @param       dat: Ҫ���͵�����
 * @retval      ��
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
 * @brief       IIC����һ���ֽ�
 * @param       ack: ack=1ʱ������ack; ack=0ʱ������nack
 * @retval      ���յ�������
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
 * @brief       ��ʼ��IIC�ӿ�
 * @param       ��
 * @retval      ��
 */
void mpu6050_iic_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* ʹ��SCL��SDA����GPIO��ʱ�� */
    MPU6050_IIC_SCL_GPIO_CLK_ENABLE();
    MPU6050_IIC_SDA_GPIO_CLK_ENABLE();
    
    /* ��ʼ��SCL���� */
    gpio_init_struct.Pin    = MPU6050_IIC_SCL_GPIO_PIN;      /* SCL���� */
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_PP;           /* ������� */
    gpio_init_struct.Pull   = GPIO_PULLUP;                   /* ���� */
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(MPU6050_IIC_SCL_GPIO_PORT, &gpio_init_struct);
    
    /* ��ʼ��SDA���� */
    gpio_init_struct.Pin    = MPU6050_IIC_SDA_GPIO_PIN;      /* SDA���� */
    gpio_init_struct.Mode   = GPIO_MODE_OUTPUT_OD;           /* ��©��� */
    HAL_GPIO_Init(MPU6050_IIC_SDA_GPIO_PORT, &gpio_init_struct);
    
    mpu6050_iic_stop();
}
