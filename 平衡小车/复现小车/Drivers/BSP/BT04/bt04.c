/**
 ****************************************************************************************************
 * @file        bt04.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-21
 * @brief       BT04ģ����������
 ****************************************************************************************************
 * @attention
 *
 * ����ģ�����������
 *
 *
 * �޸�˵��
 * V1.0 20230821
 * ��һ�η���
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
static uint8_t g_uart_rx_buf[BT04_UART_RX_BUF_SIZE];        /* BT04 UART���ջ��� */
static uint8_t g_uart_tx_buf[BT04_UART_TX_BUF_SIZE];        /* BT04 UART���ͻ��� */
uint8_t g_usart_receive;                                    /* BT04���յ������� */

/* ����ң����صı��� */
uint8_t Flag_Front = 0, Flag_Back = 0;
uint8_t Flag_Left = 0, Flag_Right = 0;
uint8_t Flag_Velocity = 2;
uint8_t PID_Set;

/**
 * @brief       BT04 UART printf
 * @param       fmt: ����ӡ������
 * @retval      ��
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
 * @brief       BT04 UART��ʼ��
 * @param       baudrate: UARTͨѶ������
 * @retval      ��
 */
void bt04_uart_init(uint32_t baudrate)
{
    g_uart_handle.Instance          = BT04_UART_INTERFACE;     /* BT04 UART */
    g_uart_handle.Init.BaudRate     = baudrate;                /* ������ */
    g_uart_handle.Init.WordLength   = UART_WORDLENGTH_8B;      /* ����λ */
    g_uart_handle.Init.StopBits     = UART_STOPBITS_1;         /* ֹͣλ */
    g_uart_handle.Init.Parity       = UART_PARITY_NONE;        /* У��λ */
    g_uart_handle.Init.Mode         = UART_MODE_TX_RX;         /* �շ�ģʽ */
    g_uart_handle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;     /* ��Ӳ������ */
    g_uart_handle.Init.OverSampling = UART_OVERSAMPLING_16;    /* ������ */
    HAL_UART_Init(&g_uart_handle);                             /* ʹ�� BT04 UART
                                                                * HAL_UART_Init()����ú���HAL_UART_MspInit()
                                                                * �ú����������ļ�usart.c��
                                                                */
}



/**
 * @brief       BT04 UART�жϻص�����
 * @param       ��
 * @retval      ��
 */
void BT04_UART_IRQHandler(void)
{
    uint8_t tmp;
    
    if (__HAL_UART_GET_FLAG(&g_uart_handle, UART_FLAG_ORE) != RESET)        /* UART���չ��ش����ж� */
    {
        __HAL_UART_CLEAR_OREFLAG(&g_uart_handle);                           /* ������չ��ش����жϱ�־ */
        (void)g_uart_handle.Instance->SR;                                   /* �ȶ�SR�Ĵ������ٶ�DR�Ĵ��� */
        (void)g_uart_handle.Instance->DR;
    }
    
    if (__HAL_UART_GET_FLAG(&g_uart_handle, UART_FLAG_RXNE) != RESET)       /* UART�����ж� */
    {
        HAL_UART_Receive(&g_uart_handle, &tmp, 1, HAL_MAX_DELAY);           /* UART�������� */
        
        static int uart_receive = 0;
        static uint8_t Flag_PID, i, j, Receive[50];
        static float Data;
        g_uart_rx_buf[0] = tmp;
        uart_receive = g_uart_rx_buf[0];
        g_usart_receive = uart_receive;
        
        /* ���ж�С�����յ�������ָ���Ǽ��ٻ��Ǽ��� */
        if (uart_receive == 0x59) {Flag_Velocity = 2;}      /* ���ٵ� */
        if (uart_receive == 0x58) {Flag_Velocity = 1;}      /* ���ٵ� */
        
        if (uart_receive > 10)      /* Ĭ��ʹ�� */
        {
            /* ���ո�����ָ�if�жϼ��� */
            /* ɲ�� */
            if (uart_receive == 0x5A)
            {
                Flag_Front = 0, Flag_Back = 0;
                Flag_Left = 0, Flag_Right = 0;
            }
            /* ǰ�� */
            else if (uart_receive == 0x41)
            {
                Flag_Front = 1, Flag_Back = 0;
                Flag_Left = 0, Flag_Right = 0;
            }
            /* ���� */
            else if (uart_receive == 0x45)
            {
                Flag_Front = 0, Flag_Back = 1;
                Flag_Left = 0, Flag_Right = 0;
            }
            /* ���ϡ��ҡ��Һ� */
            else if (uart_receive == 0x42 || uart_receive == 0x43 || uart_receive == 0x44)
            {
                Flag_Front = 0, Flag_Back = 0;
                Flag_Left = 0, Flag_Right = 1;
            }
            /* �������ǰ */
            else if (uart_receive == 0x46 || uart_receive == 0x47 || uart_receive == 0x48)
            {
                Flag_Front = 0, Flag_Back = 0;
                Flag_Left = 1, Flag_Right = 0;
            }
            /* ����ָ���ɲ�� */
            else
            {
                Flag_Front = 0, Flag_Back = 0;
                Flag_Left = 0, Flag_Right = 0;
            }
        }
        
        /* ������PID�������� */
        if (g_usart_receive == 0x7B) {Flag_PID = 1;}      /* APP�ĵ���ָ����ʼλ */
        if (g_usart_receive == 0x7D) {Flag_PID = 2;}      /* APP�ĵ���ָ����ֹλ */
        
        if (Flag_PID == 1)  /* �������ݣ��ɼ����� */
        {
            Receive[i] = g_usart_receive;
            i++;
        }
        if (Flag_PID == 2)  /* ���ݴ�����ϣ��������ݽ�� */
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


