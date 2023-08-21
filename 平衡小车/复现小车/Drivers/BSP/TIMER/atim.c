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
 * @brief       高级定时器 驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的高级定时器驱动
 * 用TIM1的CH1和CH4发出两路PWM
 *
<<<<<<< HEAD
 *
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


#include "./BSP/TIMER/atim.h"
#include "./BSP/TIMER/gtim.h"
<<<<<<< HEAD
#include "./BSP/CONTROL/control.h"
=======
#include "control.h"
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 
TIM_HandleTypeDef g_tim1_handle;

/* c8t6的唯一一个高级定时器 */
/**
 * @brief       高级定时器TIM1 通道1、通道4 PWM输出模式 初始化函数
 * @note
 *              高级定时器的时钟来自APB2, 而PCLK2 = 72Mhz, 我们设置PPRE2不分频, 因此
 *              高级定时器时钟 = 72Mhz高级定时器时钟 = 72Mhz 
 *              定时器溢出时间计算方法: Tout = ((arr + 1) * (psc + 1)) / Ft us. 
 *              Ft=定时器工作频率,单位:Mhz 
 * @param       arr: 自动重装值 
 * @param       psc: 时钟预分频数 
 * @retval 无
 */
void atim_tim1_pwm_init(uint16_t psc, uint16_t arr)
{
    TIM_OC_InitTypeDef sConfigOC = {0};
<<<<<<< HEAD
//    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
=======
    TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    
    /* 1.通过TIM_HandleTypeDef初始TIM1的参数 */
    g_tim1_handle.Instance = ATIM_TIM1_PWM;
    g_tim1_handle.Init.Prescaler = psc;                                         /* 预分频系数 */
    g_tim1_handle.Init.CounterMode = TIM_COUNTERMODE_UP;                        /* 递增 */
    g_tim1_handle.Init.Period = arr;                                            /* 自动重装载值 */
    g_tim1_handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;                  /* 时钟不分频 */
    g_tim1_handle.Init.RepetitionCounter = 0;                                   /* 不开启重复计数器 */
    g_tim1_handle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;       /* 开启影子寄存器，有缓冲 */
    HAL_TIM_PWM_Init(&g_tim1_handle);
    
    /* 2.设置PWM输出 */
    /* 控制两个电机，所以要放入两个channel中 */
    sConfigOC.OCMode = TIM_OCMODE_PWM1;                                         /* PWM模式1 */
    sConfigOC.Pulse = 0;                                                        /* 用来设置占空比，初始化为0 */
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;                                 /* 输出极性为高电平 */
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;                               /* 互补输出通道也是高电平 */
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;                                  /* 不使用快速模式 */
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;                              /* 开启刹车才会生效，空闲状态下低电平 */
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;                            /* 开启刹车才会生效，空闲状态下低电平 */
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, ATIM_TIM1_PWM_CH1);
    HAL_TIM_PWM_ConfigChannel(&g_tim1_handle, &sConfigOC, ATIM_TIM1_PWM_CH4);
    
<<<<<<< HEAD
//    /* 3.设置死区参数 */
//    /* 运行状态关闭死区 */
//    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
//    /* 空闲模式的关闭输出状态 */
//    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
//    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;                         /* 关闭寄存器锁功能 */
//    sBreakDeadTimeConfig.DeadTime = 0;                                          /* 初始化死去时间设置为0 */
//    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;                        /* 失能刹车输入 */
//    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;                /* 刹车输入有效信号极性为高 */
//    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;         /* 未使能AOE，刹车后不会自动恢复 */
//    HAL_TIMEx_ConfigBreakDeadTime(&g_tim1_handle, &sBreakDeadTimeConfig);
=======
    /* 3.设置死区参数 */
    /* 运行状态关闭死区 */
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    /* 空闲模式的关闭输出状态 */
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;                         /* 关闭寄存器锁功能 */
    sBreakDeadTimeConfig.DeadTime = 0;                                          /* 初始化死去时间设置为0 */
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_ENABLE;                         /* 使能刹车输入 */
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;                /* 刹车输入有效信号极性为高 */
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;         /* 未使能AOE，刹车后不会自动恢复 */
    HAL_TIMEx_ConfigBreakDeadTime(&g_tim1_handle, &sBreakDeadTimeConfig);
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    
    /* 4.开启PWM输出 */
    HAL_TIM_PWM_Start(&g_tim1_handle, ATIM_TIM1_PWM_CH1);
    HAL_TIM_PWM_Start(&g_tim1_handle, ATIM_TIM1_PWM_CH4);
    
<<<<<<< HEAD
//    __HAL_TIM_ENABLE_IT(&g_tim1_handle,TIM_IT_UPDATE);               /* 使能更新中断 */
//    __HAL_TIM_CLEAR_FLAG(&g_tim1_handle,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
=======
    __HAL_TIM_ENABLE_IT(&g_tim1_handle,TIM_IT_UPDATE);               /* 使能更新中断 */
    __HAL_TIM_CLEAR_FLAG(&g_tim1_handle,TIM_IT_UPDATE);              /* 清除更新中断标志位 */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
}

/* 在MSP函数中定义NVIC、GPIO等 */
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == ATIM_TIM1_PWM)
    {
        GPIO_InitTypeDef gpio_init_struct;                      /* GPIO句柄 */
        ATIM_TIM1_PWM_CH1_CLK_ENABLE();                         /* 开启TIM1时钟 */
        ATIM_TIM1_PWM_CH4_CLK_ENABLE();
        ATIM_TIM1_PWM_CH1_GPIO_CLK_ENABLE();                    /* 开启GPIOA时钟 */
        ATIM_TIM1_PWM_CH4_GPIO_CLK_ENABLE();
        
        /* 初始化GPIO */
<<<<<<< HEAD
        gpio_init_struct.Pin = ATIM_TIM1_PWM_CH1_GPIO_PIN;      /* 选定定时器1通道1引脚 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;           /* 低速 */
        HAL_GPIO_Init(ATIM_TIM1_PWM_CH1_GPIO_PORT, &gpio_init_struct);
        
        gpio_init_struct.Pin = ATIM_TIM1_PWM_CH4_GPIO_PIN;      /* 选定定时器1通道4引脚 */
        HAL_GPIO_Init(ATIM_TIM1_PWM_CH4_GPIO_PORT, &gpio_init_struct);
=======
        gpio_init_struct.Pin = ATIM_TIM1_PWM_CH1_GPIO_PIN | ATIM_TIM1_PWM_CH4_GPIO_PIN;      /* 选定定时器1通道1和通道4引脚 */
        gpio_init_struct.Mode = GPIO_MODE_AF_PP;                /* 复用推挽输出 */
        gpio_init_struct.Speed = GPIO_SPEED_FREQ_LOW;           /* 低速 */
        HAL_GPIO_Init(ATIM_TIM1_PWM_CH1_GPIO_PORT, &gpio_init_struct);
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    }
}








