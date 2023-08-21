/**
 ****************************************************************************************************
 * @file        show.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       ������ʾ����
 ****************************************************************************************************
 * @attention
 *
 * ��ȤС������ʾ���֣�������OELD,APP����ʾ
 *
 ****************************************************************************************************
*/


#include "show.h"
#include "./BSP/OLED/oled.h"

float Velocity_Left,Velocity_Right;	//�����ٶ�(mm/s)


/**
 * @brief       OLED��ʾ���ݱ�д
 * @param       ��
 * @retval      ��
 */
void oled_show(void)
{
    oled_show_string(0, 0, "0.96' OLED TEST", 16);
    oled_show_string(0, 20, "Time 2023/8/13", 12);
    oled_show_string(0, 44, "ASCII:", 12);
    oled_show_string(64,44, "CODE:", 12);
    oled_refresh_gram(); /* ������ʾ��OLED */
}


