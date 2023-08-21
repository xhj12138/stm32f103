/**
 ****************************************************************************************************
 * @file        control.c
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
 
#include "./BSP/KEY/key.h"
#include "./BSP/CONTROL/control.h"
#include "./BSP/TIMER/atim.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/eMPL/inv_mpu.h"
#include "./BSP/ADC/adc.h"
#include "./SYSTEM/usart/usart.h"
#include "./BSP/BT04/bt04.h"

uint8_t Flag_Stop = 1;
float Velocity_Left, Velocity_Right;            /* 两轮的线速度 */
int Motor_Left, Motor_Right;                    /* 电机的PWM的比较值，控制占空比 */
float pitch, roll, yaw;                         /* 通过MPU6050获取的欧拉角 */
int16_t gyro_x, gyro_y, gyro_z;                 /* 通过MPU6050获得的陀螺仪值 */
int16_t acc_x, acc_y, acc_z;                    /* 通过MPU6050获得的加速度值 */
float Angle_Balance, Gyro_Balance, Gyro_Turn;   /* 平衡倾角 平衡陀螺仪 转向陀螺仪 */
float Acceleration_Z;                           /* Z轴加速度计 */
int Voltage;                                    /* 电池电压 */
int16_t temp;                                   /* MPU6050温度 */
uint16_t atim_psc = 1 - 1, atim_arr = 7200 - 1; /* TIM1的预分频系数和自动重装载值 */
float P_stand = 25000, D_stand = 120;           /* 直立环的PID参数 */
float P_velocity = 13000, I_velocity = 65;      /* 速度环的PID参数 */
float P_turn = 4000, D_turn = 20;               /* 转向环的PID参数 */
int PWM_Left_Duty = 0, PWM_Right_Duty = 0;
/**
 * @brief       中断服务程序中需要做的事情
                在HAL库中所有的外部中断服务函数都会调用此函数
 * @param       GPIO_Pin:中断引脚号
 * @retval      无
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    int Stand_PWM, Velocity_PWM, Turn_PWM;
    int Encoder_Left, Encoder_Right;
    if (GPIO_Pin == MPU6050_INT_GPIO_PIN)
    {
        uint8_t key = 0;
        key = key_scan(0);
        if (key == KEY_PRES) {Flag_Stop = !Flag_Stop;}
        uint8_t ret = Get_Angle(1);
        if (!ret)
        {
            Encoder_Left = -gtim2_get_encode();
            Encoder_Right = -gtim4_get_encode();
            if (my_abs(Encoder_Left) > 60000) {Encoder_Left += 65536;}
            if (my_abs(Encoder_Right) > 60000) {Encoder_Right += 65536;}
            Get_Velocity_From_Encoder(Encoder_Left, Encoder_Right);
            
            Voltage = adc_get_battery_voltage(ADC_ADCX_CHY);
            
            Stand_PWM = PID_Stand(Angle_Balance, Gyro_Balance);
            Velocity_PWM = PID_Velocity(Encoder_Left, Encoder_Right);
            Turn_PWM = PID_Turn(Gyro_Turn);
            Motor_Left = Stand_PWM + Velocity_PWM + Turn_PWM;
            Motor_Right = Stand_PWM + Velocity_PWM - Turn_PWM;
            Motor_Left = PWM_Limit(Motor_Left, -7000, 7000);
            Motor_Right = PWM_Limit(Motor_Right, -7000, 7000);
            PWM_Left_Duty = Motor_Left * 100 / atim_arr;
            PWM_Right_Duty = Motor_Right * 100 / atim_arr;
            if (!Flag_Stop) {Set_PWM(Motor_Left, Motor_Right);}
            else {Set_PWM(0, 0);}
        }
    }
}

/**
 * @brief       TB6612需要的初始化函数
 * @note
 *              初始化对应的GPIO引脚
 * @param       无
 * @retval      无
 */
void TB6612_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    AIN1_GPIO_CLK_ENABLE();     /* 使能AIN1时钟 */
    AIN2_GPIO_CLK_ENABLE();     /* 使能AIN2时钟 */
    BIN1_GPIO_CLK_ENABLE();     /* 使能BIN1时钟 */
    BIN2_GPIO_CLK_ENABLE();     /* 使能BIN2时钟 */
    
    gpio_init_struct.Pin = AIN1_GPIO_PIN;                /* AIN1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;       /* 高速 */
    HAL_GPIO_Init(AIN1_GPIO_PORT, &gpio_init_struct);    /* AIN1引脚模式设置 */

    gpio_init_struct.Pin = AIN2_GPIO_PIN;                /* AIN2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;       /* 高速 */
    HAL_GPIO_Init(AIN2_GPIO_PORT, &gpio_init_struct);    /* AIN2引脚模式设置 */
    
    gpio_init_struct.Pin = BIN1_GPIO_PIN;                /* BIN1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;       /* 高速 */
    HAL_GPIO_Init(BIN1_GPIO_PORT, &gpio_init_struct);    /* BIN1引脚模式设置 */
    
    gpio_init_struct.Pin = BIN2_GPIO_PIN;                /* BIN2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;       /* 高速 */
    HAL_GPIO_Init(BIN2_GPIO_PORT, &gpio_init_struct);    /* BIN2引脚模式设置 */
    
    AIN1(0);
    AIN2(0);
    BIN1(0);
    BIN2(0);
}

/**
 * @brief       计算绝对值
 * @param       num：原始值
 * @retval      tmp：绝对值
 */
int my_abs(int num)
{
    int tmp = 0;
    if (num < 0) {tmp = -num;}
    else tmp = num;
    return tmp;
}


/**
 * @brief       设置定时器1的两路PWM输出的占空比，控制电机转速
 * @param       motor_left：小车左轮的期望占空比
 * @param       motor_right：小车右轮的期望占空比
 * @retval      无
 */
void Set_PWM(int motor_left, int motor_right)
{
    if (motor_left > 0)
    {
        /* 左轮参数为正，需要正转 */
        BIN1(1);
        BIN2(0);
    }
    if (motor_left < 0)
    {
        /* 左轮参数为负，需要反转 */
        BIN1(0);
        BIN2(1);
    }
    ATIM_TIM1_PWM_CH4_CCRX = my_abs(motor_left);
    
    if (motor_right > 0)
    {
        /* 右轮参数为正，需要正转 */
        AIN1(0);
        AIN2(1);
    }
    if (motor_right < 0)
    {
        /* 右轮参数为负，需要反转 */
        AIN1(1);
        AIN2(0);
    }
    ATIM_TIM1_PWM_CH1_CCRX = my_abs(motor_right);
}


/**
 * @brief       饱和模块，设置PWM输出的最大值
 * @param       IN：输入的计算值
 * @param       min：输出的最小值
 * @param       max：输出的最大值
 * @retval      OUT：饱和计算得到的PWM输出值
 */
int PWM_Limit(int IN, int min, int max)
{
    int OUT = IN;
    if (OUT > max) OUT = max;
    if (OUT < min) OUT = min;
    return OUT;
}

/**
 * @brief       读取编码器，计算当前轮子线速度
                单位：mm/s
 * @param       无
 * @retval      无
 */
void Get_Velocity_From_Encoder(int encoder_left, int encoder_right)
{
    if (my_abs(encoder_left) > 60000) {encoder_left += 65536;}
    if (my_abs(encoder_right) > 60000) {encoder_right += 65536;}
    float rotate_left = 0.0, rotate_right = 0.0;
    rotate_left = (float)encoder_left * CONTROL_FREQUENCY / ROTO_RATIO / REDUCTION_RATIO;
    rotate_right = (float)encoder_right * CONTROL_FREQUENCY / ROTO_RATIO / REDUCTION_RATIO;
    Velocity_Left = rotate_left * PI * Diameter;
    Velocity_Right = rotate_right * PI * Diameter;
}

/**
 * @brief       获取当前小车角度
                首先实现直接基于MPU6050自带的DMP算法
 * @param       way:使用方法：1.DMP
 * @retval      0: 函数执行成功
 *              1: 函数执行失败
 */
uint8_t Get_Angle(uint8_t way)
{
    if (way == 1)
    {
        uint8_t result = mpu6050_dmp_get_data(&pitch, &roll, &yaw);
        result += mpu6050_get_gyroscope(&gyro_x, &gyro_y, &gyro_z);
        result += mpu6050_get_accelerometer(&acc_x, &acc_y, &acc_z);
        result += mpu6050_get_temperature(&temp);
        if (result) {return 1;}
        else
        {
            Angle_Balance = roll;
            Gyro_Balance = gyro_x;
            Gyro_Turn = gyro_z;
            Acceleration_Z = acc_z;
        }
    }
    return 0;
}

/**
 * @brief       小车的直立环计算，实际就是PD控制
 * @param       Angle：MPU6050读取得到的当前倾斜角度，用于P控制
 * @param       Gyro：MPU6050读取得到的角速度，相当于角度微分，用于D控制
 * @retval      Actual_Value：直立环的PID期望输出
 */
int PID_Stand(float Angle, float Gyro)
{
    float Angle_Bias, Gyro_Bias;
    int Actual_Value;
    Angle_Bias = MIDDLE_ANGLE - Angle;
    Gyro_Bias = 0 - Gyro;
    Actual_Value = -P_stand * Angle_Bias / AMPLIFICATION + D_stand * Gyro_Bias / AMPLIFICATION;
    return Actual_Value;
}


/**
 * @brief       小车的速度环计算，实际就是PI控制
 * @param       encoder_left：左编码器读数
 * @param       encoder_right：右编码器读数
 * @retval      Actual_Value：速度环的PID期望输出
 */
int PID_Velocity(int encoder_left, int encoder_right)
{
    static float Actual_Value;
    static float Encoder_Least, q, Encoder_Bias, Encoder_Integral;
    static float Target_Velocity, Movement;
    /***********************************************遥控前进后退部分********************************************/
    Target_Velocity = 30;
    if (Flag_Front) {Movement = Target_Velocity / Flag_Velocity;}
    else if (Flag_Back) {Movement = -Target_Velocity / Flag_Velocity;}
    else Movement = 0;
    /***********************************************速度环PI部分********************************************/
    Encoder_Least = 0 - (encoder_left + encoder_right);
    /* 一阶低通滤波
     * 公式为：Y(n)= qX(n) + (1-q)Y(n-1)
     * 其中X(n)为本次采样值；Y(n-1)为上次滤波输出值；Y(n)为本次滤波输出值，q为滤波系数
     * q值越小则上一次输出对本次输出影响越大，整体曲线越平稳，但是对于速度变化的响应也会越慢
     */
    q = 0.8;
    Encoder_Bias *= q;
    Encoder_Bias += Encoder_Least * (1 - q);
    Encoder_Integral += Encoder_Bias;
    Encoder_Integral += Movement;
    if (Encoder_Integral > 10000) {Encoder_Integral = 10000;}
    if (Encoder_Integral < -10000) {Encoder_Integral = -10000;}
    if (Flag_Stop) {Encoder_Integral = 0;}
    Actual_Value = -P_velocity * Encoder_Bias / AMPLIFICATION - I_velocity * Encoder_Integral / AMPLIFICATION;
    return Actual_Value;
}

/**
 * @brief       小车的转向环计算，实际就是PD控制
 * @param       gyro：z轴的陀螺仪
 * @retval      Actual_Value：转向环的PID期望输出
 */
int PID_Turn(float gyro)
{
    static float Actual_Value;
    static float Turn_Target, Turn_Amplitude = 54;  /* Turn_Amplitude控制转向速度 */
    float Kp = P_turn, Kd;
    /* 蓝牙遥控转向 */
    if (Flag_Left) {Turn_Target = -Turn_Amplitude / Flag_Velocity;}
    else if (Flag_Right) {Turn_Target = Turn_Amplitude / Flag_Velocity;}
    else {Turn_Target = 0;}
    if (Flag_Front || Flag_Back) {Kd = D_turn;}
    else {Kd = 0;}      /* 转向时，取消陀螺仪纠正 */
    Actual_Value = Kp * Turn_Target / AMPLIFICATION + gyro * Kd / AMPLIFICATION;
    return Actual_Value;
}


