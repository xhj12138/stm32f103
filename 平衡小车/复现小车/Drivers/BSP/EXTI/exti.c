/**
 ****************************************************************************************************
 * @file        exti.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       外部中断 驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车，用外部中断完成50ms的精准计时
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

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/EXTI/exti.h"

volatile uint8_t delay_flag, delay_50;     /* 提供延时的变量 */


/**
 * @brief       MPU6050_INT 外部中断服务程序
 * @param       无
 * @retval      无
 */
void MPU6050_INT_IRQHandler(void)
{
    if (MPU6050_read == 0)
<<<<<<< HEAD
    {
        if(delay_flag == 1)
        {
            delay_50++;
            if(delay_50 == 10)
            {
                delay_50 = 0;
                delay_flag = 0;/* 给主函数提供50ms的精准延时，示波器需要50ms高精度延时 */
            }
        }
    }
=======
            {
                if(delay_flag == 1)
                {
                    delay_50++;
                    if(delay_50 == 10)
                    {
                        delay_50 = 0;
                        delay_flag = 0;/* 给主函数提供50ms的精准延时，示波器需要50ms高精度延时 */
                    }
                }
            }
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    /* 调用中断处理公用函数 清除MPU6050_INT所在中断线 的中断标志位 */
    HAL_GPIO_EXTI_IRQHandler(MPU6050_INT_GPIO_PIN);
    /* HAL库默认先清中断再处理回调，退出时再清一次中断，避免按键抖动误触发 */
    __HAL_GPIO_EXTI_CLEAR_IT(MPU6050_INT_GPIO_PIN);
}


/**
 * @brief       外部中断初始化程序
 * @param       无
 * @retval      无
 */
void extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    MPU6050_INT_GPIO_CLK_ENABLE();                              /* MPU6050_INT时钟使能 */

    gpio_init_struct.Pin = MPU6050_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;               /* 下降沿触发 */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(MPU6050_INT_GPIO_PORT, &gpio_init_struct);    /* MPU6050_INT配置为下降沿触发中断 */

    HAL_NVIC_SetPriority(MPU6050_INT_IRQn, 1, 1);               /* 抢占1，子优先级1 */
    HAL_NVIC_EnableIRQ(MPU6050_INT_IRQn);                       /* 使能中断线15_10 */
}












