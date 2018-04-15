#ifndef _DZXH_STM32_TIM_
#define _DZXH_STM32_TIM_
#include "stm32f10x.h"
#define TIM_ENABLE 1
#define TIM_DISABLE 0


extern int tim2_ready_buf_ok;	//超时标志 1未超时 0超时

//功能：使能或失能定时器
//参数1：定时器的编号(范围 2~7)
//参数2: 0关闭(TIM_DISABLE)，1开启(TIM_ENABLE)
//例：Tim_Cmd(5,1);	//使能定时器5
void Tim_Cmd(u8 TIMx,u8 flag);

u8 TIM_Common_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority);
//例：	TIM_Common_Init(5,7200,10000,TIM_CounterMode_Up,0,1);	//定时器初始化
//定制器5，预分频7200,1秒进入一次中断，向上计数模式，抢断优先级级别0，响应优先级级别1
/*******说明******************************************************************/
/*
定时器初始化 （默认时钟分割为TIM_CKD_DIV1，TIM输出比较极性高，使能关）
			(默认：4个抢断优先级，4个相应优先级)
TIM_Common_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority)

参数1：选用的定时器；(范围 2~7)
						2	TIM2
						3	TIM3
						4	TIM4
						5	TIM5
						6	TIM6
						7	TIM7
参数2：时钟预分频值（不用减1）；取值范围：0——65535

参数3：装入活动的自动重装载寄存器周期的值（设定周期）取值范围：0——65535

参数4：计数模式
				TIM_CounterMode_Up 				TIM 向上计数模式
				TIM_CounterMode_Down 			TIM 向下计数模式
				TIM_CounterMode_CenterAligned1 	TIM 中央对齐模式 1 计数模式
				TIM_CounterMode_CenterAligned2 	TIM 中央对齐模式 2 计数模式
				TIM_CounterMode_CenterAligned3 	TIM 中央对齐模式 3 计数模式
				
参数5：对应抢断优先级级别		取值范围(0,1,2,3)	数值越低优先级越高

参数6：对应响应优先级级别		取值范围(0,1,2,3)	数值越低优先级越高

返回值：0成功，1失败
*/
/********************************************************************************/
#endif

