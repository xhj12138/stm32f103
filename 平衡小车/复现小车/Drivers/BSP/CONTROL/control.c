/**
 ****************************************************************************************************
 * @file        control.c
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
float Velocity_Left, Velocity_Right;            /* ���ֵ����ٶ� */
int Motor_Left, Motor_Right;                    /* �����PWM�ıȽ�ֵ������ռ�ձ� */
float pitch, roll, yaw;                         /* ͨ��MPU6050��ȡ��ŷ���� */
int16_t gyro_x, gyro_y, gyro_z;                 /* ͨ��MPU6050��õ�������ֵ */
int16_t acc_x, acc_y, acc_z;                    /* ͨ��MPU6050��õļ��ٶ�ֵ */
float Angle_Balance, Gyro_Balance, Gyro_Turn;   /* ƽ����� ƽ�������� ת�������� */
float Acceleration_Z;                           /* Z����ٶȼ� */
int Voltage;                                    /* ��ص�ѹ */
int16_t temp;                                   /* MPU6050�¶� */
uint16_t atim_psc = 1 - 1, atim_arr = 7200 - 1; /* TIM1��Ԥ��Ƶϵ�����Զ���װ��ֵ */
float P_stand = 25000, D_stand = 120;           /* ֱ������PID���� */
float P_velocity = 13000, I_velocity = 65;      /* �ٶȻ���PID���� */
float P_turn = 4000, D_turn = 20;               /* ת�򻷵�PID���� */
int PWM_Left_Duty = 0, PWM_Right_Duty = 0;
/**
 * @brief       �жϷ����������Ҫ��������
                ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
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
 * @brief       TB6612��Ҫ�ĳ�ʼ������
 * @note
 *              ��ʼ����Ӧ��GPIO����
 * @param       ��
 * @retval      ��
 */
void TB6612_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    AIN1_GPIO_CLK_ENABLE();     /* ʹ��AIN1ʱ�� */
    AIN2_GPIO_CLK_ENABLE();     /* ʹ��AIN2ʱ�� */
    BIN1_GPIO_CLK_ENABLE();     /* ʹ��BIN1ʱ�� */
    BIN2_GPIO_CLK_ENABLE();     /* ʹ��BIN2ʱ�� */
    
    gpio_init_struct.Pin = AIN1_GPIO_PIN;                /* AIN1���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;       /* ���� */
    HAL_GPIO_Init(AIN1_GPIO_PORT, &gpio_init_struct);    /* AIN1����ģʽ���� */

    gpio_init_struct.Pin = AIN2_GPIO_PIN;                /* AIN2���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;       /* ���� */
    HAL_GPIO_Init(AIN2_GPIO_PORT, &gpio_init_struct);    /* AIN2����ģʽ���� */
    
    gpio_init_struct.Pin = BIN1_GPIO_PIN;                /* BIN1���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;       /* ���� */
    HAL_GPIO_Init(BIN1_GPIO_PORT, &gpio_init_struct);    /* BIN1����ģʽ���� */
    
    gpio_init_struct.Pin = BIN2_GPIO_PIN;                /* BIN2���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;       /* ���� */
    HAL_GPIO_Init(BIN2_GPIO_PORT, &gpio_init_struct);    /* BIN2����ģʽ���� */
    
    AIN1(0);
    AIN2(0);
    BIN1(0);
    BIN2(0);
}

/**
 * @brief       �������ֵ
 * @param       num��ԭʼֵ
 * @retval      tmp������ֵ
 */
int my_abs(int num)
{
    int tmp = 0;
    if (num < 0) {tmp = -num;}
    else tmp = num;
    return tmp;
}


/**
 * @brief       ���ö�ʱ��1����·PWM�����ռ�ձȣ����Ƶ��ת��
 * @param       motor_left��С�����ֵ�����ռ�ձ�
 * @param       motor_right��С�����ֵ�����ռ�ձ�
 * @retval      ��
 */
void Set_PWM(int motor_left, int motor_right)
{
    if (motor_left > 0)
    {
        /* ���ֲ���Ϊ������Ҫ��ת */
        BIN1(1);
        BIN2(0);
    }
    if (motor_left < 0)
    {
        /* ���ֲ���Ϊ������Ҫ��ת */
        BIN1(0);
        BIN2(1);
    }
    ATIM_TIM1_PWM_CH4_CCRX = my_abs(motor_left);
    
    if (motor_right > 0)
    {
        /* ���ֲ���Ϊ������Ҫ��ת */
        AIN1(0);
        AIN2(1);
    }
    if (motor_right < 0)
    {
        /* ���ֲ���Ϊ������Ҫ��ת */
        AIN1(1);
        AIN2(0);
    }
    ATIM_TIM1_PWM_CH1_CCRX = my_abs(motor_right);
}


/**
 * @brief       ����ģ�飬����PWM��������ֵ
 * @param       IN������ļ���ֵ
 * @param       min���������Сֵ
 * @param       max����������ֵ
 * @retval      OUT�����ͼ���õ���PWM���ֵ
 */
int PWM_Limit(int IN, int min, int max)
{
    int OUT = IN;
    if (OUT > max) OUT = max;
    if (OUT < min) OUT = min;
    return OUT;
}

/**
 * @brief       ��ȡ�����������㵱ǰ�������ٶ�
                ��λ��mm/s
 * @param       ��
 * @retval      ��
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
 * @brief       ��ȡ��ǰС���Ƕ�
                ����ʵ��ֱ�ӻ���MPU6050�Դ���DMP�㷨
 * @param       way:ʹ�÷�����1.DMP
 * @retval      0: ����ִ�гɹ�
 *              1: ����ִ��ʧ��
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
 * @brief       С����ֱ�������㣬ʵ�ʾ���PD����
 * @param       Angle��MPU6050��ȡ�õ��ĵ�ǰ��б�Ƕȣ�����P����
 * @param       Gyro��MPU6050��ȡ�õ��Ľ��ٶȣ��൱�ڽǶ�΢�֣�����D����
 * @retval      Actual_Value��ֱ������PID�������
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
 * @brief       С�����ٶȻ����㣬ʵ�ʾ���PI����
 * @param       encoder_left�������������
 * @param       encoder_right���ұ���������
 * @retval      Actual_Value���ٶȻ���PID�������
 */
int PID_Velocity(int encoder_left, int encoder_right)
{
    static float Actual_Value;
    static float Encoder_Least, q, Encoder_Bias, Encoder_Integral;
    static float Target_Velocity, Movement;
    /***********************************************ң��ǰ�����˲���********************************************/
    Target_Velocity = 30;
    if (Flag_Front) {Movement = Target_Velocity / Flag_Velocity;}
    else if (Flag_Back) {Movement = -Target_Velocity / Flag_Velocity;}
    else Movement = 0;
    /***********************************************�ٶȻ�PI����********************************************/
    Encoder_Least = 0 - (encoder_left + encoder_right);
    /* һ�׵�ͨ�˲�
     * ��ʽΪ��Y(n)= qX(n) + (1-q)Y(n-1)
     * ����X(n)Ϊ���β���ֵ��Y(n-1)Ϊ�ϴ��˲����ֵ��Y(n)Ϊ�����˲����ֵ��qΪ�˲�ϵ��
     * qֵԽС����һ������Ա������Ӱ��Խ����������Խƽ�ȣ����Ƕ����ٶȱ仯����ӦҲ��Խ��
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
 * @brief       С����ת�򻷼��㣬ʵ�ʾ���PD����
 * @param       gyro��z���������
 * @retval      Actual_Value��ת�򻷵�PID�������
 */
int PID_Turn(float gyro)
{
    static float Actual_Value;
    static float Turn_Target, Turn_Amplitude = 54;  /* Turn_Amplitude����ת���ٶ� */
    float Kp = P_turn, Kd;
    /* ����ң��ת�� */
    if (Flag_Left) {Turn_Target = -Turn_Amplitude / Flag_Velocity;}
    else if (Flag_Right) {Turn_Target = Turn_Amplitude / Flag_Velocity;}
    else {Turn_Target = 0;}
    if (Flag_Front || Flag_Back) {Kd = D_turn;}
    else {Kd = 0;}      /* ת��ʱ��ȡ�������Ǿ��� */
    Actual_Value = Kp * Turn_Target / AMPLIFICATION + gyro * Kd / AMPLIFICATION;
    return Actual_Value;
}


