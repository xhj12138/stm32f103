/**
 ****************************************************************************************************
 * @file        show.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-21
 * @brief       数据显示代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的显示部分，来进行OELD,APP的显示
 *
 *
 * 修改说明
 * V1.0 20230821
 * 第一次发布
 *
 *
 ****************************************************************************************************
*/


#ifndef __SHOW_H
#define __SHOW_H

/******************************************************************************************/
/* 参数 定义 */
extern float Velocity_Left,Velocity_Right;             /* 左轮速度、右轮速度 */
extern int Motor_Left,Motor_Right;                     /* 电机的PWM的比较值，控制占空比 */
extern float pitch, roll, yaw;                         /* 通过MPU6050获取的欧拉角 */
extern int gyro_x, gyro_y, gyro_z;                     /* 通过MPU6050获得的陀螺仪值 */
extern int acc_x, acc_y, acc_z;                        /* 通过MPU6050获得的加速度值 */
extern float Angle_Balance, Gyro_Balance, Gyro_Turn;   /* 平衡倾角 平衡陀螺仪 转向陀螺仪 */
extern float Acceleration_Z;                           /* Z轴加速度计 */
extern int Voltage;                                    /* 电池电压 */
/******************************************************************************************/
void oled_show(void);
void APP_Show(void);


#endif


