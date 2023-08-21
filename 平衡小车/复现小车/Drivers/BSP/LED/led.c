/**
 ****************************************************************************************************
 * @file        led.c
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


#include "./BSP/LED/led.h"


/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    LED_GPIO_CLK_ENABLE();                                 /* LEDʱ��ʹ�� */

    gpio_init_struct.Pin = LED_GPIO_PIN;                   /* LED���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(LED_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED���� */

    LED(0);                                                /* �ر� LED */
}
