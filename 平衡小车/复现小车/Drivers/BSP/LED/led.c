/**
 ****************************************************************************************************
 * @file        led.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       LED 驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的LED驱动，LED接在PA4
 *
<<<<<<< HEAD
 *
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


#include "./BSP/LED/led.h"


/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    LED_GPIO_CLK_ENABLE();                                 /* LED时钟使能 */

    gpio_init_struct.Pin = LED_GPIO_PIN;                   /* LED引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(LED_GPIO_PORT, &gpio_init_struct);       /* 初始化LED引脚 */

    LED(0);                                                /* 关闭 LED */
}
