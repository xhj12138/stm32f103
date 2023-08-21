/**
 ****************************************************************************************************
 * @file        gtim.c
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

#include "./BSP/TIMER/gtim.h"
#include "./BSP/TIMER/atim.h"
<<<<<<< HEAD
#include "./BSP/CONTROL/control.h"
=======
#include "control.h"
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735


TIM_HandleTypeDef g_tim2_encode_handle;         /* ��ʱ��2��� */
TIM_Encoder_InitTypeDef g_tim2_encoder_handle;  /* ��ʱ2��������� */
TIM_HandleTypeDef g_tim4_encode_handle;         /* ��ʱ��4��� */
TIM_Encoder_InitTypeDef g_tim4_encoder_handle;  /* ��ʱ4��������� */

void gtim_tim2_encoder_init(uint16_t psc, uint16_t arr)
{
    /* ��ʱ��x���� */
    g_tim2_encode_handle.Instance = GTIM_TIM2_ENCODER;                      /* ��ʱ��x */
    g_tim2_encode_handle.Init.Prescaler = psc;                              /* ��ʱ����Ƶ */
    g_tim2_encode_handle.Init.Period = arr;                                 /* �Զ���װ��ֵ */
    g_tim2_encode_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* ʱ�ӷ�Ƶ���� */
    
    /* ��ʱ��x���������� */
    g_tim2_encoder_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1��TI2����⣬4��Ƶ */
    g_tim2_encoder_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
    g_tim2_encoder_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
    g_tim2_encoder_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
    g_tim2_encoder_handle.IC1Filter = 10;                                   /* �˲������� */
    g_tim2_encoder_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
    g_tim2_encoder_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
    g_tim2_encoder_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
    g_tim2_encoder_handle.IC2Filter = 10;                                   /* �˲������� */
<<<<<<< HEAD
    HAL_TIM_Encoder_Init(&g_tim2_encode_handle, &g_tim2_encoder_handle);    /* ��ʼ����ʱ��x������ */
=======
    HAL_TIM_Encoder_Init(&g_tim2_encode_handle, &g_tim2_encoder_handle);/* ��ʼ����ʱ��x������ */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
     
    HAL_TIM_Encoder_Start(&g_tim2_encode_handle,GTIM_TIM2_ENCODER_CH1);     /* ʹ�ܱ�����ͨ��1 */
    HAL_TIM_Encoder_Start(&g_tim2_encode_handle,GTIM_TIM2_ENCODER_CH2);     /* ʹ�ܱ�����ͨ��2 */
//    __HAL_TIM_ENABLE_IT(&g_tim2_encode_handle,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */
//    __HAL_TIM_CLEAR_FLAG(&g_tim2_encode_handle,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
}


void gtim_tim4_encoder_init(uint16_t psc, uint16_t arr)
{
    /* ��ʱ��x���� */
    g_tim4_encode_handle.Instance = GTIM_TIM4_ENCODER;                      /* ��ʱ��x */
    g_tim4_encode_handle.Init.Prescaler = psc;                              /* ��ʱ����Ƶ */
    g_tim4_encode_handle.Init.Period = arr;                                 /* �Զ���װ��ֵ */
    g_tim4_encode_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* ʱ�ӷ�Ƶ���� */
    
    /* ��ʱ��x���������� */
    g_tim4_encoder_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1��TI2����⣬4��Ƶ */
    g_tim4_encoder_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
    g_tim4_encoder_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
    g_tim4_encoder_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
    g_tim4_encoder_handle.IC1Filter = 10;                                   /* �˲������� */
    g_tim4_encoder_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* ���뼫�ԣ��Ƿ��� */
    g_tim4_encoder_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* ����ͨ��ѡ�� */
    g_tim4_encoder_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* ����Ƶ */
    g_tim4_encoder_handle.IC2Filter = 10;                                   /* �˲������� */
    HAL_TIM_Encoder_Init(&g_tim4_encode_handle, &g_tim4_encoder_handle);/* ��ʼ����ʱ��x������ */
     
    HAL_TIM_Encoder_Start(&g_tim4_encode_handle,GTIM_TIM4_ENCODER_CH1);     /* ʹ�ܱ�����ͨ��1 */
    HAL_TIM_Encoder_Start(&g_tim4_encode_handle,GTIM_TIM4_ENCODER_CH2);     /* ʹ�ܱ�����ͨ��2 */
//    __HAL_TIM_ENABLE_IT(&g_tim4_encode_handle,TIM_IT_UPDATE);               /* ʹ�ܸ����ж� */
//    __HAL_TIM_CLEAR_FLAG(&g_tim4_encode_handle,TIM_IT_UPDATE);              /* ��������жϱ�־λ */
}


/**
 * @brief       ��ʱ���ײ�������ʱ��ʹ�ܣ���������
                �˺����ᱻHAL_TIM_Encoder_Init()����
 * @param       htim:��ʱ�����
 * @retval      ��
 */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIM2_ENCODER)
    {
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIM2_ENCODER_CH1_CLK_ENABLE();                                      /* ������ʱ��ʱ�� */
        GTIM_TIM2_ENCODER_CH2_CLK_ENABLE();
        GTIM_TIM2_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* ����ͨ����GPIOʱ�� */
        GTIM_TIM2_ENCODER_CH2_GPIO_CLK_ENABLE();


        gpio_init_struct.Pin = GTIM_TIM2_ENCODER_CH1_GPIO_PIN;                   /* ͨ��y��GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;                                 /* ���� */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* �������� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
        HAL_GPIO_Init(GTIM_TIM2_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
        
        gpio_init_struct.Pin = GTIM_TIM2_ENCODER_CH2_GPIO_PIN;                   /* ͨ��y��GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;                                 /* ���� */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* �������� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
        HAL_GPIO_Init(GTIM_TIM2_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
       
//        HAL_NVIC_SetPriority(GTIM_TIM2_ENCODER_INT_IRQn, 3, 0);                  /* �ж����ȼ����� */
//        HAL_NVIC_EnableIRQ(GTIM_TIM2_ENCODER_INT_IRQn);                          /* �����ж� */
    }
    if (htim->Instance == GTIM_TIM4_ENCODER)
    {
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIM4_ENCODER_CH1_CLK_ENABLE();                                      /* ������ʱ��ʱ�� */
        GTIM_TIM4_ENCODER_CH2_CLK_ENABLE();
        GTIM_TIM4_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* ����ͨ����GPIOʱ�� */
        GTIM_TIM4_ENCODER_CH2_GPIO_CLK_ENABLE();


        gpio_init_struct.Pin = GTIM_TIM4_ENCODER_CH1_GPIO_PIN;                   /* ͨ��y��GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;                                 /* ���� */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* �������� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
        HAL_GPIO_Init(GTIM_TIM4_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
        
        gpio_init_struct.Pin = GTIM_TIM4_ENCODER_CH2_GPIO_PIN;                   /* ͨ��y��GPIO�� */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;                                 /* ���� */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* �������� */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* ���� */
        HAL_GPIO_Init(GTIM_TIM4_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
       
//        HAL_NVIC_SetPriority(GTIM_TIM4_ENCODER_INT_IRQn, 3, 1);                  /* �ж����ȼ����� */
//        HAL_NVIC_EnableIRQ(GTIM_TIM4_ENCODER_INT_IRQn);                          /* �����ж� */
    }
}

///**
// * @brief       ��ʱ���жϷ�����
// * @param       ��
// * @retval      ��
// */
//void GTIM_TIM2_ENCODER_INT_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&g_tim2_encode_handle);
//}

//void GTIM_TIM4_ENCODER_INT_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&g_tim4_encode_handle);
//}


///* ����ͨ�ö�ʱ��ͳ��������� */
//volatile int g_tim2_encode_count = 0;                                   /* ������� */
//volatile int g_tim4_encode_count = 0;                                   /* ������� */

///**
// * @brief       ��ʱ�������жϻص�����
// * @param        htim:��ʱ�����ָ��
// * @note        �˺����ᱻ��ʱ���жϺ�����ͬ���õ�
// * @retval      ��
// */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == GTIM_TIM2_ENCODER)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim2_encode_handle))   /* �ж�CR1��DIRλ */
//        {
//            g_tim2_encode_count--;                                      /* DIRλΪ1��Ҳ���ǵݼ����� */
//        }
//        else
//        {
//            g_tim2_encode_count++;                                      /* DIRλΪ0��Ҳ���ǵ������� */
//        }
//    }
//    if (htim->Instance == GTIM_TIM4_ENCODER)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim4_encode_handle))   /* �ж�CR1��DIRλ */
//        {
//            g_tim4_encode_count--;                                      /* DIRλΪ1��Ҳ���ǵݼ����� */
//        }
//        else
//        {
//            g_tim4_encode_count++;                                      /* DIRλΪ0��Ҳ���ǵ������� */
//        }
//    }

//}

/**
 * @brief       ��ȡ��������ֵ
 * @param       ��
 * @retval      ������ֵ
 */
int gtim2_get_encode(void)
{
<<<<<<< HEAD
//    int count = __HAL_TIM_GET_COUNTER(&g_tim2_encode_handle);
//    int sum = count + g_tim2_encode_count * 65536;
//    g_tim2_encode_count = 0;
//    __HAL_TIM_SET_COUNTER(&g_tim2_encode_handle, 0);
//    return ( int32_t ) sum;       /* ��ǰ����ֵ+֮ǰ�ۼƱ�������ֵ=�ܵı�����ֵ */
    int encode = __HAL_TIM_GET_COUNTER(&g_tim2_encode_handle);
    __HAL_TIM_SET_COUNTER(&g_tim2_encode_handle, 0);
    return ( int32_t ) encode;              /* ��ǰ����ֵ */
=======
    //return ( int32_t )__HAL_TIM_GET_COUNTER(&g_tim2_encode_handle) + g_tim2_encode_count * 65536;       /* ��ǰ����ֵ+֮ǰ�ۼƱ�������ֵ=�ܵı�����ֵ */
    return ( int32_t )__HAL_TIM_GET_COUNTER(&g_tim2_encode_handle);              /* ��ǰ����ֵ */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
}

int gtim4_get_encode(void)
{
<<<<<<< HEAD
//    int count = __HAL_TIM_GET_COUNTER(&g_tim4_encode_handle);
//    int sum = count + g_tim4_encode_count * 65536;
//    g_tim4_encode_count = 0;
//    __HAL_TIM_SET_COUNTER(&g_tim4_encode_handle, 0);
//    return ( int32_t ) sum;       /* ��ǰ����ֵ+֮ǰ�ۼƱ�������ֵ=�ܵı�����ֵ */
    int encode = __HAL_TIM_GET_COUNTER(&g_tim4_encode_handle);
    __HAL_TIM_SET_COUNTER(&g_tim4_encode_handle, 0);
    return ( int32_t ) encode;              /* ��ǰ����ֵ */
=======
    //return ( int32_t )__HAL_TIM_GET_COUNTER(&g_tim4_encode_handle) + g_tim4_encode_count * 65536;       /* ��ǰ����ֵ+֮ǰ�ۼƱ�������ֵ=�ܵı�����ֵ */
    return ( int32_t )__HAL_TIM_GET_COUNTER(&g_tim4_encode_handle);              /* ��ǰ����ֵ */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
}


