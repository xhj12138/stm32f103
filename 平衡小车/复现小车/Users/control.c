/**
 ****************************************************************************************************
 * @file        control.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       放置小车的电机驱动代码，直立环速度环等驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的控制程序，所有控制都在这里，来控制小车的直立和前进后退转向
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
 * @brief       中断服务程序中需要做的事情
                在HAL库中所有的外部中断服务函数都会调用此函数
 * @param       GPIO_Pin:中断引脚号
 * @retval      无
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
         usart_init(115200);                         /* 串口初始化为115200 */
         /* 获取MPU6050 DMP处理后的数据 */
        ret = mpu6050_dmp_get_data(&pit, &rol, &yaw);
        /* 获取MPU050加速度值 */
        ret += mpu6050_get_accelerometer(&acc_x, &acc_y, &acc_z);
        /* 获取MPU6050陀螺仪值 */
        ret += mpu6050_get_gyroscope(&gyr_x, &gyr_y, &gyr_z);
        /* 获取MPU6050温度值 */
        ret += mpu6050_get_temperature(&temp);
        if (ret == 0)
        {
            /* 上传相关数据信息至串口调试助手 */
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

/* AIN1、AIN2、BIN1、BIN2初始化 */
void TB6612_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    __HAL_RCC_GPIOB_CLK_ENABLE();     /* 使能PORTB时钟 */
    
    gpio_init_struct.Pin = AIN1_GPIO_PIN;                /* AIN1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;     /* 中速 */
    HAL_GPIO_Init(AIN1_GPIO_PORT, &gpio_init_struct);    /* AIN1引脚模式设置 */

    gpio_init_struct.Pin = AIN2_GPIO_PIN;                /* AIN2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;     /* 中速 */
    HAL_GPIO_Init(AIN2_GPIO_PORT, &gpio_init_struct);    /* AIN2引脚模式设置 */
    
    gpio_init_struct.Pin = BIN1_GPIO_PIN;                /* BIN1引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;     /* 中速 */
    HAL_GPIO_Init(BIN1_GPIO_PORT, &gpio_init_struct);    /* BIN1引脚模式设置 */
    
    gpio_init_struct.Pin = BIN2_GPIO_PIN;                /* BIN2引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;         /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_NOPULL;                 /* 无上下拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_MEDIUM;     /* 中速 */
    HAL_GPIO_Init(BIN2_GPIO_PORT, &gpio_init_struct);    /* BIN2引脚模式设置 */
    
    AIN1(0);
    AIN2(0);
    BIN1(0);
    BIN2(0);
}

/* 控制正反准，方向通过四个引脚控制，大小通过这个绝对值函数进行转换 */
int my_abs(int num)
{
    int tmp = 0;
    if (num < 0) {tmp = -num;}
    else tmp = num;
    return tmp;
}


/* 实现通过四路信号，控制两个电机的正反转 */
void Set_PWM(int motor_left, int motor_right)
{
    if (motor_left > 0)
    {
        /* 左轮参数为正，需要正转 */
        BIN1(1);
        BIN2(0);
    }
    else    /* 左轮参数为负，需要反转 */
    {
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
    else    /* 右轮参数为负，需要反转 */
    {
        AIN1(1);
        AIN2(0);
    }
    ATIM_TIM1_PWM_CH1_CCRX = my_abs(motor_right);
}


/* 限制比较值的大小，饱和模块 */
int PWM_Limit(int IN, int min, int max)
{
    int OUT = IN;
    if (OUT > max) OUT = max;
    if (OUT < min) OUT = min;
    return OUT;
}



ENCODE_TypeDef g_encode2;     /*编码器参数变量*/
ENCODE_TypeDef g_encode4;     /*编码器参数变量*/
/**
 * @brief       电机速度计算
 * @param       encode_now：当前编码器总的计数值
 *              ms：计算速度的间隔，中断50ms进入一次，例如ms = 50即5ms计算一次速度
 * @retval      无
 */
void speed_computer2(int32_t encode_now, uint8_t ms)
{
    uint8_t i = 0, j = 0;
    float temp = 0.0;
    static uint8_t sp_count = 0, k = 0;
    static float speed_arr[10] = {0.0};                     /* 存储速度进行滤波运算 */

    if (sp_count == ms)                                     /* 计算一次速度 */
    {
        /* 计算电机转速 
           第一步 ：计算ms毫秒内计数变化量
           第二步 ；计算1min内计数变化量：g_encode.speed * ((200 / ms) * 60 ，
           第三步 ：除以编码器旋转一圈的计数次数（倍频倍数 * 编码器分辨率）
           第四步 ：除以减速比即可得出电机转速
        */
        g_encode2.encode_now = encode_now;                                /* 取出编码器当前计数值 */
        g_encode2.speed = (g_encode2.encode_now - g_encode2.encode_old);    /* 计算编码器计数值的变化量 */
        
        speed_arr[k++] = (float)(g_encode2.speed * ((200 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO );    /* 保存电机转速 */
        
        g_encode2.encode_old = g_encode2.encode_now;          /* 保存当前编码器的值 */

        /* 累计10次速度值，后续进行滤波*/
        if (k == 10)
        {
            for (i = 10; i >= 1; i--)                       /* 冒泡排序*/
            {
                for (j = 0; j < (i - 1); j++) 
                {
                    if (speed_arr[j] > speed_arr[j + 1])    /* 数值比较 */
                    { 
                        temp = speed_arr[j];                /* 数值换位 */
                        speed_arr[j] = speed_arr[j + 1];
                        speed_arr[j + 1] = temp;
                    }
                }
            }
            
            temp = 0.0;
            
            for (i = 2; i < 8; i++)                         /* 去除两边高低数据 */
            {
                temp += speed_arr[i];                       /* 将中间数值累加 */
            }
            
            temp = (float)(temp / 6);                       /*求速度平均值*/
            
            /* 一阶低通滤波
             * 公式为：Y(n)= qX(n) + (1-q)Y(n-1)
             * 其中X(n)为本次采样值；Y(n-1)为上次滤波输出值；Y(n)为本次滤波输出值，q为滤波系数
             * q值越小则上一次输出对本次输出影响越大，整体曲线越平稳，但是对于速度变化的响应也会越慢
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
    static float speed_arr[10] = {0.0};                     /* 存储速度进行滤波运算 */

    if (sp_count == ms)                                     /* 计算一次速度 */
    {
        /* 计算电机转速 
           第一步 ：计算ms毫秒内计数变化量
           第二步 ；计算1min内计数变化量：g_encode.speed * ((200 / ms) * 60 ，
           第三步 ：除以编码器旋转一圈的计数次数（倍频倍数 * 编码器分辨率）
           第四步 ：除以减速比即可得出电机转速
        */
        g_encode4.encode_now = encode_now;                                /* 取出编码器当前计数值 */
        g_encode4.speed = (g_encode2.encode_now - g_encode4.encode_old);    /* 计算编码器计数值的变化量 */
        
        speed_arr[k++] = (float)(g_encode4.speed * ((200 / ms) * 60.0) / REDUCTION_RATIO / ROTO_RATIO );    /* 保存电机转速 */
        
        g_encode4.encode_old = g_encode4.encode_now;          /* 保存当前编码器的值 */

        /* 累计10次速度值，后续进行滤波*/
        if (k == 10)
        {
            for (i = 10; i >= 1; i--)                       /* 冒泡排序*/
            {
                for (j = 0; j < (i - 1); j++) 
                {
                    if (speed_arr[j] > speed_arr[j + 1])    /* 数值比较 */
                    { 
                        temp = speed_arr[j];                /* 数值换位 */
                        speed_arr[j] = speed_arr[j + 1];
                        speed_arr[j + 1] = temp;
                    }
                }
            }
            
            temp = 0.0;
            
            for (i = 2; i < 8; i++)                         /* 去除两边高低数据 */
            {
                temp += speed_arr[i];                       /* 将中间数值累加 */
            }
            
            temp = (float)(temp / 6);                       /*求速度平均值*/
            
            /* 一阶低通滤波
             * 公式为：Y(n)= qX(n) + (1-q)Y(n-1)
             * 其中X(n)为本次采样值；Y(n-1)为上次滤波输出值；Y(n)为本次滤波输出值，q为滤波系数
             * q值越小则上一次输出对本次输出影响越大，整体曲线越平稳，但是对于速度变化的响应也会越慢
             */
            velocity_right = (float)( ((float)0.48 * temp) + (velocity_right * (float)0.52) );
            velocity_right *= PI * Diameter;
            k = 0;
        }
        sp_count = 0;
    }
    sp_count ++;
}

