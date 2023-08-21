/**
 ****************************************************************************************************
 * @file        control.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-21
 * @brief       ����С���ĵ���������룬ֱ�����ٶȻ�����������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС���Ŀ��Ƴ������п��ƶ������������С����ֱ����ǰ������ת��
 *
 *
 * �޸�˵��
 * V1.0 20230821
 * ��һ�η���
 *
 *
 ****************************************************************************************************
 */

#ifndef __CONTROL_H
#define __CONTROL_H

#include "./SYSTEM/sys/sys.h"

#define PI 3.14129265
#define CONTROL_FREQUENCY   200     /* �жϵ�Ƶ�� */
#define ROTO_RATIO          52      /* ����*��Ƶϵ������13*4=52 */
#define REDUCTION_RATIO     30      /* ���ٱ�30:1 */
#define Diameter            67.0    /*����ֱ��67mm */
#define AMPLIFICATION       100     /* PID�����ķŴ�ϵ�� */

#define MIDDLE_ANGLE        0       /* ƽ��Ƕ� */

/******************************************************************************************/
/* PWM����������� ���� */

#define AIN1_GPIO_PORT            GPIOB
#define AIN1_GPIO_PIN             GPIO_PIN_14
#define AIN1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */
#define AIN2_GPIO_PORT            GPIOB
#define AIN2_GPIO_PIN             GPIO_PIN_15
#define AIN2_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */

#define BIN1_GPIO_PORT            GPIOB
#define BIN1_GPIO_PIN             GPIO_PIN_13
#define BIN1_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */
#define BIN2_GPIO_PORT            GPIOB
#define BIN2_GPIO_PIN             GPIO_PIN_12
#define BIN2_GPIO_CLK_ENABLE()    do{  __HAL_RCC_GPIOB_CLK_ENABLE(); }while(0)   /* PB��ʱ��ʹ�� */


/******************************************************************************************/
#define AIN1(x)     do{ x ? \
                      HAL_GPIO_WritePin(AIN1_GPIO_PORT, AIN1_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(AIN1_GPIO_PORT, AIN1_GPIO_PIN, GPIO_PIN_RESET); \
                    }while(0)       /* ����AIN1���� */

#define AIN2(x)     do{ x ? \
                      HAL_GPIO_WritePin(AIN2_GPIO_PORT, AIN2_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(AIN2_GPIO_PORT, AIN2_GPIO_PIN, GPIO_PIN_RESET); \
                    }while(0)       /* ����AIN2���� */

#define BIN1(x)     do{ x ? \
                      HAL_GPIO_WritePin(BIN1_GPIO_PORT, BIN1_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BIN1_GPIO_PORT, BIN1_GPIO_PIN, GPIO_PIN_RESET); \
                    }while(0)       /* ����BIN1���� */

#define BIN2(x)     do{ x ? \
                      HAL_GPIO_WritePin(BIN2_GPIO_PORT, BIN2_GPIO_PIN, GPIO_PIN_SET) : \
                      HAL_GPIO_WritePin(BIN2_GPIO_PORT, BIN2_GPIO_PIN, GPIO_PIN_RESET); \
                    }while(0)       /* ����BIN2���� */
                    
/******************************************************************************************/

extern float P_stand, D_stand;           /* ֱ������PID���� */
extern float P_velocity, I_velocity;     /* �ٶȻ���PID���� */
extern float P_turn, D_turn;             /* ת�򻷵�PID���� */
                    
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


