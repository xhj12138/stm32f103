/**
 ****************************************************************************************************
 * @file        mpu6050.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       MPU6050ģ����������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС�����MPU6050�ĳ�ʼ���������
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

#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/mpu6050_iic.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       MPU6050Ӳ����ʼ��
 * @param       ��
 * @retval      ��
 */
static void mpu6050_hw_init(void)
{
    GPIO_InitTypeDef gpio_init_struct = {0};
    
    /* ʹ��AD0����GPIO��ʱ�� */
    MPU6050_AD0_GPIO_CLK_ENABLE();
    
    /* ��ʼ��AD0���� */
    gpio_init_struct.Pin    = MPU6050_AD0_GPIO_PIN;     /* AD0���� */
    gpio_init_struct.Mode   = GPIO_MODE_IT_FALLING;     /* �½��ش��������ⲿ�ж�ģʽ */
    gpio_init_struct.Pull   = GPIO_PULLUP;              /* ���� */
    gpio_init_struct.Speed  = GPIO_SPEED_FREQ_HIGH;     /* ���� */
    HAL_GPIO_Init(MPU6050_AD0_GPIO_PORT, &gpio_init_struct);
    
    /* ����MPU6050��AD0����Ϊ�͵�ƽ
     * ������IIC�Ĵӻ���ַΪ0x68
     */
    MPU6050_AD0(0);
}

/**
 * @brief       ��MPU6050��ָ���Ĵ�������д��ָ������
 * @param       addr: MPU6050��IICͨѶ��ַ
 *              reg : MPU6050�Ĵ�����ַ
 *              len : д��ĳ���
 *              dat : д�������
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
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
 * @brief       ��MPU6050��ָ���Ĵ���д��һ�ֽ�����
 * @param       addr: MPU6050��IICͨѶ��ַ
 *              reg : MPU6050�Ĵ�����ַ
 *              dat : д�������
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
 */
uint8_t mpu6050_write_byte(uint8_t addr, uint8_t reg, uint8_t dat)
{
    return mpu6050_write(addr, reg, 1, &dat);
}

/**
 * @brief       ������ȡMPU6050ָ���Ĵ�����ֵ
 * @param       addr: MPU6050��IICͨѶ��ַ
 *              reg : MPU6050�Ĵ�����ַ
 *              len: ��ȡ�ĳ���
 *              dat: ��Ŷ�ȡ�������ݵĵ�ַ
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
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
 * @brief       ��ȡMPU6050ָ���Ĵ�����ֵ
 * @param       addr: MPU6050��IICͨѶ��ַ
 *              reg : MPU6050�Ĵ�����ַ
 *              dat: ��ȡ���ļĴ�����ֵ
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
 */
uint8_t mpu6050_read_byte(uint8_t addr, uint8_t reg, uint8_t *dat)
{
    return mpu6050_read(addr, reg, 1, dat);
}

/**
 * @brief       MPU6050�����λ
 * @param       ��
 * @retval      ��
 */
void mpu6050_sw_reset(void)
{
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT1_REG, 0x80);
    delay_ms(100);
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT1_REG, 0x00);
}

/**
 * @brief       MPU6050���������Ǵ��������̷�Χ
 * @param       frs: 0 --> ��250dps
 *                   1 --> ��500dps
 *                   2 --> ��1000dps
 *                   3 --> ��2000dps
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
 */
uint8_t mpu6050_set_gyro_fsr(uint8_t fsr)
{
    return mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_GYRO_CFG_REG, fsr << 3);
}

/**
 * @brief       MPU6050���ü��ٶȴ��������̷�Χ
 * @param       frs: 0 --> ��2g
 *                   1 --> ��4g
 *                   2 --> ��8g
 *                   3 --> ��16g
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
 */
uint8_t mpu6050_set_accel_fsr(uint8_t fsr)
{
    return mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_ACCEL_CFG_REG, fsr << 3);
}

/**
 * @brief       MPU6050�������ֵ�ͨ�˲���Ƶ��
 * @param       lpf: ���ֵ�ͨ�˲�����Ƶ�ʣ�Hz��
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
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
 * @brief       MPU6050���ò�����
 * @param       rate: �����ʣ�4~1000Hz��
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
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
 * @brief       MPU6050��ȡ�¶�ֵ
 * @param       temperature: ��ȡ�����¶�ֵ��������10����
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
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
 * @brief       MPU6050��ȡ������ֵ
 * @param       gx��gy��gz: ������x��y��z���ԭʼ�����������ţ�
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
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
 * @brief       MPU6050��ȡ���ٶ�ֵ
 * @param       ax��ay��az: ���ٶ�x��y��z���ԭʼ�����������ţ�
 * @retval      MPU6050_EOK : ����ִ�гɹ�
 *              MPU6050_EACK: IICͨѶACK���󣬺���ִ��ʧ��
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
 * @brief       MPU6050��ʼ��
 * @param       ��
 * @retval      MPU6050_EOK: ����ִ�гɹ�
 *              MPU6050_EID: ��ȡID���󣬺���ִ��ʧ��
 */
uint8_t mpu6050_init(void)
{
    uint8_t id;
    
    mpu6050_hw_init();                                                   /* MPU6050Ӳ����ʼ�� */
    mpu6050_iic_init();                                                  /* ��ʼ��IIC�ӿ� */
    mpu6050_sw_reset();                                                  /* MPU050�����λ */
    mpu6050_set_gyro_fsr(3);                                             /* �����Ǵ���������2000dps */
    mpu6050_set_accel_fsr(0);                                            /* ���ٶȴ���������2g */
<<<<<<< HEAD
    //mpu6050_set_rate(50);                                                /* �����ʣ�50Hz */
=======
    mpu6050_set_rate(50);                                                /* �����ʣ�50Hz */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_INT_EN_REG, 0X00);          /* �ر������ж� */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_USER_CTRL_REG, 0X00);       /* �ر�IIC��ģʽ */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_FIFO_EN_REG, 0X00);         /* �ر�FIFO */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_INTBP_CFG_REG, 0X80);       /* INT���ŵ͵�ƽ��Ч */
    mpu6050_read_byte(MPU6050_IIC_ADDR, MPU_DEVICE_ID_REG, &id);         /* ��ȡ�豸ID */
    if (id != MPU6050_IIC_ADDR)
    {
        return MPU6050_EID;
    }
<<<<<<< HEAD
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT1_REG, 0x01);       /* ����CLKSEL��PLL X��Ϊ�ο� */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT2_REG, 0x00);       /* ���ٶ��������Ƕ����� */
    //mpu6050_set_rate(50);                                                /* �����ʣ�50Hz */
=======
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT1_REG, 0x02);       /* ����CLKSEL��PLL Y��Ϊ�ο� */
    mpu6050_write_byte(MPU6050_IIC_ADDR, MPU_PWR_MGMT2_REG, 0x00);       /* ���ٶ��������Ƕ����� */
    mpu6050_set_rate(50);                                                /* �����ʣ�50Hz */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    
    return MPU6050_EOK;
}
