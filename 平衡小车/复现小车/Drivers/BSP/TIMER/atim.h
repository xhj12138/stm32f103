/**
 ****************************************************************************************************
 * @file        atim.h
 * @author      Xia
<<<<<<< HEAD
 * @version     V1.1
 * @date        2023-08-18
=======
 * @version     V1.0
 * @date        2023-08-14
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 * @brief       高级定时器 驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的高级定时器驱动
 * 用TIM1的CH1和CH4发出两路PWM
 *
 *
<<<<<<< HEAD
 * 修改说明
 * V1.0 20230813
 * 第一次发布
 * V1.1 20230818
 * 1.删除死区刹车部分，对于本项目没有用处，且之前导致PWM没有产生的原因就是使能刹车
 *
 *
=======
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 ****************************************************************************************************
 */

#ifndef __ATIM_H
#define __ATIM_H

#include "./SYSTEM/sys/sys.h"

/******************************************************************************************/
/* 高级定时器 定义 */


#define ATIM_TIM1_PWM_CH1_GPIO_PORT            GPIOA
#define ATIM_TIM1_PWM_CH1_GPIO_PIN             GPIO_PIN_8
#define ATIM_TIM1_PWM_CH1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */
#define ATIM_TIM1_PWM_CH4_GPIO_PORT            GPIOA
#define ATIM_TIM1_PWM_CH4_GPIO_PIN             GPIO_PIN_11
#define ATIM_TIM1_PWM_CH4_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA口时钟使能 */

#define ATIM_TIM1_PWM                          TIM1
#define ATIM_TIM1_PWM_IRQn                     TIM1_UP_IRQn
#define ATIM_TIM1_PWM_IRQHandler               TIM1_UP_IRQHandler
#define ATIM_TIM1_PWM_CH1                      TIM_CHANNEL_1                                  /* 通道Y,  1<= Y <=4 */
#define ATIM_TIM1_PWM_CH1_CCRX                 TIM1->CCR1                                     /* 通道Y的输出比较寄存器 */
#define ATIM_TIM1_PWM_CH1_CLK_ENABLE()         do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)     /* TIM1 时钟使能 */
#define ATIM_TIM1_PWM_CH4                      TIM_CHANNEL_4                                  /* 通道Y,  1<= Y <=4 */
#define ATIM_TIM1_PWM_CH4_CCRX                 TIM1->CCR4                                     /* 通道Y的输出比较寄存器 */
#define ATIM_TIM1_PWM_CH4_CLK_ENABLE()         do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)     /* TIM1 时钟使能 */


/******************************************************************************************/
void atim_tim1_pwm_init(uint16_t psc, uint16_t arr);

#endif

















