#include "dzxh_stm32_pwm_dac.h"
#include "dzxh_stm32_pwm.h"

#define TIM_DAC_period 155	//定时器计数值

/********PWM模拟DAC*************************************************************************************************/
/*

@例:	PWM_DAC_Set(TIM1,1,230);
		参数1：选用的定时器；TIM1，TIM2，TIM3，TIM4，TIM5

		参数2：定时器通道(范围 1,2,3,4,)
		
		参数3：//设置输出电压	取值范围(0~330,代表0~3.3V)
		
@例:	PWM_DAC_Init(1,1,0);		//初始化

		参数1：选用的定时器；(范围 1,2,3,4,)
						1  	TIM1
						2	TIM2
						3	TIM3
						4	TIM4
						5	TIM5
						
		参数2：定时器通道(范围 1,2,3,4,)
		
		参数3：引脚重映射	(范围 参考下表)
		
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
*/
/****************************************************************************************************************/

//设置输出电压
//vol:0~330,代表0~3.3V
void PWM_DAC_Set(TIM_TypeDef* TIMx,u16 TIM_channel,u16 vol)
{
	float temp=vol+6;	//加六是为了数值更准确
	temp/=100;
	temp=temp*TIM_DAC_period/3.3;
	switch(TIM_channel)
	{
		case 1:	TIM_SetCompare1(TIMx,temp);break;
		case 2:	TIM_SetCompare2(TIMx,temp);break;
		case 3:	TIM_SetCompare3(TIMx,temp);break;
		case 4:	TIM_SetCompare4(TIMx,temp);break;
	}	
//	TIM_SetCompare1(TIMx,temp);
}

static TIM_TypeDef* get_tim_num(u8 TIMx)
{
	switch(TIMx)
	{
		case 1:return TIM1;
		case 2:return TIM2;
		case 3:return TIM3;
		case 4:return TIM4;
		case 5:return TIM5;		
	}
	return 0;
}

void PWM_DAC_Init(u8 TIMx,u16 TIM_channel,u8 remap_pwm)
{
	TIM_TypeDef* TIM;
	TIM=get_tim_num(TIMx);
	TIM_PWM_Init(TIMx,0,TIM_DAC_period,100,TIM_channel,remap_pwm);	//PWM初始化
	switch(TIM_channel)
	{
		case 1:	TIM_SetCompare1(TIM,100);break;//初始值为0
		case 2:	TIM_SetCompare2(TIM,100);break;//初始值为0
		case 3:	TIM_SetCompare3(TIM,100);break;//初始值为0
		case 4:	TIM_SetCompare4(TIM,100);break;//初始值为0
	}
}

/*
  * log:

  *	2016年7月7日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/
