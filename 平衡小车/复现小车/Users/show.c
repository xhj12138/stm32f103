/**
 ****************************************************************************************************
 * @file        show.c
 * @author      Xia
 * @version     V1.0
 * @date        2023-08-13
 * @brief       数据显示代码
 ****************************************************************************************************
 * @attention
 *
 * 轮趣小车的显示部分，来进行OELD,APP的显示
 *
 ****************************************************************************************************
*/


#include "show.h"
#include "./BSP/OLED/oled.h"

float Velocity_Left,Velocity_Right;	//车轮速度(mm/s)


/**
 * @brief       OLED显示内容编写
 * @param       无
 * @retval      无
 */
void oled_show(void)
{
    oled_show_string(0, 0, "0.96' OLED TEST", 16);
    oled_show_string(0, 20, "Time 2023/8/13", 12);
    oled_show_string(0, 44, "ASCII:", 12);
    oled_show_string(64,44, "CODE:", 12);
    oled_refresh_gram(); /* 更新显示到OLED */
}


