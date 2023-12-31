/**
 ****************************************************************************************************
 * @file        control.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-21
 * @brief       放置小车的电机驱动代码，直立环速度环等驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的控制程序，所有控制都在这里，来控制小车的直立和前进后退转向
 *
 *
 * 修改说明
 * V1.0 20230821
 * 第一次发布
 *
 *
 ****************************************************************************************************
 */

#ifndef __CONTROL_H
#define __CONTROL_H

#include "./SYSTEM/sys/sys.h"

#define PI 3.14129265
#define CONTROL_FREQUENCY   200     /* 中断的频率 */
#define ROTO_RATIO          52      /* 线数*倍频系数，即13*4=52 */
#define REDUCTION_RATIO     30      /* 减速比30:1 */
#define Diameter            67.0    /*轮子直径67mm */
#define AMPLIFICATION       100     /* PID参数的放大系数 */

#define MIDDLE_ANGLE        0       /* 平衡角度 */

/******************************************************************************************/
/* PWM电机控制引脚 定义 */

#define AIN1_GPIO_PORT            GPIOB
#define AIN1_GPIO_PIN             GPIO_PIN_14
#define AIN1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB口时钟使能 */
#define AIN2_GPIO_PORT            GPIOB
#define AIN2_GPIO_PIN             GPIO_PIN_15
#define AIN2_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB口时钟使能 */

#define BIN1_GPIO_PORT            GPIOB
#define BIN1_GPIO_PIN             GPIO_PIN_13
#define BIN1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB口时钟使能 */
#define BIN2_GPIO_PORT            GPIOB
#define BIN2_GPIO_PIN             GPIO_PIN_12
#define BIN2_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB口时钟使能 */


/******************************************************************************************/
#define AIN1(x)     do{ x ? \
                      HAL_GPIO_WritePin(AIN1_GPIO_PORT, AIN1_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(AIN1_GPIO_PORT, AIN1_GPIO_PIN, GPIO_PIN_RESET); \
                    }while(0)       /* 设置AIN1引脚 */

#define AIN2(x)     do{ x ? \
                      HAL_GPIO_WritePin(AIN2_GPIO_PORT, AIN2_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(AIN2_GPIO_PORT, AIN2_GPIO_PIN, GPIO_PIN_RESET); \
                    }while(0)       /* 设置AIN2引脚 */

#define BIN1(x)     do{ x ? \
                      HAL_GPIO_WritePin(BIN1_GPIO_PORT, BIN1_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BIN1_GPIO_PORT, BIN1_GPIO_PIN, GPIO_PIN_RESET); \
                    }while(0)       /* 设置BIN1引脚 */

#define BIN2(x)     do{ x ? \
                      HAL_GPIO_WritePin(BIN2_GPIO_PORT, BIN2_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BIN2_GPIO_PORT, BIN2_GPIO_PIN, GPIO_PIN_RESET); \
                    }while(0)       /* 设置BIN2引脚 */
                    
/******************************************************************************************/

extern float P_stand, D_stand;           /* 直立环的PID参数 */
extern float P_velocity, I_velocity;     /* 速度环的PID参数 */
extern float P_turn, D_turn;             /* 转向环的PID参数 */
                    
void TB6612_init(void);
int my_abs(int num);
void Set_PWM(int motor_left,int motor_right);
int PWM_Limit(int IN, int min, int max);
                    
void Get_Velocity_From_Encoder(int encoder_left, int encoder_right);
uint8_t Get_Angle(uint8_t way);
int PID_Stand(float Angle, float Gyro);
int PID_Velocity(int encoder_left, int encoder_right);
int PID_Turn(float gyro);

#endif


