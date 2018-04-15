#ifndef __DZXH_STM32_SYSTICK_H__
#define __DZXH_STM32_SYSTICK_H__

#include "stm32f10x.h"

#ifndef configTICK_RATE_HZ			//每1/configTICK_RATE_HZ秒中断一次
#define configTICK_RATE_HZ	(1000)	//时钟节拍频率，这里设置为1000，周期就是1ms
#endif

//定义进入滴答中断 SysTick_Handler 时间(ms)
#define SYSTEMTICK_PERIOD_MS  1/configTICK_RATE_HZ

void SysTick_delay_init(void);
void SysTick_delay_ms(u16 nms);
void SysTick_delay_us(u32 nus);

#endif

