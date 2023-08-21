/**
 ******************************************************************************
 * @file     main.c
 * @author   Xia
<<<<<<< HEAD
 * @version  V1.1
 * @date     2023-08-21
=======
 * @version  V1.0
 * @date     2023-08-13
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 * @brief    ��ȤС����main����
 ******************************************************************************
 * @attention
 * 
 * ��ȤС����ֲ����
<<<<<<< HEAD
 *
 *
 * �޸�˵��
 * V1.0 20230813
 * ��һ�η���
 * 1.��ɴ��ڡ��ⲿ�жϡ�ADC����ʱ��1����ʱ��2����ʱ��4��MPU6050��TB6612��LED��KEY��OLED�ĳ�ʼ��
 * 2.��ɻ���MPU6050�Դ���DMPֱ�Ӷ�ȡ����
 * 3.OLED�Ĳ�����ʾ����
 * V1.1
 * 1.����������ڵĳ�ʼ��
 * 2.��дֱ�������ٶȻ���ת�򻷵Ŀ��ƴ���
 * 3.�������Ȥ�Ƽ�APP���������ݴ��ڴ���
 * 4.���ң�ع�����APP��ʾ��OLED��ʾ����
 *
 *
=======
 
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 ******************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/TIMER/atim.h"
#include "./BSP/TIMER/gtim.h"
#include "./BSP/KEY/key.h"
#include "./BSP/OLED/oled.h"
#include "./BSP/ADC/adc.h"
#include "./BSP/EXTI/exti.h"
<<<<<<< HEAD
#include "./BSP/CONTROL/control.h"
#include "./BSP/SHOW/show.h"
#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/eMPL/inv_mpu.h"
#include "./BSP/BT04/bt04.h"

extern volatile uint8_t delay_flag, delay_50;
extern uint16_t atim_psc, atim_arr;
extern float P_stand, D_stand;
extern float P_velocity, I_velocity;

int main(void)
{
=======
#include "control.h"
#include "show.h"

#include "./BSP/MPU6050/mpu6050.h"
#include "./BSP/MPU6050/eMPL/inv_mpu.h"

extern TIM_HandleTypeDef g_tim1_handle;
extern volatile uint8_t delay_flag, delay_50;

int main(void)
{
    uint8_t key = 0;
    float voltage = 0;
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    uint8_t ret = 0;
    
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(RCC_PLL_MUL9);         /* ����ʱ��, 72Mhz */
<<<<<<< HEAD
    
    led_init();                                 /* LED��ʼ�� */
    key_init();                                 /* ������ʼ�� */
    usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
    bt04_uart_init(9600);                       /* �������ڳ�ʼ��Ϊ9600 */
    TB6612_init();                              /* ��ʼ��ֱ����������� */
    atim_tim1_pwm_init(atim_psc, atim_arr);     /* 72M / 7200 = 10kHz */
    gtim_tim2_encoder_init(1 - 1, 0XFFFF - 1);  /* ������1������Ƶֱ��65536 */
    gtim_tim4_encoder_init(1 - 1, 0XFFFF - 1);  /* ������2������Ƶֱ��65536 */
    adc_init();                                 /* ��ʼ��ADC */
    
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();              /* ����JTAG��ʹ��SWD���� */
    
    delay_init(72);                             /* ��ʱ��ʼ�� */
    oled_init();                                /* oled��ʼ�� */
    ret = mpu6050_init();                       /* ��ʼ��MPU6050 */
    ret += mpu6050_dmp_init();                  /* ��ʼ��MPU6050 DMP */
=======
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();              /* ����JTAG��ʹ��SWD���� */
    delay_init(72);                             /* ��ʱ��ʼ�� */
    led_init();                                 /* LED��ʼ�� */
    key_init();                                 /* ������ʼ�� */
    usart_init(115200);                         /* ���ڳ�ʼ��Ϊ115200 */
    atim_tim1_pwm_init(1 - 1, 7199 - 1);        /* 72M / 7200 = 10kHz */
    gtim_tim2_encoder_init(1 - 1, 0XFFFF - 1);  /* ������1������Ƶֱ��65536 */
    gtim_tim4_encoder_init(1 - 1, 0XFFFF - 1);  /* ������2������Ƶֱ��65536 */
    oled_init();                                /* oled��ʼ�� */
    adc_init();                                 /* ��ʼ��ADC */
    TB6612_init();                              /* ��ʼ��ֱ����������� */
    ret = mpu6050_init();                       /* ��ʼ��MPU6050 */
    ret = mpu6050_dmp_init();                   /* ��ʼ��MPU6050 DMP */
    if (!ret) printf("MPU6050 init successful!\r\n");
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
    extix_init();                               /* �ⲿ�жϳ�ʼ�� */
    
    while(1)
    { 
<<<<<<< HEAD
        oled_show();
        APP_Show();
        delay_flag = 1;
        delay_50 = 0;
        while (delay_flag);
=======
        key = key_scan(0);
        if (key == KEY_PRES)
        {
            LED_TOGGLE();
        }
        
        voltage = adc_get_battery_voltage(ADC_ADCX_CHY, 20);
        
        
        //printf("encode = %d\r\n", gtim2_get_encode);
        
        
        
        delay_flag = 1;
        delay_50 = 0;
        while (delay_flag);
        
        oled_show();
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735

    }
}


