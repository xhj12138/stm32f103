/**
 ******************************************************************************
 * @file     main.c
 * @author   Xia
<<<<<<< HEAD
 * @version  V1.1
 * @date     2023-08-21
=======
 * @version  V1.0
 * @date     2023-08-13
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 * @brief    轮趣小车的main函数
 ******************************************************************************
 * @attention
 * 
 * 轮趣小车移植代码
<<<<<<< HEAD
 *
 *
 * 修改说明
 * V1.0 20230813
 * 第一次发布
 * 1.完成串口、外部中断、ADC、定时器1、定时器2、定时器4、MPU6050、TB6612、LED、KEY、OLED的初始化
 * 2.完成基于MPU6050自带的DMP直接读取数据
 * 3.OLED的部分显示功能
 * V1.1
 * 1.完成蓝牙串口的初始化
 * 2.编写直立环、速度环、转向环的控制代码
 * 3.完成与轮趣科技APP的蓝牙数据串口传输
 * 4.完成遥控功能与APP显示、OLED显示功能
 *
 *
=======
 
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/atim.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/KEY/key.h"
#include "./BSP/OLED/oled.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/EXTI/exti.h"
<<<<<<< HEAD
#include "./BSP/CONTROL/control.h"
#include "./BSP/SHOW/show.h"
#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/eMPL/inv_mpu.h"
#include "./BSP/BT04/bt04.h"

extern volatile uint8_t delay_flag, delay_50;
extern uint16_t atim_psc, atim_arr;
extern float P_stand, D_stand;
extern float P_velocity, I_velocity;

int main(void)
{
=======
#include "control.h"
#include "show.h"

#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/eMPL/inv_mpu.h"

extern TIM_HandleTypeDef g_tim1_handle;
extern volatile uint8_t delay_flag, delay_50;

int main(void)
{
    uint8_t key = 0;
    float voltage = 0;
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    uint8_t ret = 0;
    
    HAL_Init();                                 /* 初始化HAL库 */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* 设置时钟, 72Mhz */
<<<<<<< HEAD
    
    led_init();                                 /* LED初始化 */
    key_init();                                 /* 按键初始化 */
    usart_init(115200);                         /* 串口初始化为115200 */
    bt04_uart_init(9600);                       /* 蓝牙串口初始化为9600 */
    TB6612_init();                              /* 初始化直流电机驱动器 */
    atim_tim1_pwm_init(atim_psc, atim_arr);     /* 72M / 7200 = 10kHz */
    gtim_tim2_encoder_init(1 - 1, 0XFFFF - 1);  /* 编码器1，不分频直接65536 */
    gtim_tim4_encoder_init(1 - 1, 0XFFFF - 1);  /* 编码器2，不分频直接65536 */
    adc_init();                                 /* 初始化ADC */
    
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();              /* 禁用JTAG，使用SWD调试 */
    
    delay_init(72);                             /* 延时初始化 */
    oled_init();                                /* oled初始化 */
    ret = mpu6050_init();                       /* 初始化MPU6050 */
    ret += mpu6050_dmp_init();                  /* 初始化MPU6050 DMP */
=======
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();              /* 禁用JTAG，使用SWD调试 */
    delay_init(72);                             /* 延时初始化 */
    led_init();                                 /* LED初始化 */
    key_init();                                 /* 按键初始化 */
    usart_init(115200);                         /* 串口初始化为115200 */
    atim_tim1_pwm_init(1 - 1, 7199 - 1);        /* 72M / 7200 = 10kHz */
    gtim_tim2_encoder_init(1 - 1, 0XFFFF - 1);  /* 编码器1，不分频直接65536 */
    gtim_tim4_encoder_init(1 - 1, 0XFFFF - 1);  /* 编码器2，不分频直接65536 */
    oled_init();                                /* oled初始化 */
    adc_init();                                 /* 初始化ADC */
    TB6612_init();                              /* 初始化直流电机驱动器 */
    ret = mpu6050_init();                       /* 初始化MPU6050 */
    ret = mpu6050_dmp_init();                   /* 初始化MPU6050 DMP */
    if (!ret) printf("MPU6050 init successful!\r\n");
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    extix_init();                               /* 外部中断初始化 */
    
    while(1)
    { 
<<<<<<< HEAD
        oled_show();
        APP_Show();
        delay_flag = 1;
        delay_50 = 0;
        while (delay_flag);
=======
        key = key_scan(0);
        if (key == KEY_PRES)
        {
            LED_TOGGLE();
        }
        
        voltage = adc_get_battery_voltage(ADC_ADCX_CHY, 20);
        
        
        //printf("encode = %d\r\n", gtim2_get_encode);
        
        
        
        delay_flag = 1;
        delay_50 = 0;
        while (delay_flag);
        
        oled_show();
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735

    }
}


