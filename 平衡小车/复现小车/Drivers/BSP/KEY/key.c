/**
 ****************************************************************************************************
 * @file        key.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       按键输入 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的按键驱动
 * 只有一个按键，在PA5
 *
<<<<<<< HEAD
 * 修改说明
 * V1.0 20230813
 * 第一次发布
 *
 *
=======
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 ****************************************************************************************************
 */



#include "./BSP/KEY/key.h"
#include "./SYSTEM/delay/delay.h"


/**
 * @brief       按键初始化函数
 * @param       无
 * @retval      无
 */
void key_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    KEY_GPIO_CLK_ENABLE();                                     /* KEY时钟使能 */

    gpio_init_struct.Pin = KEY_GPIO_PIN;                       /* KEY引脚 */
    gpio_init_struct.Mode = GPIO_MODE_INPUT;                   /* 输入 */
    gpio_init_struct.Pull = GPIO_PULLUP;                       /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;             /* 高速 */
    HAL_GPIO_Init(KEY_GPIO_PORT, &gpio_init_struct);           /* KEY引脚模式设置,上拉输入 */

}

/**
 * @brief       按键扫描函数
 * @note        该函数有响应优先级(同时按下多个按键): WK_UP > KEY1 > KEY0!!
 * @param       mode:0 / 1, 具体含义如下:
 *   @arg       0,  不支持连续按(当按键按下不放时, 只有第一次调用会返回键值,
 *                  必须松开以后, 再次按下才会返回其他键值)
 *   @arg       1,  支持连续按(当按键按下不放时, 每次调用该函数都会返回键值)
 * @retval      键值, 定义如下:
 *              KEY_PRES, 1, KEY按下
 */
uint8_t key_scan(uint8_t mode)
{
    static uint8_t key_up = 1;  /* 按键按松开标志 */
    uint8_t keyval = 0;

    if (mode) key_up = 1;       /* 支持连按 */

    if (key_up && KEY == 0)  /* 按键松开标志为1, 且有任意一个按键按下了 */
    {
        delay_ms(10);           /* 去抖动 */
        key_up = 0;

        if (KEY == 0)  keyval = KEY_PRES;

    }
    else if (KEY == 1) /* 没有任何按键按下, 标记按键松开 */
    {
        key_up = 1;
    }

    return keyval;              /* 返回键值 */
}




















