/**
 ****************************************************************************************************
 * @file        mpu6050_demo.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-14
 * @brief       MPU6050模块测试实验
 ****************************************************************************************************
 * @attention
 *
 * 配置好MPU6050后，读取和计算数据
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
 * @brief       例程演示入口函数
 * @param       无
 * @retval      无
 */
void mpu6050_demo_run(void)
{
    uint8_t ret;
    float pit, rol, yaw;
    int16_t acc_x, acc_y, acc_z;
    int16_t gyr_x, gyr_y, gyr_z;
    int16_t temp;
    
    /* 初始化MPU6050 */
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
    
    /* 初始化MPU6050 DMP */
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
        
        /* 获取MPU6050 DMP处理后的数据 */
        ret  = mpu6050_dmp_get_data(&pit, &rol, &yaw);
        /* 获取MPU050加速度值 */
        ret += mpu6050_get_accelerometer(&acc_x, &acc_y, &acc_z);
        /* 获取MPU6050陀螺仪值 */
        ret += mpu6050_get_gyroscope(&gyr_x, &gyr_y, &gyr_z);
        /* 获取MPU6050温度值 */
        ret += mpu6050_get_temperature(&temp);
        if (ret == 0)
        {
            /* 上传相关数据信息至串口调试助手 */
            printf("pit: %.2f, rol: %.2f, yaw: %.2f, ", pit, rol, yaw);
            printf("acc_x: %d, acc_y: %d, acc_z: %d, ", acc_x, acc_y, acc_z);
            printf("gyr_x: %d, gyr_y: %d, gyr_z: %d, ", gyr_x, gyr_y, gyr_z);
            printf("temp: %d\r\n", temp);
        }
    }
}
