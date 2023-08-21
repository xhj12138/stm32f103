/**
 ****************************************************************************************************
 * @file        oled.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       OLED ��������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС����OLED��������
 *
 * С����OLEDģ��Ĭ����4��SPI�����԰�8080�Ĳ���ȫ��ɾȥ
<<<<<<< HEAD
 *
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
 
#ifndef __OLED_H
#define __OLED_H

#include "stdlib.h" 
#include "./SYSTEM/sys/sys.h"


/* OLEDģʽ����
 * 0: 4�ߴ���ģʽ  ��ģ���BS1��BS2����GND��
 * 1: ����8080ģʽ ��ģ���BS1��BS2����VCC��
 * ��Ȥ��С���ϵ�OLEDû��CSƬѡ�źţ���Ĭ��Ϊ4��SPI
 */

/******************************************************************************************/
/* OLED SPIģʽ���� ���� */

#define OLED_SPI_RST_PORT               GPIOB
#define OLED_SPI_RST_PIN                GPIO_PIN_3
#define OLED_SPI_RST_CLK_ENABLE()       do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */

#define OLED_SPI_RS_PORT                GPIOA
#define OLED_SPI_RS_PIN                 GPIO_PIN_15
#define OLED_SPI_RS_CLK_ENABLE()        do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)   /* PA��ʱ��ʹ�� */

#define OLED_SPI_SCLK_PORT              GPIOB
#define OLED_SPI_SCLK_PIN               GPIO_PIN_5
#define OLED_SPI_SCLK_CLK_ENABLE()      do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */

#define OLED_SPI_SDIN_PORT              GPIOB
#define OLED_SPI_SDIN_PIN               GPIO_PIN_4
#define OLED_SPI_SDIN_CLK_ENABLE()      do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */

/******************************************************************************************/

/* OLED SPIģʽ��ض˿ڿ��ƺ��� ���� 
 * ע��:OLED_RST/OLED_CS/OLED_RS,�������Ǻ�80����ģʽ���õ�,��80ģʽҲ����ʵ����3������!
 */
#define OLED_RST(x)     do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_RST_PORT, OLED_SPI_RST_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_RST_PORT, OLED_SPI_RST_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����RST���� */

#define OLED_RS(x)      do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_RS_PORT, OLED_SPI_RS_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_RS_PORT, OLED_SPI_RS_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����RS���� */
                              
#define OLED_SCLK(x)    do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_SCLK_PORT, OLED_SPI_SCLK_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_SCLK_PORT, OLED_SPI_SCLK_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����SCLK���� */
#define OLED_SDIN(x)    do{ x ? \
                                  HAL_GPIO_WritePin(OLED_SPI_SDIN_PORT, OLED_SPI_SDIN_PIN, GPIO_PIN_SET) : \
                                  HAL_GPIO_WritePin(OLED_SPI_SDIN_PORT, OLED_SPI_SDIN_PIN, GPIO_PIN_RESET); \
                        }while(0)       /* ����SDIN���� */


/* ����/���� ���� */
#define OLED_CMD        0       /* д���� */
#define OLED_DATA       1       /* д���� */

/******************************************************************************************/
    
static void oled_wr_byte(uint8_t data, uint8_t cmd);    /* дһ���ֽڵ�OLED */
static uint32_t oled_pow(uint8_t m, uint8_t n);         /* OLED��ƽ������ */


void oled_init(void);           /* OLED��ʼ�� */
void oled_clear(void);          /* OLED���� */
void oled_display_on(void);     /* ����OLED��ʾ */
void oled_display_off(void);    /* �ر�OLED��ʾ */
void oled_refresh_gram(void);   /* �����Դ浽OLED */ 
void oled_draw_point(uint8_t x, uint8_t y, uint8_t dot);    /* OLED���� */
void oled_fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t dot);        /* OLED������� */
void oled_show_char(uint8_t x, uint8_t y, uint8_t chr, uint8_t size, uint8_t mode); /* OLED��ʾ�ַ� */
void oled_show_num(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);  /* OLED��ʾ���� */
void oled_show_string(uint8_t x, uint8_t y, const char *p, uint8_t size);           /* OLED��ʾ�ַ��� */

#endif




