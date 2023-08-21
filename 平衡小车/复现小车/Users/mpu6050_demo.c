/**
 ****************************************************************************************************
 * @file        mpu6050_demo.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-14
 * @brief       MPU6050ģ�����ʵ��
 ****************************************************************************************************
 * @attention
 *
 * ���ú�MPU6050�󣬶�ȡ�ͼ�������
 *
 ****************************************************************************************************
 */

#include "mpu6050_demo.h"
#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/eMPL/inv_mpu.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"


/**
 * @brief       ������ʾ��ں���
 * @param       ��
 * @retval      ��
 */
void mpu6050_demo_run(void)
{
    uint8_t ret;
    float pit, rol, yaw;
    int16_t acc_x, acc_y, acc_z;
    int16_t gyr_x, gyr_y, gyr_z;
    int16_t temp;
    
    /* ��ʼ��MPU6050 */
    ret = mpu6050_init();
    if (ret != 0)
    {
        printf("MPU6050 init failed!\r\n");
        while (1)
        {
            LED_TOGGLE();
            delay_ms(200);
        }
    }
    
    /* ��ʼ��MPU6050 DMP */
    ret = mpu6050_dmp_init();
    if (ret != 0)
    {
        printf("MPU6050 DMP init failed!\r\n");
        while (1)
        {
            LED_TOGGLE();
            delay_ms(200);
        }
    }
    
    while (1)
    {
        usart_init(115200);
        
        /* ��ȡMPU6050 DMP���������� */
        ret  = mpu6050_dmp_get_data(&pit, &rol, &yaw);
        /* ��ȡMPU050���ٶ�ֵ */
        ret += mpu6050_get_accelerometer(&acc_x, &acc_y, &acc_z);
        /* ��ȡMPU6050������ֵ */
        ret += mpu6050_get_gyroscope(&gyr_x, &gyr_y, &gyr_z);
        /* ��ȡMPU6050�¶�ֵ */
        ret += mpu6050_get_temperature(&temp);
        if (ret == 0)
        {
            /* �ϴ����������Ϣ�����ڵ������� */
            printf("pit: %.2f, rol: %.2f, yaw: %.2f, ", pit, rol, yaw);
            printf("acc_x: %d, acc_y: %d, acc_z: %d, ", acc_x, acc_y, acc_z);
            printf("gyr_x: %d, gyr_y: %d, gyr_z: %d, ", gyr_x, gyr_y, gyr_z);
            printf("temp: %d\r\n", temp);
        }
    }
}
