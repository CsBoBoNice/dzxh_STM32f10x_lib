#include "dzxh_stm32_tim.h"
#include "include.h"
/*******使用方法**************************************************************/
/*
@例:	TIM_Common_Init(5,7200,10000,TIM_CounterMode_Up,0,1);	//定时器初始化
	
	//定时器5，预分频7200,1秒进入一次中断，向上计数模式，抢断优先级级别0，响应优先级级别1
	
@例:	Tim_Cmd(5,1);	//使能定时器5
	
	//功能：使能或失能定时器
	//参数1：定时器的编号(范围 2~7)
	//参数2: 0关闭(TIM_DISABLE)，1开启(TIM_ENABLE)
*/
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

//抢断优先级高的能将抢断优先级低的打断
//两个中断同时到达，内核就会首先响应响应优先级高的

/***中断函数**********************************************************************/


void TIM2_IRQHandler(void)
{ 
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); /* 清除溢出中断标志 */
		#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
		USART_ReceiveOvertimeProcess();
		#endif
    }
	
}
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); /* 清除溢出中断标志 */
    }	
}
void TIM4_IRQHandler(void)
{

}
void TIM5_IRQHandler(void)
{
	
}
void TIM6_IRQHander(void)
{

}
void TIM7_IRQHander(void)
{
    TIM_ClearITPendingBit(TIM7,TIM_IT_Update);/* 清除溢出中断标志 */
}

/********************************************************************************/

TIM_TypeDef* get_tim(u8 TIMx)
{
	switch(TIMx)
	{
		case 2:return TIM2;
		case 3:return TIM3;
		case 4:return TIM4;
        case 5:return TIM5;
		case 6:return TIM6;
		case 7:return TIM7;
	}
	return 0;
}

#ifdef STM32F10X_MD
void time_nvic_init(u8 TIMx,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	 
	NVIC_InitTypeDef NVIC_InitStructure; 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);break;        
    }
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
#endif /* STM32F10X_MD */

#ifdef STM32F10X_HD
void time_nvic_init(u8 TIMx,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	 
	NVIC_InitTypeDef NVIC_InitStructure; 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);break;
        case 5:NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);break;
        case 6:NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);break;
        case 7:NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);break;        
    }
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
#endif /* STM32F10X_HD */ 

#ifdef STM32F10X_CL	
void time_nvic_init(u8 TIMx,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	 
	NVIC_InitTypeDef NVIC_InitStructure; 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);break;
        case 5:NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);break;
        case 6:NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);break;
        case 7:NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);break;        
    }
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
#endif /* STM32F10X_CL */ 

u8 TIM_Common_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority)
//pwm初始化 （默认时钟分割为1，向上计数，TIM输出比较极性高，使能关）
//参数1：选用的定时器；(范围 2~7)
//参数2：时钟预分频值（不用减1）；
//参数3：装入活动的自动重装载寄存器周期的值（设定周期）
//返回值：0成功，1失败
{
	TIM_TypeDef* TIM;
	TIM_TimeBaseInitTypeDef tim_TimeBaseInitTypeDef;
	TIM=get_tim(TIMx);
	if(0!=TIM)
	{
        time_nvic_init(TIMx,PreemptionPriority,SubPriority);
		tim_TimeBaseInitTypeDef.TIM_ClockDivision=TIM_CKD_DIV1;/* 采样分频 */
		tim_TimeBaseInitTypeDef.TIM_CounterMode=TIM_CounterMode;/* 计数模式 */
		tim_TimeBaseInitTypeDef.TIM_Period=TIM_period-1; /* 自动重装载寄存器周期的值(计数值) */ 
		tim_TimeBaseInitTypeDef.TIM_Prescaler=TIM_prescaler-1;/* 预分频系数*/
		
		TIM_ARRPreloadConfig(TIM,ENABLE);/*使能 TIMx 在 ARR 上的预装载寄存器*/
		
		/***以下几行代码顺序不可更改，解决了初始化定时器后马上进入一次定时器的问题***/	    
        TIM_TimeBaseInit(TIM,&tim_TimeBaseInitTypeDef);/* 初始化定时器 */
		TIM_ClearITPendingBit(TIM, TIM_IT_Update);/* 清除溢出中断标志 */
        TIM_ITConfig(TIM,TIM_IT_Update,ENABLE);/* 溢出中断使能 */
		TIM_Cmd(TIM,DISABLE);/* 计数器不使能 */

		return 0;
	}
	return 1;
}
void Tim_Cmd(u8 TIMx,u8 flag)
{
    TIM_TypeDef* TIM;
	TIM=get_tim(TIMx);
    if(flag)
    {
        TIM_Cmd(TIM,ENABLE);/* 计数器使能 */
    }
    else
    {
        TIM_Cmd(TIM,DISABLE);/* 计数器不使能 */
    }
}
/*
  * log:

  *	2018年4月6日
	修复了初始化定时器后马上进入一次定时器的问题
	删除了中断优先级初始化，在dzxh_stm32_nvic.c中统一初始化
	Programmer:陈述

  *	2016年7月7日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

