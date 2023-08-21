/**
 ****************************************************************************************************
 * @file        adc.h
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       ADC 驱动代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车ADC驱动
 * 用以检测电池的电压
 * 接口在PA6，所以是ADC_Channel6
 *
<<<<<<< HEAD
 *
 * 修改说明
 * V1.0 20230813
 * 第一次发布
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
/* ADC及引脚 定义 */

#define ADC_ADCX_CHY_GPIO_PORT              GPIOA
#define ADC_ADCX_CHY_GPIO_PIN               GPIO_PIN_6
#define ADC_ADCX_CHY_GPIO_CLK_ENABLE()      do{ __HAL_RCC_GPIOA_CLK_ENABLE(); }while(0)  /* PA口时钟使能 */

#define ADC_ADCX                            ADC1 
#define ADC_ADCX_CHY                        ADC_CHANNEL_6                                /* 通道Y,  0 <= Y <= 17 */ 
#define ADC_ADCX_CHY_CLK_ENABLE()           do{ __HAL_RCC_ADC1_CLK_ENABLE(); }while(0)   /* ADC1 时钟使能 */

#define ADC_MAX                             3.3         /* ADC可测量的最大值 */
#define ADC_MAX_NUM                         4095        /* 对应最大量程值的最大测量值 */
<<<<<<< HEAD
#define Voltage_Divider                     11          /* 原理图所对应的分压系数 */
=======
#define Voltage_Divider                     0.11        /* 原理图所对应的分压系数 */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735

/******************************************************************************************/

void adc_init(void);                                                /* ADC初始化 */
void adc_channel_set(ADC_HandleTypeDef *adc_handle, uint32_t ch,uint32_t rank, uint32_t stime); /* ADC通道设置 */
uint32_t adc_get_result(uint32_t ch);                               /* 获得某个通道值  */
uint32_t adc_get_result_average(uint32_t ch, uint8_t times);        /* 得到某个通道给定次数采样的平均值 */
<<<<<<< HEAD
int adc_get_battery_voltage(uint32_t ch);                           /* 将ADC读取值转化为电池电压，单位为mV */
//int adc_get_battery_voltage(uint32_t ch, uint8_t times);                           /* 将ADC读取值转化为电池电压，单位为mV */
=======
float adc_get_battery_voltage(uint32_t ch, uint8_t times);       /* 将平均的ADC读取值转化为电池电压，单位为mV */
>>>>>>> cfa0758316210b1f15f08368ce0a9cc75cf23735

#endif 















