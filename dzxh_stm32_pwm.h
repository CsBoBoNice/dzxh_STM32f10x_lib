#ifndef _DZXH_STM32_PWM_H_ 
#define _DZXH_STM32_PWM_H_
#include "stm32f10x.h"

u8 TIM_PWM_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,u16 TIM_pulse,u16 TIM_channel,u8 remap_pwm);//功能：改变PWM占空比

void Change_PWM_pulse(TIM_TypeDef* TIM,u8 TIM_channel,u16 pulse);//功能：改变PWM周期

void Change_PWM_period(TIM_TypeDef* TIM,u16 TIM_period);//功能：改变PWM脉冲宽度


/******使用方法******************************************************************/
/*
	TIM_PWM_Init(1,72,20000,1100,1，0);	//PWM初始化
	
	Change_PWM_period( TIM1,10000);		//改变PWM周期
	
	Change_PWM_pulse(TIM1,2,600);		//改变PWM占空比
*/
/***************************************************************************/
/*
//pwm初始化 （默认时钟分割为1，向上计数，TIM输出比较极性高，开使能）
//参数1：选用的定时器；(范围 1,2,3,4,)
						1  	TIM1
						2	TIM2
						3	TIM3
						4	TIM4
						5	TIM5
//参数2：时钟预分频值（不用减1）；
//参数3：装入活动的自动重装载寄存器周期的值（设定周期）
//参数4：待装入捕获比较寄存器的脉冲值（设定脉冲高电平时间）
//参数5：定时器通道(范围 1,2,3,4,)
//参数6：引脚重映射	(范围 参考下表)
//定时器引脚：

定时器	引脚重映像		通道	1	  2	   3	4

TIM1	0 没重映像 				PA8   PA9  PA10  PA11 
		1 完全重映相			PE9	  PE11 PE13	 PE14

TIM2	0 没重映相				PA0   PA1  PA2   PA3 
		1 部分重映相1			PA15  PB3  PA2	 PA3
		2 部分重映像2			PA0   PA1  PB10	 PB11
		3 完全从映像			PA15  PB3  PB10  PB11

TIM3	0 没重映相				PA6   PA7  PB0   PB1
		1 部分重映像			PB4   PB5  PB0   PB1
		2 完全重映像			PC6   PC7  PC8   PC9

TIM4	0 没重映像				PB6   PB7  PB8   PB9
		1 完全重映像			PD12  PD13 PD14  PD15

TIM5    0 没重映像				PA0   PA1  PA2   PA3

				定时器	通道	1	 2	  3	    4
				TIM1 			PA8  PA9  PA10  PA11 
				TIM2 			PA0  PA1  PA2   PA3 
				TIM3 			PA6  PA7  PB0   PB1 
				TIM4 			PB6  PB7  PB8   PB9
				TIM5			PA0  PA1  PA2   PA3
//返回值：0成功，1失败

*/
/***************************************************************************/

#endif
