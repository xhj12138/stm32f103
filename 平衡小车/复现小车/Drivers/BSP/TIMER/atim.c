/**
 ****************************************************************************************************
 * @file        atim.c
 * @author      Xia
<<<<<<< HEAD
 * @version     V1.1
 * @date        2023-08-18
=======
 * @version     V1.0
 * @date        2023-08-13
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 * @brief       �߼���ʱ�� ��������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС���ĸ߼���ʱ������
 * ��TIM1��CH1��CH4������·PWM
 *
<<<<<<< HEAD
 *
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


#include "./BSP/TIMER/atim.h"
#include "./BSP/TIMER/gtim.h"
<<<<<<< HEAD
#include "./BSP/CONTROL/control.h"
=======
#include "control.h"
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 
TIM_HandleTypeDef g_tim1_handle;

/* c8t6��Ψһһ���߼���ʱ�� */
/**
 * @brief       �߼���ʱ��TIM1 ͨ��1��ͨ��4 PWM���ģʽ ��ʼ������
 * @note
 *              �߼���ʱ����ʱ������APB2, ��PCLK2 = 72Mhz, ��������PPRE2����Ƶ, ���
 *              �߼���ʱ��ʱ�� = 72Mhz�߼���ʱ��ʱ�� = 72Mhz 
 *              ��ʱ�����ʱ����㷽��: Tout = ((arr + 1) * (psc + 1)) / Ft us. 
 *              Ft=��ʱ������Ƶ��,��λ:Mhz 
 * @param       arr: �Զ���װֵ 
 * @param       psc: ʱ��Ԥ��Ƶ�� 
 * @retval ��
 */
void atim_tim1_pwm_init(uint16_t psc, uint16_t arr)
{
    TIM_OC_InitTypeDef sConfigOC = {0};
<<<<<<< HEAD
//    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
=======
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    
    /* 1.ͨ��TIM_HandleTypeDef��ʼTIM1�Ĳ��� */
    g_tim1_handle.Instance = ATIM_TIM1_PWM;
    g_tim1_handle.Init.Prescaler = psc;                                         /* Ԥ��Ƶϵ�� */
    g_tim1_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                        /* ���� */
    g_tim1_handle.Init.Period = arr;                                            /* �Զ���װ��ֵ */
    g_tim1_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                  /* ʱ�Ӳ���Ƶ */
    g_tim1_handle.Init.RepetitionCounter = 0;                                   /* �������ظ������� */
    g_tim1_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;       /* ����Ӱ�ӼĴ������л��� */
    HAL_TIM_PWM_Init(&g_tim1_handle);
    
    /* 2.����PWM��� */
    /* �����������������Ҫ��������channel�� */
    sConfigOC.OCMode = TIM_OCMODE_PWM1;                                         /* PWMģʽ1 */
    sConfigOC.Pulse = 0;                                                        /* ��������ռ�ձȣ���ʼ��Ϊ0 */
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;                                 /* �������Ϊ�ߵ�ƽ */
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;                               /* �������ͨ��Ҳ�Ǹߵ�ƽ */
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;                                  /* ��ʹ�ÿ���ģʽ */
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;                              /* ����ɲ���Ż���Ч������״̬�µ͵�ƽ */
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;                            /* ����ɲ���Ż���Ч������״̬�µ͵�ƽ */
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, ATIM_TIM1_PWM_CH1);
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, ATIM_TIM1_PWM_CH4);
    
<<<<<<< HEAD
//    /* 3.������������ */
//    /* ����״̬�ر����� */
//    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
//    /* ����ģʽ�Ĺر����״̬ */
//    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
//    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;                         /* �رռĴ��������� */
//    sBreakDeadTimeConfig.DeadTime = 0;                                          /* ��ʼ����ȥʱ������Ϊ0 */
//    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;                        /* ʧ��ɲ������ */
//    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;                /* ɲ��������Ч�źż���Ϊ�� */
//    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;         /* δʹ��AOE��ɲ���󲻻��Զ��ָ� */
//    HAL_TIMEx_ConfigBreakDeadTime(&g_tim1_handle, &sBreakDeadTimeConfig);
=======
    /* 3.������������ */
    /* ����״̬�ر����� */
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    /* ����ģʽ�Ĺر����״̬ */
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;                         /* �رռĴ��������� */
    sBreakDeadTimeConfig.DeadTime = 0;                                          /* ��ʼ����ȥʱ������Ϊ0 */
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_ENABLE;                         /* ʹ��ɲ������ */
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;                /* ɲ��������Ч�źż���Ϊ�� */
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;         /* δʹ��AOE��ɲ���󲻻��Զ��ָ� */
    HAL_TIMEx_ConfigBreakDeadTime(&g_tim1_handle, &sBreakDeadTimeConfig);
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    
    /* 4.����PWM��� */
    HAL_TIM_PWM_Start(&g_tim1_handle, ATIM_TIM1_PWM_CH1);
    HAL_TIM_PWM_Start(&g_tim1_handle, ATIM_TIM1_PWM_CH4);
    
<<<<<<< HEAD
//    __HAL_TIM_ENABLE_IT(&g_tim1_handle,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */
//    __HAL_TIM_CLEAR_FLAG(&g_tim1_handle,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
=======
    __HAL_TIM_ENABLE_IT(&g_tim1_handle,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */
    __HAL_TIM_CLEAR_FLAG(&g_tim1_handle,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
}

/* ��MSP�����ж���NVIC��GPIO�� */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == ATIM_TIM1_PWM)
    {
        GPIO_InitTypeDef gpio_init_struct;                      /* GPIO��� */
        ATIM_TIM1_PWM_CH1_CLK_ENABLE();                         /* ����TIM1ʱ�� */
        ATIM_TIM1_PWM_CH4_CLK_ENABLE();
        ATIM_TIM1_PWM_CH1_GPIO_CLK_ENABLE();                    /* ����GPIOAʱ�� */
        ATIM_TIM1_PWM_CH4_GPIO_CLK_ENABLE();
        
        /* ��ʼ��GPIO */
<<<<<<< HEAD
        gpio_init_struct.Pin = ATIM_TIM1_PWM_CH1_GPIO_PIN;      /* ѡ����ʱ��1ͨ��1���� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ����������� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;           /* ���� */
        HAL_GPIO_Init(ATIM_TIM1_PWM_CH1_GPIO_PORT, &gpio_init_struct);
        
        gpio_init_struct.Pin = ATIM_TIM1_PWM_CH4_GPIO_PIN;      /* ѡ����ʱ��1ͨ��4���� */
        HAL_GPIO_Init(ATIM_TIM1_PWM_CH4_GPIO_PORT, &gpio_init_struct);
=======
        gpio_init_struct.Pin = ATIM_TIM1_PWM_CH1_GPIO_PIN | ATIM_TIM1_PWM_CH4_GPIO_PIN;      /* ѡ����ʱ��1ͨ��1��ͨ��4���� */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* ����������� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;           /* ���� */
        HAL_GPIO_Init(ATIM_TIM1_PWM_CH1_GPIO_PORT, &gpio_init_struct);
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    }
}








