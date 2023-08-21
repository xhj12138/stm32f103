/**
 ****************************************************************************************************
 * @file        exti.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       �ⲿ�ж� ��������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС�������ⲿ�ж����50ms�ľ�׼��ʱ
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

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/EXTI/exti.h"

volatile uint8_t delay_flag, delay_50;     /* �ṩ��ʱ�ı��� */


/**
 * @brief       MPU6050_INT �ⲿ�жϷ������
 * @param       ��
 * @retval      ��
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
                delay_flag = 0;/* ���������ṩ50ms�ľ�׼��ʱ��ʾ������Ҫ50ms�߾�����ʱ */
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
                        delay_flag = 0;/* ���������ṩ50ms�ľ�׼��ʱ��ʾ������Ҫ50ms�߾�����ʱ */
                    }
                }
            }
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    /* �����жϴ����ú��� ���MPU6050_INT�����ж��� ���жϱ�־λ */
    HAL_GPIO_EXTI_IRQHandler(MPU6050_INT_GPIO_PIN);
    /* HAL��Ĭ�������ж��ٴ���ص����˳�ʱ����һ���жϣ����ⰴ�������󴥷� */
    __HAL_GPIO_EXTI_CLEAR_IT(MPU6050_INT_GPIO_PIN);
}


/**
 * @brief       �ⲿ�жϳ�ʼ������
 * @param       ��
 * @retval      ��
 */
void extix_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;

    MPU6050_INT_GPIO_CLK_ENABLE();                              /* MPU6050_INTʱ��ʹ�� */

    gpio_init_struct.Pin = MPU6050_INT_GPIO_PIN;
    gpio_init_struct.Mode = GPIO_MODE_IT_FALLING;               /* �½��ش��� */
    gpio_init_struct.Pull = GPIO_PULLUP;
    HAL_GPIO_Init(MPU6050_INT_GPIO_PORT, &gpio_init_struct);    /* MPU6050_INT����Ϊ�½��ش����ж� */

    HAL_NVIC_SetPriority(MPU6050_INT_IRQn, 1, 1);               /* ��ռ1�������ȼ�1 */
    HAL_NVIC_EnableIRQ(MPU6050_INT_IRQn);                       /* ʹ���ж���15_10 */
}












