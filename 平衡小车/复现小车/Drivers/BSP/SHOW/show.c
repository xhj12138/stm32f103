/**
 ****************************************************************************************************
 * @file        show.c
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


#include "./BSP/SHOW/show.h"
#include "./BSP/OLED/oled.h"
#include "./BSP/CONTROL/control.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/BT04/bt04.h"

extern int PWM_Left_Duty, PWM_Right_Duty;

/**
 * @brief       OLED显示内容编写
 * @param       无
 * @retval      无
 */
void oled_show(void)
{
/***************第一行显示滤波算法以及当前小车模式***************/
    oled_show_string( 0, 0, "DMP", 12);
    oled_show_string(70, 0, "Normal", 12);
/***************第二行显示当前角度***************/
    oled_show_string( 0, 10, "Angle:", 12);
    if (Angle_Balance < 0) oled_show_string(48, 10, "-", 12);
    if (Angle_Balance >= 0) oled_show_string(48, 10, "+", 12);
    oled_show_num(56, 10, my_abs((int)Angle_Balance), 3, 12);
/***************第三行显示当前角速度和距离***************/
    oled_show_string( 0, 20, "Gyrox", 12);
    if (Gyro_Balance < 0) oled_show_string(42, 20, "-", 12);
    if (Gyro_Balance >= 0) oled_show_string(42, 20, "+", 12);
    oled_show_num(50, 20, my_abs((int)Gyro_Balance), 3, 12);
/***************第四行显示左编码器读数和PWM占空比***************/
    oled_show_string( 0, 30, "L", 12);
    if (Motor_Left < 0)  oled_show_string(16, 30, "-", 12);
    if (Motor_Left >= 0)  oled_show_string(16, 30, "+", 12);
    oled_show_num(26, 30, my_abs(PWM_Right_Duty), 4, 12);
    if (Velocity_Left < 0) oled_show_string(60, 30, "-", 12);
    if (Velocity_Left >= 0) oled_show_string(60, 30, "+", 12);
    oled_show_num(68, 30, my_abs(Velocity_Left), 4, 12);
    oled_show_string(96, 30, "mm/s", 12);
/***************第五行显示右编码器读数和PWM占空比***************/
    oled_show_string( 0, 40, "R", 12);
    if (Motor_Right < 0)  oled_show_string(16, 40, "-", 12);
    if (Motor_Right >= 0)  oled_show_string(16, 40, "+", 12);
    oled_show_num(26, 40, my_abs(PWM_Right_Duty), 4, 12);
    if (Velocity_Right < 0) oled_show_string(60, 40, "-", 12);
    if (Velocity_Right >= 0) oled_show_string(60, 40, "+", 12);
    oled_show_num(68, 40, my_abs(Velocity_Right), 4, 12);
    oled_show_string(96, 40, "mm/s", 12);
/***************第六行显示电压和电机开关***************/
    oled_show_string( 0, 50, "V", 12);
    oled_show_string(30, 50, ".", 12);
    oled_show_string(64, 50, "V", 12);
    oled_show_num(19, 50, Voltage / 100, 2, 12);
    oled_show_num(42, 50, Voltage / 10 % 10, 1, 12);
    oled_show_num(50, 50, Voltage % 10, 1, 12);
    
    oled_refresh_gram(); /* 更新显示到OLED */
}

/**
 * @brief       发送数据给APP
 * @param       无
 * @retval      无
 */
void APP_Show(void)
{
    static uint8_t flag;
    int Encoder_Left_Show, Encoder_Right_Show, Voltage_Show;
    /* 处理电压数据 */
    Voltage_Show = (Voltage - 1110) * 2 / 3;
    if (Voltage_Show < 0) {Voltage_Show = 0;}
    if (Voltage_Show > 100) {Voltage_Show = 100;}
    /* 处理编码器数据 */
    Encoder_Left_Show = Velocity_Left * 1.1;
    if (Encoder_Left_Show < 0) {Encoder_Left_Show = -Encoder_Left_Show;}
    Encoder_Right_Show = Velocity_Right * 1.1;
    if (Encoder_Right_Show < 0) {Encoder_Right_Show = -Encoder_Right_Show;}
    
    flag = !flag;
    if (PID_Set == 1)
    {
        bt04_uart_printf("{C%d:%d:%d:%d:%d:%d:%d:%d:%d}$",(int)P_stand,(int)D_stand,(int)P_velocity,(int)I_velocity,(int)P_turn,(int)D_turn,0,0,0);//打印到APP上面	
        PID_Set = 0;
    }
    else if (!flag)     /* 发送电压、速度、角度 */
    {
        bt04_uart_printf("{A%d:%d:%d:%d}$",(int)Encoder_Left_Show,(int)Encoder_Right_Show,(int)Voltage_Show,(int)Angle_Balance); //打印到APP上面
    }
    else        /* 发送姿态角 */
    {
        bt04_uart_printf("{B%d:%d:%d}$",(int)pitch,(int)roll,(int)yaw); //x，y，z轴角度 在APP上面显示波形
    }
}


