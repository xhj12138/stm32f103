/**
 ****************************************************************************************************
 * @file        mpu6050_iic.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       MPU6050ģ��IIC�ӿ���������
 ****************************************************************************************************
<<<<<<< HEAD
 *
 *
 * �޸�˵��
 * V1.0 20230813
 * ��һ�η���
 *
=======
 * @attention
 *
 * ��ȤС�����ʵ��IIC����������MPU6050
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 *
 ****************************************************************************************************
 */

#ifndef __MPU6050_IIC_H
#define __MPU6050_IIC_H

#include "./SYSTEM/sys/sys.h"

/* ���Ŷ��� */
#define MPU6050_IIC_SCL_GPIO_PORT            GPIOB
#define MPU6050_IIC_SCL_GPIO_PIN             GPIO_PIN_8
#define MPU6050_IIC_SCL_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)
#define MPU6050_IIC_SDA_GPIO_PORT            GPIOB
#define MPU6050_IIC_SDA_GPIO_PIN             GPIO_PIN_9
#define MPU6050_IIC_SDA_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/* IO���� */
#define MPU6050_IIC_SCL(x)                   do{ x ?                                                                                             \
                                                HAL_GPIO_WritePin(MPU6050_IIC_SCL_GPIO_PORT, MPU6050_IIC_SCL_GPIO_PIN, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(MPU6050_IIC_SCL_GPIO_PORT, MPU6050_IIC_SCL_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MPU6050_IIC_SDA(x)                   do{ x ?                                                                                             \
                                                HAL_GPIO_WritePin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MPU6050_IIC_READ_SDA()               HAL_GPIO_ReadPin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN)

/* �������� */
void mpu6050_iic_start(void);                /* ����IIC��ʼ�ź� */
void mpu6050_iic_stop(void);                 /* ����IICֹͣ�ź� */
uint8_t mpu6050_iic_wait_ack(void);          /* �ȴ�IICӦ���ź� */
void mpu6050_iic_ack(void);                  /* ����ACKӦ���ź� */
void mpu6050_iic_nack(void);                 /* ������ACKӦ���ź� */
void mpu6050_iic_send_byte(uint8_t dat);     /* IIC����һ���ֽ� */
uint8_t mpu6050_iic_read_byte(uint8_t ack);  /* IIC����һ���ֽ� */
void mpu6050_iic_init(void);                 /* ��ʼ��IIC�ӿ� */

#endif
