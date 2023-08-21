/**
 ****************************************************************************************************
 * @file        gtim.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       通用定时器 驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的通用定时器驱动代码
 * TIM2与TIM4连接两个编码器
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

#ifndef __GTIM_H
#define __GTIM_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* 通用定时器 定义 */

 
#define GTIM_TIM2_ENCODER_CH1_GPIO_PORT         GPIOA
#define GTIM_TIM2_ENCODER_CH1_GPIO_PIN          GPIO_PIN_0
#define GTIM_TIM2_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA口时钟使能 */

#define GTIM_TIM2_ENCODER_CH2_GPIO_PORT         GPIOA
#define GTIM_TIM2_ENCODER_CH2_GPIO_PIN          GPIO_PIN_1
#define GTIM_TIM2_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA口时钟使能 */

#define GTIM_TIM2_ENCODER                       TIM2                                         /* TIM2 */
#define GTIM_TIM2_ENCODER_INT_IRQn              TIM2_IRQn
#define GTIM_TIM2_ENCODER_INT_IRQHandler        TIM2_IRQHandler

#define GTIM_TIM2_ENCODER_CH1                   TIM_CHANNEL_1                                /* 通道1 */
#define GTIM_TIM2_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM2_CLK_ENABLE(); }while(0)   /* TIM2 时钟使能 */

#define GTIM_TIM2_ENCODER_CH2                   TIM_CHANNEL_2                                /* 通道2 */
#define GTIM_TIM2_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM2_CLK_ENABLE(); }while(0)   /* TIM2 时钟使能 */


#define GTIM_TIM4_ENCODER_CH1_GPIO_PORT         GPIOB
#define GTIM_TIM4_ENCODER_CH1_GPIO_PIN          GPIO_PIN_6
#define GTIM_TIM4_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)  /* PB口时钟使能 */

#define GTIM_TIM4_ENCODER_CH2_GPIO_PORT         GPIOB
#define GTIM_TIM4_ENCODER_CH2_GPIO_PIN          GPIO_PIN_7
#define GTIM_TIM4_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)  /* PB口时钟使能 */

#define GTIM_TIM4_ENCODER                       TIM4                                         /* TIM4 */
#define GTIM_TIM4_ENCODER_INT_IRQn              TIM4_IRQn
#define GTIM_TIM4_ENCODER_INT_IRQHandler        TIM4_IRQHandler

#define GTIM_TIM4_ENCODER_CH1                   TIM_CHANNEL_1                                /* 通道1 */
#define GTIM_TIM4_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)   /* TIM4 时钟使能 */

#define GTIM_TIM4_ENCODER_CH2                   TIM_CHANNEL_2                                /* 通道2 */
#define GTIM_TIM4_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)   /* TIM4 时钟使能 */


<<<<<<< HEAD
///* 编码器参数结构体 */
//typedef struct 
//{
//  int encode_old;                  /* 上一次计数值 */
//  int encode_now;                  /* 当前计数值 */
//  float speed;                     /* 编码器速度 */
//} ENCODE_TypeDef;

//extern ENCODE_TypeDef g_encode2;    /* 编码器参数变量 */
//extern ENCODE_TypeDef g_encode4;    /* 编码器参数变量 */
=======
/* 编码器参数结构体 */
typedef struct 
{
  int encode_old;                  /* 上一次计数值 */
  int encode_now;                  /* 当前计数值 */
  float speed;                     /* 编码器速度 */
} ENCODE_TypeDef;

extern ENCODE_TypeDef g_encode2;    /* 编码器参数变量 */
extern ENCODE_TypeDef g_encode4;    /* 编码器参数变量 */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
/******************************************************************************************/
void gtim_tim2_encoder_init(uint16_t psc, uint16_t arr);
void gtim_tim4_encoder_init(uint16_t psc, uint16_t arr);
int gtim2_get_encode(void);                                          /* 获取编码器总计数值 */
int gtim4_get_encode(void);                                          /* 获取编码器总计数值 */



#endif

















