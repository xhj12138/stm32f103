/**
 ****************************************************************************************************
 * @file        adc.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       ADC ��������
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС��ADC����
 * ���Լ���صĵ�ѹ
 * �ӿ���PA6��������ADC_Channel6
 *
<<<<<<< HEAD
 *
 * �޸�˵��
 * V1.0 20230813
 * ��һ�η���
 *
 *
=======
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735
 ****************************************************************************************************
 */

#ifndef __ADC_H
#define __ADC_H


#include "./SYSTEM/sys/sys.h"


/******************************************************************************************/
/* ADC������ ���� */

#define ADC_ADCX_CHY_GPIO_PORT              GPIOA
#define ADC_ADCX_CHY_GPIO_PIN               GPIO_PIN_6
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA��ʱ��ʹ�� */

#define ADC_ADCX                            ADC1 
#define ADC_ADCX_CHY                        ADC_CHANNEL_6                                /* ͨ��Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)   /* ADC1 ʱ��ʹ�� */

#define ADC_MAX                             3.3         /* ADC�ɲ��������ֵ */
#define ADC_MAX_NUM                         4095        /* ��Ӧ�������ֵ��������ֵ */
<<<<<<< HEAD
#define Voltage_Divider                     11          /* ԭ��ͼ����Ӧ�ķ�ѹϵ�� */
=======
#define Voltage_Divider                     0.11        /* ԭ��ͼ����Ӧ�ķ�ѹϵ�� */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735

/******************************************************************************************/

void adc_init(void);                                                /* ADC��ʼ�� */
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch,uint32_t rank, uint32_t stime); /* ADCͨ������ */
uint32_t adc_get_result(uint32_t ch);                               /* ���ĳ��ͨ��ֵ  */
uint32_t adc_get_result_average(uint32_t ch, uint8_t times);        /* �õ�ĳ��ͨ����������������ƽ��ֵ */
<<<<<<< HEAD
int adc_get_battery_voltage(uint32_t ch);                           /* ��ADC��ȡֵת��Ϊ��ص�ѹ����λΪmV */
//int adc_get_battery_voltage(uint32_t ch, uint8_t times);                           /* ��ADC��ȡֵת��Ϊ��ص�ѹ����λΪmV */
=======
float adc_get_battery_voltage(uint32_t ch, uint8_t times);       /* ��ƽ����ADC��ȡֵת��Ϊ��ص�ѹ����λΪmV */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735

#endif 















