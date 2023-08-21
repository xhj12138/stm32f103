/**
 ****************************************************************************************************
 * @file        gtim.c
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

#include "./BSP/TIMER/gtim.h"
#include "./BSP/TIMER/atim.h"
<<<<<<< HEAD
#include "./BSP/CONTROL/control.h"
=======
#include "control.h"
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735


TIM_HandleTypeDef g_tim2_encode_handle;         /* 定时器2句柄 */
TIM_Encoder_InitTypeDef g_tim2_encoder_handle;  /* 定时2编码器句柄 */
TIM_HandleTypeDef g_tim4_encode_handle;         /* 定时器4句柄 */
TIM_Encoder_InitTypeDef g_tim4_encoder_handle;  /* 定时4编码器句柄 */

void gtim_tim2_encoder_init(uint16_t psc, uint16_t arr)
{
    /* 定时器x配置 */
    g_tim2_encode_handle.Instance = GTIM_TIM2_ENCODER;                      /* 定时器x */
    g_tim2_encode_handle.Init.Prescaler = psc;                              /* 定时器分频 */
    g_tim2_encode_handle.Init.Period = arr;                                 /* 自动重装载值 */
    g_tim2_encode_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* 时钟分频因子 */
    
    /* 定时器x编码器配置 */
    g_tim2_encoder_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1、TI2都检测，4倍频 */
    g_tim2_encoder_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
    g_tim2_encoder_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
    g_tim2_encoder_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
    g_tim2_encoder_handle.IC1Filter = 10;                                   /* 滤波器设置 */
    g_tim2_encoder_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
    g_tim2_encoder_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
    g_tim2_encoder_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
    g_tim2_encoder_handle.IC2Filter = 10;                                   /* 滤波器设置 */
<<<<<<< HEAD
    HAL_TIM_Encoder_Init(&g_tim2_encode_handle, &g_tim2_encoder_handle);    /* 初始化定时器x编码器 */
=======
    HAL_TIM_Encoder_Init(&g_tim2_encode_handle, &g_tim2_encoder_handle);/* 初始化定时器x编码器 */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
     
    HAL_TIM_Encoder_Start(&g_tim2_encode_handle,GTIM_TIM2_ENCODER_CH1);     /* 使能编码器通道1 */
    HAL_TIM_Encoder_Start(&g_tim2_encode_handle,GTIM_TIM2_ENCODER_CH2);     /* 使能编码器通道2 */
//    __HAL_TIM_ENABLE_IT(&g_tim2_encode_handle,TIM_IT_UPDATE);               /* 使能更新中断 */
//    __HAL_TIM_CLEAR_FLAG(&g_tim2_encode_handle,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
}


void gtim_tim4_encoder_init(uint16_t psc, uint16_t arr)
{
    /* 定时器x配置 */
    g_tim4_encode_handle.Instance = GTIM_TIM4_ENCODER;                      /* 定时器x */
    g_tim4_encode_handle.Init.Prescaler = psc;                              /* 定时器分频 */
    g_tim4_encode_handle.Init.Period = arr;                                 /* 自动重装载值 */
    g_tim4_encode_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;       /* 时钟分频因子 */
    
    /* 定时器x编码器配置 */
    g_tim4_encoder_handle.EncoderMode = TIM_ENCODERMODE_TI12;               /* TI1、TI2都检测，4倍频 */
    g_tim4_encoder_handle.IC1Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
    g_tim4_encoder_handle.IC1Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
    g_tim4_encoder_handle.IC1Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
    g_tim4_encoder_handle.IC1Filter = 10;                                   /* 滤波器设置 */
    g_tim4_encoder_handle.IC2Polarity = TIM_ICPOLARITY_RISING;              /* 输入极性，非反向 */
    g_tim4_encoder_handle.IC2Selection = TIM_ICSELECTION_DIRECTTI;          /* 输入通道选择 */
    g_tim4_encoder_handle.IC2Prescaler = TIM_ICPSC_DIV1;                    /* 不分频 */
    g_tim4_encoder_handle.IC2Filter = 10;                                   /* 滤波器设置 */
    HAL_TIM_Encoder_Init(&g_tim4_encode_handle, &g_tim4_encoder_handle);/* 初始化定时器x编码器 */
     
    HAL_TIM_Encoder_Start(&g_tim4_encode_handle,GTIM_TIM4_ENCODER_CH1);     /* 使能编码器通道1 */
    HAL_TIM_Encoder_Start(&g_tim4_encode_handle,GTIM_TIM4_ENCODER_CH2);     /* 使能编码器通道2 */
//    __HAL_TIM_ENABLE_IT(&g_tim4_encode_handle,TIM_IT_UPDATE);               /* 使能更新中断 */
//    __HAL_TIM_CLEAR_FLAG(&g_tim4_encode_handle,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
}


/**
 * @brief       定时器底层驱动，时钟使能，引脚配置
                此函数会被HAL_TIM_Encoder_Init()调用
 * @param       htim:定时器句柄
 * @retval      无
 */
void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == GTIM_TIM2_ENCODER)
    {
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIM2_ENCODER_CH1_CLK_ENABLE();                                      /* 开启定时器时钟 */
        GTIM_TIM2_ENCODER_CH2_CLK_ENABLE();
        GTIM_TIM2_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* 开启通道的GPIO时钟 */
        GTIM_TIM2_ENCODER_CH2_GPIO_CLK_ENABLE();


        gpio_init_struct.Pin = GTIM_TIM2_ENCODER_CH1_GPIO_PIN;                   /* 通道y的GPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;                                 /* 输入 */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 无上下拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
        HAL_GPIO_Init(GTIM_TIM2_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
        
        gpio_init_struct.Pin = GTIM_TIM2_ENCODER_CH2_GPIO_PIN;                   /* 通道y的GPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;                                 /* 输入 */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 无上下拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
        HAL_GPIO_Init(GTIM_TIM2_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
       
//        HAL_NVIC_SetPriority(GTIM_TIM2_ENCODER_INT_IRQn, 3, 0);                  /* 中断优先级设置 */
//        HAL_NVIC_EnableIRQ(GTIM_TIM2_ENCODER_INT_IRQn);                          /* 开启中断 */
    }
    if (htim->Instance == GTIM_TIM4_ENCODER)
    {
        GPIO_InitTypeDef gpio_init_struct;
        GTIM_TIM4_ENCODER_CH1_CLK_ENABLE();                                      /* 开启定时器时钟 */
        GTIM_TIM4_ENCODER_CH2_CLK_ENABLE();
        GTIM_TIM4_ENCODER_CH1_GPIO_CLK_ENABLE();                                 /* 开启通道的GPIO时钟 */
        GTIM_TIM4_ENCODER_CH2_GPIO_CLK_ENABLE();


        gpio_init_struct.Pin = GTIM_TIM4_ENCODER_CH1_GPIO_PIN;                   /* 通道y的GPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;                                 /* 输入 */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 无上下拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
        HAL_GPIO_Init(GTIM_TIM4_ENCODER_CH1_GPIO_PORT, &gpio_init_struct);  
        
        gpio_init_struct.Pin = GTIM_TIM4_ENCODER_CH2_GPIO_PIN;                   /* 通道y的GPIO口 */
        gpio_init_struct.Mode = GPIO_MODE_INPUT;                                 /* 输入 */
        gpio_init_struct.Pull = GPIO_NOPULL;                                     /* 无上下拉 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;                           /* 高速 */
        HAL_GPIO_Init(GTIM_TIM4_ENCODER_CH2_GPIO_PORT, &gpio_init_struct);         
       
//        HAL_NVIC_SetPriority(GTIM_TIM4_ENCODER_INT_IRQn, 3, 1);                  /* 中断优先级设置 */
//        HAL_NVIC_EnableIRQ(GTIM_TIM4_ENCODER_INT_IRQn);                          /* 开启中断 */
    }
}

///**
// * @brief       定时器中断服务函数
// * @param       无
// * @retval      无
// */
//void GTIM_TIM2_ENCODER_INT_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&g_tim2_encode_handle);
//}

//void GTIM_TIM4_ENCODER_INT_IRQHandler(void)
//{
//    HAL_TIM_IRQHandler(&g_tim4_encode_handle);
//}


///* 两个通用定时器统计溢出次数 */
//volatile int g_tim2_encode_count = 0;                                   /* 溢出次数 */
//volatile int g_tim4_encode_count = 0;                                   /* 溢出次数 */

///**
// * @brief       定时器更新中断回调函数
// * @param        htim:定时器句柄指针
// * @note        此函数会被定时器中断函数共同调用的
// * @retval      无
// */
//void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
//{
//    if (htim->Instance == GTIM_TIM2_ENCODER)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim2_encode_handle))   /* 判断CR1的DIR位 */
//        {
//            g_tim2_encode_count--;                                      /* DIR位为1，也就是递减计数 */
//        }
//        else
//        {
//            g_tim2_encode_count++;                                      /* DIR位为0，也就是递增计数 */
//        }
//    }
//    if (htim->Instance == GTIM_TIM4_ENCODER)
//    {
//        if(__HAL_TIM_IS_TIM_COUNTING_DOWN(&g_tim4_encode_handle))   /* 判断CR1的DIR位 */
//        {
//            g_tim4_encode_count--;                                      /* DIR位为1，也就是递减计数 */
//        }
//        else
//        {
//            g_tim4_encode_count++;                                      /* DIR位为0，也就是递增计数 */
//        }
//    }

//}

/**
 * @brief       获取编码器的值
 * @param       无
 * @retval      编码器值
 */
int gtim2_get_encode(void)
{
<<<<<<< HEAD
//    int count = __HAL_TIM_GET_COUNTER(&g_tim2_encode_handle);
//    int sum = count + g_tim2_encode_count * 65536;
//    g_tim2_encode_count = 0;
//    __HAL_TIM_SET_COUNTER(&g_tim2_encode_handle, 0);
//    return ( int32_t ) sum;       /* 当前计数值+之前累计编码器的值=总的编码器值 */
    int encode = __HAL_TIM_GET_COUNTER(&g_tim2_encode_handle);
    __HAL_TIM_SET_COUNTER(&g_tim2_encode_handle, 0);
    return ( int32_t ) encode;              /* 当前计数值 */
=======
    //return ( int32_t )__HAL_TIM_GET_COUNTER(&g_tim2_encode_handle) + g_tim2_encode_count * 65536;       /* 当前计数值+之前累计编码器的值=总的编码器值 */
    return ( int32_t )__HAL_TIM_GET_COUNTER(&g_tim2_encode_handle);              /* 当前计数值 */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
}

int gtim4_get_encode(void)
{
<<<<<<< HEAD
//    int count = __HAL_TIM_GET_COUNTER(&g_tim4_encode_handle);
//    int sum = count + g_tim4_encode_count * 65536;
//    g_tim4_encode_count = 0;
//    __HAL_TIM_SET_COUNTER(&g_tim4_encode_handle, 0);
//    return ( int32_t ) sum;       /* 当前计数值+之前累计编码器的值=总的编码器值 */
    int encode = __HAL_TIM_GET_COUNTER(&g_tim4_encode_handle);
    __HAL_TIM_SET_COUNTER(&g_tim4_encode_handle, 0);
    return ( int32_t ) encode;              /* 当前计数值 */
=======
    //return ( int32_t )__HAL_TIM_GET_COUNTER(&g_tim4_encode_handle) + g_tim4_encode_count * 65536;       /* 当前计数值+之前累计编码器的值=总的编码器值 */
    return ( int32_t )__HAL_TIM_GET_COUNTER(&g_tim4_encode_handle);              /* 当前计数值 */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
}


