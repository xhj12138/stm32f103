/**
 ****************************************************************************************************
 * @file        exti.h
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

#ifndef __EXTI_H
#define __EXTI_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* 引脚 和 中断编号 & 中断服务函数 定义 */ 

#define MPU6050_INT_GPIO_PORT              GPIOA
#define MPU6050_INT_GPIO_PIN               GPIO_PIN_12
#define MPU6050_INT_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PE口时钟使能 */
#define MPU6050_INT_IRQn                   EXTI15_10_IRQn
#define MPU6050_INT_IRQHandler             EXTI15_10_IRQHandler

#define MPU6050_read        HAL_GPIO_ReadPin(MPU6050_INT_GPIO_PORT, MPU6050_INT_GPIO_PIN)     /* 读取MPU6050_INT引脚 */

/******************************************************************************************/


void extix_init(void);  /* 外部中断初始化 */

#endif

























