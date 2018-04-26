#include "dzxh_stm32_nvic.h"

/*//取值范围:
  *   This parameter can be one of the following values:
  *     @arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
  *                                4 bits for subpriority
  *     @arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
  *                                3 bits for subpriority
  *     @arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
  *                                2 bits for subpriority
  *     @arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
  *                                1 bits for subpriority
  *     @arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
  *                                0 bits for subpriority
*/
//设置优先级分组：抢断优先级和相应优先级 (默认：4个抢断优先级，4个相应优先级)
void NVIC_Configuration(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}

/*
  * log:

  *	2018年4月6日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

