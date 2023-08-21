/**
 ****************************************************************************************************
 * @file        led.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       LED ��������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС����LED������LED����PA4
 *
<<<<<<< HEAD
 *
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


#ifndef _LED_H
#define _LED_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ���� ���� */

#define LED_GPIO_PORT                  GPIOA
#define LED_GPIO_PIN                   GPIO_PIN_4
#define LED_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)             /* PB��ʱ��ʹ�� */

/******************************************************************************************/
/* LED�˿ڶ��� */
#define LED(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)      /* LED��ת */


/* LEDȡ������ */
#define LED_TOGGLE()   do{ HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_GPIO_PIN); }while(0)        /* ��תLED0 */

/******************************************************************************************/
/* �ⲿ�ӿں���*/
void led_init(void);                                                                            /* ��ʼ�� */

#endif
