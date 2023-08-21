/**
 ****************************************************************************************************
 * @file        bt04.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-21
 * @brief       BT04模块驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 蓝牙模块的驱动代码
 *
 *
 * 修改说明
 * V1.0 20230821
 * 第一次发布
 *
 *
 ****************************************************************************************************
 */
 
 #ifndef __BT04_H
 #define __BT04_H
 
 #include "./SYSTEM/sys/sys.h"
 


/******************************************************************************************/
 /* 引脚定义 */
#define BT04_UART_TX_GPIO_PORT         GPIOB
#define BT04_UART_TX_GPIO_PIN          GPIO_PIN_10
#define BT04_UART_TX_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define BT04_UART_RX_GPIO_PORT         GPIOB
#define BT04_UART_RX_GPIO_PIN          GPIO_PIN_11
#define BT04_UART_RX_GPIO_CLK_ENABLE() do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

#define BT04_UART_INTERFACE            USART3
#define BT04_UART_IRQn                 USART3_IRQn
#define BT04_UART_IRQHandler           USART3_IRQHandler
#define BT04_UART_CLK_ENABLE()         do{ __HAL_RCC_USART3_CLK_ENABLE(); }while(0)

/* UART收发缓冲大小 */
#define BT04_UART_RX_BUF_SIZE          2048
#define BT04_UART_TX_BUF_SIZE          64


/******************************************************************************************/

/* 操作函数 */
void bt04_uart_printf(char *fmt, ...);     /* BT04 UART printf */
void bt04_uart_init(uint32_t baudrate);    /* BT04 UART 初始化 */

/* 蓝牙遥控相关的变量 */
extern uint8_t Flag_Front, Flag_Back;
extern uint8_t Flag_Left, Flag_Right;
extern uint8_t Flag_Velocity;
extern uint8_t PID_Set;
 
 
 #endif
 



