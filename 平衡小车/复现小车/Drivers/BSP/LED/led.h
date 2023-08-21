/**
 ****************************************************************************************************
 * @file        led.h
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


#ifndef _LED_H
#define _LED_H
#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* 引脚 定义 */

#define LED_GPIO_PORT                  GPIOA
#define LED_GPIO_PIN                   GPIO_PIN_4
#define LED_GPIO_CLK_ENABLE()          do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)             /* PB口时钟使能 */

/******************************************************************************************/
/* LED端口定义 */
#define LED(x)   do{ x ? \
                      HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(LED_GPIO_PORT, LED_GPIO_PIN, GPIO_PIN_RESET); \
                  }while(0)      /* LED翻转 */


/* LED取反定义 */
#define LED_TOGGLE()   do{ HAL_GPIO_TogglePin(LED_GPIO_PORT, LED_GPIO_PIN); }while(0)        /* 翻转LED0 */

/******************************************************************************************/
/* 外部接口函数*/
void led_init(void);                                                                            /* 初始化 */

#endif
