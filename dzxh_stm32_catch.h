#ifndef  _DZXH_STM32_CATCH_H_
#define  _DZXH_STM32_CATCH_H_

#include "stm32f10x.h"

void TIM_Catch_Init(u8 TIMx,u16 TIM_channel,u8 remap_pwm,uint8_t PreemptionPriority,uint8_t SubPriority);//初始化输入捕获
uint32_t Get_catch(u8 TIM,u16 TIM_channel);//函数返回值为捕获低电平时间
#endif
