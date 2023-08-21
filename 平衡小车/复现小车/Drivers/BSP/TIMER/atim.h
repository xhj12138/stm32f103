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
 * @brief       �߼���ʱ�� ��������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС���ĸ߼���ʱ������
 * ��TIM1��CH1��CH4������·PWM
 *
 *
<<<<<<< HEAD
 * �޸�˵��
 * V1.0 20230813
 * ��һ�η���
 * V1.1 20230818
 * 1.ɾ������ɲ�����֣����ڱ���Ŀû���ô�����֮ǰ����PWMû�в�����ԭ�����ʹ��ɲ��
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
/* �߼���ʱ�� ���� */


#define ATIM_TIM1_PWM_CH1_GPIO_PORT            GPIOA
#define ATIM_TIM1_PWM_CH1_GPIO_PIN             GPIO_PIN_8
#define ATIM_TIM1_PWM_CH1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */
#define ATIM_TIM1_PWM_CH4_GPIO_PORT            GPIOA
#define ATIM_TIM1_PWM_CH4_GPIO_PIN             GPIO_PIN_11
#define ATIM_TIM1_PWM_CH4_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */

#define ATIM_TIM1_PWM                          TIM1
#define ATIM_TIM1_PWM_IRQn                     TIM1_UP_IRQn
#define ATIM_TIM1_PWM_IRQHandler               TIM1_UP_IRQHandler
#define ATIM_TIM1_PWM_CH1                      TIM_CHANNEL_1                                  /* ͨ��Y,  1<= Y <=4 */
#define ATIM_TIM1_PWM_CH1_CCRX                 TIM1->CCR1                                     /* ͨ��Y������ȽϼĴ��� */
#define ATIM_TIM1_PWM_CH1_CLK_ENABLE()         do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)     /* TIM1 ʱ��ʹ�� */
#define ATIM_TIM1_PWM_CH4                      TIM_CHANNEL_4                                  /* ͨ��Y,  1<= Y <=4 */
#define ATIM_TIM1_PWM_CH4_CCRX                 TIM1->CCR4                                     /* ͨ��Y������ȽϼĴ��� */
#define ATIM_TIM1_PWM_CH4_CLK_ENABLE()         do{ __HAL_RCC_TIM1_CLK_ENABLE(); }while(0)     /* TIM1 ʱ��ʹ�� */


/******************************************************************************************/
void atim_tim1_pwm_init(uint16_t psc, uint16_t arr);

#endif

















