/**
 ****************************************************************************************************
 * @file        bt04.c
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

#include "./BSP/BT04/bt04.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/CONTROL/control.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

static UART_HandleTypeDef g_uart_handle;                    /* BT04 UART */
static uint8_t g_uart_rx_buf[BT04_UART_RX_BUF_SIZE];        /* BT04 UART接收缓冲 */
static uint8_t g_uart_tx_buf[BT04_UART_TX_BUF_SIZE];        /* BT04 UART发送缓冲 */
uint8_t g_usart_receive;                                    /* BT04接收到的数据 */

/* 蓝牙遥控相关的变量 */
uint8_t Flag_Front = 0, Flag_Back = 0;
uint8_t Flag_Left = 0, Flag_Right = 0;
uint8_t Flag_Velocity = 2;
uint8_t PID_Set;

/**
 * @brief       BT04 UART printf
 * @param       fmt: 待打印的数据
 * @retval      无
 */
void bt04_uart_printf(char *fmt, ...)
{
    va_list ap;
    uint16_t len;
    
    va_start(ap, fmt);
    vsprintf((char *)g_uart_tx_buf, fmt, ap);
    va_end(ap);
    
    len = strlen((const char *)g_uart_tx_buf);
    HAL_UART_Transmit(&g_uart_handle, g_uart_tx_buf, len, HAL_MAX_DELAY);
}

/**
 * @brief       BT04 UART初始化
 * @param       baudrate: UART通讯波特率
 * @retval      无
 */
void bt04_uart_init(uint32_t baudrate)
{
    g_uart_handle.Instance          = BT04_UART_INTERFACE;     /* BT04 UART */
    g_uart_handle.Init.BaudRate     = baudrate;                /* 波特率 */
    g_uart_handle.Init.WordLength   = UART_WORDLENGTH_8B;      /* 数据位 */
    g_uart_handle.Init.StopBits     = UART_STOPBITS_1;         /* 停止位 */
    g_uart_handle.Init.Parity       = UART_PARITY_NONE;        /* 校验位 */
    g_uart_handle.Init.Mode         = UART_MODE_TX_RX;         /* 收发模式 */
    g_uart_handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;     /* 无硬件流控 */
    g_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;    /* 过采样 */
    HAL_UART_Init(&g_uart_handle);                             /* 使能 BT04 UART
                                                                * HAL_UART_Init()会调用函数HAL_UART_MspInit()
                                                                * 该函数定义在文件usart.c中
                                                                */
}



/**
 * @brief       BT04 UART中断回调函数
 * @param       无
 * @retval      无
 */
void BT04_UART_IRQHandler(void)
{
    uint8_t tmp;
    
    if (__HAL_UART_GET_FLAG(&g_uart_handle, UART_FLAG_ORE) != RESET)        /* UART接收过载错误中断 */
    {
        __HAL_UART_CLEAR_OREFLAG(&g_uart_handle);                           /* 清除接收过载错误中断标志 */
        (void)g_uart_handle.Instance->SR;                                   /* 先读SR寄存器，再读DR寄存器 */
        (void)g_uart_handle.Instance->DR;
    }
    
    if (__HAL_UART_GET_FLAG(&g_uart_handle, UART_FLAG_RXNE) != RESET)       /* UART接收中断 */
    {
        HAL_UART_Receive(&g_uart_handle, &tmp, 1, HAL_MAX_DELAY);           /* UART接收数据 */
        
        static int uart_receive = 0;
        static uint8_t Flag_PID, i, j, Receive[50];
        static float Data;
        g_uart_rx_buf[0] = tmp;
        uart_receive = g_uart_rx_buf[0];
        g_usart_receive = uart_receive;
        
        /* 先判断小车接收到的蓝牙指令是加速还是减速 */
        if (uart_receive == 0x59) {Flag_Velocity = 2;}      /* 低速档 */
        if (uart_receive == 0x58) {Flag_Velocity = 1;}      /* 高速档 */
        
        if (uart_receive > 10)      /* 默认使用 */
        {
            /* 按照给定的指令集if判断即可 */
            /* 刹车 */
            if (uart_receive == 0x5A)
            {
                Flag_Front = 0, Flag_Back = 0;
                Flag_Left = 0, Flag_Right = 0;
            }
            /* 前进 */
            else if (uart_receive == 0x41)
            {
                Flag_Front = 1, Flag_Back = 0;
                Flag_Left = 0, Flag_Right = 0;
            }
            /* 后退 */
            else if (uart_receive == 0x45)
            {
                Flag_Front = 0, Flag_Back = 1;
                Flag_Left = 0, Flag_Right = 0;
            }
            /* 右上、右、右后 */
            else if (uart_receive == 0x42 || uart_receive == 0x43 || uart_receive == 0x44)
            {
                Flag_Front = 0, Flag_Back = 0;
                Flag_Left = 0, Flag_Right = 1;
            }
            /* 左后、左、左前 */
            else if (uart_receive == 0x46 || uart_receive == 0x47 || uart_receive == 0x48)
            {
                Flag_Front = 0, Flag_Back = 0;
                Flag_Left = 1, Flag_Right = 0;
            }
            /* 其余指令都给刹车 */
            else
            {
                Flag_Front = 0, Flag_Back = 0;
                Flag_Left = 0, Flag_Right = 0;
            }
        }
        
        /* 以下是PID参数调试 */
        if (g_usart_receive == 0x7B) {Flag_PID = 1;}      /* APP的调试指令起始位 */
        if (g_usart_receive == 0x7D) {Flag_PID = 2;}      /* APP的调试指令终止位 */
        
        if (Flag_PID == 1)  /* 接收数据，采集参数 */
        {
            Receive[i] = g_usart_receive;
            i++;
        }
        if (Flag_PID == 2)  /* 数据传输完毕，进行数据解读 */
        {
            if (Receive[3] == 0x50) {PID_Set = 1;}
            else if (Receive[1] != 0x23)
            {
                for (j = i; j >= 4; j--)
                {
                    Data += (Receive[j - 1] - 48) * pow(10, i - j);
                }
                switch (Receive[1])
                {
                    case 0x30: P_stand = Data;break;
                    case 0x31: D_stand = Data;break;
                    case 0x32: P_velocity = Data;break;
                    case 0x33: I_velocity = Data;break;
                    case 0x34: P_turn = Data;break;
                    case 0x35: D_turn = Data;break;
                    case 0x36: break;
                    case 0x37: break;
                    case 0x38: break;
                }
            }
            Flag_PID = 0;
            i = j = 0;
            Data = 0;
            memset(Receive, 0, sizeof(uint8_t) * 50);
        }
    }
}


