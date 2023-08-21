/**
 ****************************************************************************************************
 * @file        control.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       ����С���ĵ���������룬ֱ�����ٶȻ�����������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС���Ŀ��Ƴ������п��ƶ������������С����ֱ����ǰ������ת��
 *
 ****************************************************************************************************
 */
 
 
#include "control.h"
#include "./BSP/TIMER/atim.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/EXTI/exti.h"
#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/eMPL/inv_mpu.h"
#include "./SYSTEM/usart/usart.h"

float velocity_left, velocity_right;
/**
 * @brief       �жϷ����������Ҫ��������
                ��HAL�������е��ⲿ�жϷ�����������ô˺���
 * @param       GPIO_Pin:�ж����ź�
 * @retval      ��
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == MPU6050_INT_GPIO_PIN)
    {
        uint8_t ret;
        float pit, rol, yaw;
        int16_t acc_x, acc_y, acc_z;
        int16_t gyr_x, gyr_y, gyr_z;
        int16_t temp;
         usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
         /* ��ȡMPU6050 DMP���������� */
        ret = mpu6050_dmp_get_data(&pit, &rol, &yaw);
        /* ��ȡMPU050���ٶ�ֵ */
        ret += mpu6050_get_accelerometer(&acc_x, &acc_y, &acc_z);
        /* ��ȡMPU6050������ֵ */
        ret += mpu6050_get_gyroscope(&gyr_x, &gyr_y, &gyr_z);
        /* ��ȡMPU6050�¶�ֵ */
        ret += mpu6050_get_temperature(&temp);
        if (ret == 0)
        {
            /* �ϴ����������Ϣ�����ڵ������� */
            printf("pit: %.2f, rol: %.2f, yaw: %.2f, ", pit, rol, yaw);
            printf("acc_x: %d, acc_y: %d, acc_z: %d, ", acc_x, acc_y, acc_z);
            printf("gyr_x: %d, gyr_y: %d, gyr_z: %d, ", gyr_x, gyr_y, gyr_z);
            printf("temp: %d\r\n", temp);
        }
        Set_PWM(0, 5000);
        speed_computer2(gtim2_get_encode(), 10);
        speed_computer4(gtim4_get_encode(), 10);
        printf("velocity left = %.2f\r\n", velocity_left);
        printf("velocity right = %.2f\r\n", velocity_right);
    }
}

/* AIN1��AIN2��BIN1��BIN2��ʼ�� */
void TB6612_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    __HAL_RCC_GPIOB_CLK_ENABLE();     /* ʹ��PORTBʱ�� */
    
    gpio_init_struct.Pin = AIN1_GPIO_PIN;                /* AIN1���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;     /* ���� */
    HAL_GPIO_Init(AIN1_GPIO_PORT, &gpio_init_struct);    /* AIN1����ģʽ���� */

    gpio_init_struct.Pin = AIN2_GPIO_PIN;                /* AIN2���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;     /* ���� */
    HAL_GPIO_Init(AIN2_GPIO_PORT, &gpio_init_struct);    /* AIN2����ģʽ���� */
    
    gpio_init_struct.Pin = BIN1_GPIO_PIN;                /* BIN1���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;     /* ���� */
    HAL_GPIO_Init(BIN1_GPIO_PORT, &gpio_init_struct);    /* BIN1����ģʽ���� */
    
    gpio_init_struct.Pin = BIN2_GPIO_PIN;                /* BIN2���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* ������� */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* �������� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;     /* ���� */
    HAL_GPIO_Init(BIN2_GPIO_PORT, &gpio_init_struct);    /* BIN2����ģʽ���� */
    
    AIN1(0);
    AIN2(0);
    BIN1(0);
    BIN2(0);
}

/* ��������׼������ͨ���ĸ����ſ��ƣ���Сͨ���������ֵ��������ת�� */
int my_abs(int num)
{
    int tmp = 0;
    if (num < 0) {tmp = -num;}
    else tmp = num;
    return tmp;
}


/* ʵ��ͨ����·�źţ������������������ת */
void Set_PWM(int motor_left, int motor_right)
{
    if (motor_left > 0)
    {
        /* ���ֲ���Ϊ������Ҫ��ת */
        BIN1(1);
        BIN2(0);
    }
    else    /* ���ֲ���Ϊ������Ҫ��ת */
    {
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
    else    /* ���ֲ���Ϊ������Ҫ��ת */
    {
        AIN1(1);
        AIN2(0);
    }
    ATIM_TIM1_PWM_CH1_CCRX = my_abs(motor_right);
}


/* ���ƱȽ�ֵ�Ĵ�С������ģ�� */
int PWM_Limit(int IN, int min, int max)
{
    int OUT = IN;
    if (OUT > max) OUT = max;
    if (OUT < min) OUT = min;
    return OUT;
}



ENCODE_TypeDef g_encode2;     /*��������������*/
ENCODE_TypeDef g_encode4;     /*��������������*/
/**
 * @brief       ����ٶȼ���
 * @param       encode_now����ǰ�������ܵļ���ֵ
 *              ms�������ٶȵļ�����ж�50ms����һ�Σ�����ms = 50��5ms����һ���ٶ�
 * @retval      ��
 */
void speed_computer2(int32_t encode_now, uint8_t ms)
{
    uint8_t i = 0, j = 0;
    float temp = 0.0;
    static uint8_t sp_count = 0, k = 0;
    static float speed_arr[10] = {0.0};                     /* �洢�ٶȽ����˲����� */

    if (sp_count == ms)                                     /* ����һ���ٶ� */
    {
        /* ������ת�� 
           ��һ�� ������ms�����ڼ����仯��
           �ڶ��� ������1min�ڼ����仯����g_encode.speed * ((200 / ms) * 60 ��
           ������ �����Ա�������תһȦ�ļ�����������Ƶ���� * �������ֱ��ʣ�
           ���Ĳ� �����Լ��ٱȼ��ɵó����ת��
        */
        g_encode2.encode_now = encode_now;                                /* ȡ����������ǰ����ֵ */
        g_encode2.speed = (g_encode2.encode_now - g_encode2.encode_old);    /* �������������ֵ�ı仯�� */
        
        speed_arr[k++] = (float)(g_encode2.speed * ((200 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO );    /* ������ת�� */
        
        g_encode2.encode_old = g_encode2.encode_now;          /* ���浱ǰ��������ֵ */

        /* �ۼ�10���ٶ�ֵ�����������˲�*/
        if (k == 10)
        {
            for (i = 10; i >= 1; i--)                       /* ð������*/
            {
                for (j = 0; j < (i - 1); j++) 
                {
                    if (speed_arr[j] > speed_arr[j + 1])    /* ��ֵ�Ƚ� */
                    { 
                        temp = speed_arr[j];                /* ��ֵ��λ */
                        speed_arr[j] = speed_arr[j + 1];
                        speed_arr[j + 1] = temp;
                    }
                }
            }
            
            temp = 0.0;
            
            for (i = 2; i < 8; i++)                         /* ȥ�����߸ߵ����� */
            {
                temp += speed_arr[i];                       /* ���м���ֵ�ۼ� */
            }
            
            temp = (float)(temp / 6);                       /*���ٶ�ƽ��ֵ*/
            
            /* һ�׵�ͨ�˲�
             * ��ʽΪ��Y(n)= qX(n) + (1-q)Y(n-1)
             * ����X(n)Ϊ���β���ֵ��Y(n-1)Ϊ�ϴ��˲����ֵ��Y(n)Ϊ�����˲����ֵ��qΪ�˲�ϵ��
             * qֵԽС����һ������Ա������Ӱ��Խ����������Խƽ�ȣ����Ƕ����ٶȱ仯����ӦҲ��Խ��
             */
            velocity_left = (float)( ((float)0.48 * temp) + (velocity_left * (float)0.52) );
            velocity_left *= PI * Diameter;
            k = 0;
        }
        sp_count = 0;
    }
    sp_count ++;
}


void speed_computer4(int32_t encode_now, uint8_t ms)
{
    uint8_t i = 0, j = 0;
    float temp = 0.0;
    static uint8_t sp_count = 0, k = 0;
    static float speed_arr[10] = {0.0};                     /* �洢�ٶȽ����˲����� */

    if (sp_count == ms)                                     /* ����һ���ٶ� */
    {
        /* ������ת�� 
           ��һ�� ������ms�����ڼ����仯��
           �ڶ��� ������1min�ڼ����仯����g_encode.speed * ((200 / ms) * 60 ��
           ������ �����Ա�������תһȦ�ļ�����������Ƶ���� * �������ֱ��ʣ�
           ���Ĳ� �����Լ��ٱȼ��ɵó����ת��
        */
        g_encode4.encode_now = encode_now;                                /* ȡ����������ǰ����ֵ */
        g_encode4.speed = (g_encode2.encode_now - g_encode4.encode_old);    /* �������������ֵ�ı仯�� */
        
        speed_arr[k++] = (float)(g_encode4.speed * ((200 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO );    /* ������ת�� */
        
        g_encode4.encode_old = g_encode4.encode_now;          /* ���浱ǰ��������ֵ */

        /* �ۼ�10���ٶ�ֵ�����������˲�*/
        if (k == 10)
        {
            for (i = 10; i >= 1; i--)                       /* ð������*/
            {
                for (j = 0; j < (i - 1); j++) 
                {
                    if (speed_arr[j] > speed_arr[j + 1])    /* ��ֵ�Ƚ� */
                    { 
                        temp = speed_arr[j];                /* ��ֵ��λ */
                        speed_arr[j] = speed_arr[j + 1];
                        speed_arr[j + 1] = temp;
                    }
                }
            }
            
            temp = 0.0;
            
            for (i = 2; i < 8; i++)                         /* ȥ�����߸ߵ����� */
            {
                temp += speed_arr[i];                       /* ���м���ֵ�ۼ� */
            }
            
            temp = (float)(temp / 6);                       /*���ٶ�ƽ��ֵ*/
            
            /* һ�׵�ͨ�˲�
             * ��ʽΪ��Y(n)= qX(n) + (1-q)Y(n-1)
             * ����X(n)Ϊ���β���ֵ��Y(n-1)Ϊ�ϴ��˲����ֵ��Y(n)Ϊ�����˲����ֵ��qΪ�˲�ϵ��
             * qֵԽС����һ������Ա������Ӱ��Խ����������Խƽ�ȣ����Ƕ����ٶȱ仯����ӦҲ��Խ��
             */
            velocity_right = (float)( ((float)0.48 * temp) + (velocity_right * (float)0.52) );
            velocity_right *= PI * Diameter;
            k = 0;
        }
        sp_count = 0;
    }
    sp_count ++;
}

