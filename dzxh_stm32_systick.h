#ifndef __DZXH_STM32_SYSTICK_H__
#define __DZXH_STM32_SYSTICK_H__

#include "stm32f10x.h"

#ifndef configTICK_RATE_HZ			//ÿ1/configTICK_RATE_HZ���ж�һ��
#define configTICK_RATE_HZ	(1000)	//ʱ�ӽ���Ƶ�ʣ���������Ϊ1000�����ھ���1ms
#endif

//�������δ��ж� SysTick_Handler ʱ��(ms)
#define SYSTEMTICK_PERIOD_MS  1/configTICK_RATE_HZ

void SysTick_delay_init(void);
void SysTick_delay_ms(u16 nms);
void SysTick_delay_us(u32 nus);

#endif

