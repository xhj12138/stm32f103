/**
 ****************************************************************************************************
 * @file        gtim.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       ͨ�ö�ʱ�� ��������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС����ͨ�ö�ʱ����������
 * TIM2��TIM4��������������
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

#ifndef __GTIM_H
#define __GTIM_H

#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ͨ�ö�ʱ�� ���� */

 
#define GTIM_TIM2_ENCODER_CH1_GPIO_PORT         GPIOA
#define GTIM_TIM2_ENCODER_CH1_GPIO_PIN          GPIO_PIN_0
#define GTIM_TIM2_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA��ʱ��ʹ�� */

#define GTIM_TIM2_ENCODER_CH2_GPIO_PORT         GPIOA
#define GTIM_TIM2_ENCODER_CH2_GPIO_PIN          GPIO_PIN_1
#define GTIM_TIM2_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA��ʱ��ʹ�� */

#define GTIM_TIM2_ENCODER                       TIM2                                         /* TIM2 */
#define GTIM_TIM2_ENCODER_INT_IRQn              TIM2_IRQn
#define GTIM_TIM2_ENCODER_INT_IRQHandler        TIM2_IRQHandler

#define GTIM_TIM2_ENCODER_CH1                   TIM_CHANNEL_1                                /* ͨ��1 */
#define GTIM_TIM2_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM2_CLK_ENABLE(); }while(0)   /* TIM2 ʱ��ʹ�� */

#define GTIM_TIM2_ENCODER_CH2                   TIM_CHANNEL_2                                /* ͨ��2 */
#define GTIM_TIM2_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM2_CLK_ENABLE(); }while(0)   /* TIM2 ʱ��ʹ�� */


#define GTIM_TIM4_ENCODER_CH1_GPIO_PORT         GPIOB
#define GTIM_TIM4_ENCODER_CH1_GPIO_PIN          GPIO_PIN_6
#define GTIM_TIM4_ENCODER_CH1_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)  /* PB��ʱ��ʹ�� */

#define GTIM_TIM4_ENCODER_CH2_GPIO_PORT         GPIOB
#define GTIM_TIM4_ENCODER_CH2_GPIO_PIN          GPIO_PIN_7
#define GTIM_TIM4_ENCODER_CH2_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)  /* PB��ʱ��ʹ�� */

#define GTIM_TIM4_ENCODER                       TIM4                                         /* TIM4 */
#define GTIM_TIM4_ENCODER_INT_IRQn              TIM4_IRQn
#define GTIM_TIM4_ENCODER_INT_IRQHandler        TIM4_IRQHandler

#define GTIM_TIM4_ENCODER_CH1                   TIM_CHANNEL_1                                /* ͨ��1 */
#define GTIM_TIM4_ENCODER_CH1_CLK_ENABLE()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)   /* TIM4 ʱ��ʹ�� */

#define GTIM_TIM4_ENCODER_CH2                   TIM_CHANNEL_2                                /* ͨ��2 */
#define GTIM_TIM4_ENCODER_CH2_CLK_ENABLE()      do{ __HAL_RCC_TIM4_CLK_ENABLE(); }while(0)   /* TIM4 ʱ��ʹ�� */


<<<<<<< HEAD
///* �����������ṹ�� */
//typedef struct 
//{
//  int encode_old;                  /* ��һ�μ���ֵ */
//  int encode_now;                  /* ��ǰ����ֵ */
//  float speed;                     /* �������ٶ� */
//} ENCODE_TypeDef;

//extern ENCODE_TypeDef g_encode2;    /* �������������� */
//extern ENCODE_TypeDef g_encode4;    /* �������������� */
=======
/* �����������ṹ�� */
typedef struct 
{
  int encode_old;                  /* ��һ�μ���ֵ */
  int encode_now;                  /* ��ǰ����ֵ */
  float speed;                     /* �������ٶ� */
} ENCODE_TypeDef;

extern ENCODE_TypeDef g_encode2;    /* �������������� */
extern ENCODE_TypeDef g_encode4;    /* �������������� */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
/******************************************************************************************/
void gtim_tim2_encoder_init(uint16_t psc, uint16_t arr);
void gtim_tim4_encoder_init(uint16_t psc, uint16_t arr);
int gtim2_get_encode(void);                                          /* ��ȡ�������ܼ���ֵ */
int gtim4_get_encode(void);                                          /* ��ȡ�������ܼ���ֵ */



#endif

















