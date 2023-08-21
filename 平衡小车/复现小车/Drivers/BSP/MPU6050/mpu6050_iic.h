/**
 ****************************************************************************************************
 * @file        mpu6050_iic.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       MPU6050模块IIC接口驱动代码
 ****************************************************************************************************
<<<<<<< HEAD
 *
 *
 * 修改说明
 * V1.0 20230813
 * 第一次发布
 *
=======
 * @attention
 *
 * 轮趣小车软件实现IIC，用以驱动MPU6050
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 *
 ****************************************************************************************************
 */

#ifndef __MPU6050_IIC_H
#define __MPU6050_IIC_H

#include "./SYSTEM/sys/sys.h"

/* 引脚定义 */
#define MPU6050_IIC_SCL_GPIO_PORT            GPIOB
#define MPU6050_IIC_SCL_GPIO_PIN             GPIO_PIN_8
#define MPU6050_IIC_SCL_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)
#define MPU6050_IIC_SDA_GPIO_PORT            GPIOB
#define MPU6050_IIC_SDA_GPIO_PIN             GPIO_PIN_9
#define MPU6050_IIC_SDA_GPIO_CLK_ENABLE()    do{ __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)

/* IO操作 */
#define MPU6050_IIC_SCL(x)                   do{ x ?                                                                                             \
                                                HAL_GPIO_WritePin(MPU6050_IIC_SCL_GPIO_PORT, MPU6050_IIC_SCL_GPIO_PIN, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(MPU6050_IIC_SCL_GPIO_PORT, MPU6050_IIC_SCL_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MPU6050_IIC_SDA(x)                   do{ x ?                                                                                             \
                                                HAL_GPIO_WritePin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN, GPIO_PIN_SET) :    \
                                                HAL_GPIO_WritePin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN, GPIO_PIN_RESET);   \
                                                }while(0)

#define MPU6050_IIC_READ_SDA()               HAL_GPIO_ReadPin(MPU6050_IIC_SDA_GPIO_PORT, MPU6050_IIC_SDA_GPIO_PIN)

/* 操作函数 */
void mpu6050_iic_start(void);                /* 产生IIC起始信号 */
void mpu6050_iic_stop(void);                 /* 产生IIC停止信号 */
uint8_t mpu6050_iic_wait_ack(void);          /* 等待IIC应答信号 */
void mpu6050_iic_ack(void);                  /* 产生ACK应答信号 */
void mpu6050_iic_nack(void);                 /* 不产生ACK应答信号 */
void mpu6050_iic_send_byte(uint8_t dat);     /* IIC发送一个字节 */
uint8_t mpu6050_iic_read_byte(uint8_t ack);  /* IIC接收一个字节 */
void mpu6050_iic_init(void);                 /* 初始化IIC接口 */

#endif
