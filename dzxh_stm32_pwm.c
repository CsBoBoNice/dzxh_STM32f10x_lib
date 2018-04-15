#include "dzxh_stm32_pwm.h"

/******使用方法******************************************************************/
/*
@例:	TIM_PWM_Init(1,72,20000,1100,1,0);	//PWM初始化
	
@例:	Change_PWM_period( TIM1,10000);		//改变PWM周期
	
@例:	Change_PWM_pulse(TIM1,2,600);		//改变PWM脉冲宽度
*/
/***************************************************************************/
/*
pwm初始化 （默认时钟分割为1，向上计数，TIM输出比较极性高，开使能）

TIM_PWM_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,u16 TIM_pulse,u16 TIM_channel,u8 remap_pwm);

//参数1：选用的定时器；(范围 1,2,3,4,)
						1  	TIM1
						2	TIM2
						3	TIM3
						4	TIM4
						5	TIM5
//参数2：时钟预分频值（不用减1）；默认时钟72MHZ			时钟分频是指：72M/时钟预分频值
//参数3：装入活动的自动重装载寄存器周期的值（设定周期）			参数3的值=72M/时钟预分频值*周期值(单位秒)
//参数4：待装入捕获比较寄存器的脉冲值（设定脉冲高电平时间）		参数4的值=72M/时钟预分频值*高电平时间(单位秒)
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

//返回值：0成功，1失败

*/
/***************************************************************************/


void TIM1_PWM_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		TIM_CtrlPWMOutputs(TIM1,ENABLE);	//解决PWM1无脉冲输出问题
		switch(TIM_channel)
		{
			case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
					GPIO_Init(GPIOA,&GPIO_InitStruct);break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
					GPIO_Init(GPIOA,&GPIO_InitStruct);break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
					GPIO_Init(GPIOA,&GPIO_InitStruct);break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
					GPIO_Init(GPIOA,&GPIO_InitStruct);break;	
		}
	}
	
	if(remap_pwm==1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM1, ENABLE); //TIM1 复用功能完全映射
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		TIM_CtrlPWMOutputs(TIM1,ENABLE);	//解决PWM1无脉冲输出问题
		switch(TIM_channel)
		{
			case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
					GPIO_Init(GPIOE,&GPIO_InitStruct);break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
					GPIO_Init(GPIOE,&GPIO_InitStruct);break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
					GPIO_Init(GPIOE,&GPIO_InitStruct);break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14;
					GPIO_Init(GPIOE,&GPIO_InitStruct);break;	
		}		
	}
}
void TIM2_PWM_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;	
		}
	}

	if(remap_pwm==1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); //TIM2 复用功能部分映射1
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//解决TIM2 复用功能部分映射1没有波形的问题
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;	
		}		
	}
	
	if(remap_pwm==2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE); //TIM2 复用功能部分映射2
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}		
	}

	if(remap_pwm==3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); //TIM2 复用功能完全映射
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//解决TIM2 复用功能部分映射3没有波形的问题
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}		
	}	
}
void TIM3_PWM_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;		
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;		
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}
	}

	if(remap_pwm==1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //TIM3 复用功能部分映射
		GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);//解决TIM3 复用功能部分映射1没有波形的问题
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;		
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}		
	}
	
	if(remap_pwm==2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //TIM3 复用功能完全映射
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;		
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
						GPIO_Init(GPIOC,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
						GPIO_Init(GPIOC,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
						GPIO_Init(GPIOC,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
						GPIO_Init(GPIOC,&GPIO_InitStruct);break;	
		}
	}
}
void TIM4_PWM_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;		
		switch(TIM_channel)
		{
			case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
					GPIO_Init(GPIOB,&GPIO_InitStruct);break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
					GPIO_Init(GPIOB,&GPIO_InitStruct);break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
					GPIO_Init(GPIOB,&GPIO_InitStruct);break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
					GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}		
	}

	if(remap_pwm==1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); //TIM4 复用功能映射
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;		
		switch(TIM_channel)
		{
			case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
					GPIO_Init(GPIOD,&GPIO_InitStruct);break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
					GPIO_Init(GPIOD,&GPIO_InitStruct);break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14;
					GPIO_Init(GPIOD,&GPIO_InitStruct);break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
					GPIO_Init(GPIOD,&GPIO_InitStruct);break;	
		}		
	}
}
void TIM5_PWM_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		//使能TIM5
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;		//复用推挽输出	
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		
		switch(TIM_channel)
		{
			case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
					GPIO_Init(GPIOA,&GPIO_InitStruct);break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
					GPIO_Init(GPIOA,&GPIO_InitStruct);break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
					GPIO_Init(GPIOA,&GPIO_InitStruct);break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
					GPIO_Init(GPIOA,&GPIO_InitStruct);break;	
		}
	}

}
void TIM_OCInit(TIM_TypeDef* TIMx,u16 TIM_channel,TIM_OCInitTypeDef* TIM_OCInitStruct)
{
	switch(TIM_channel)
	{
		case 1:TIM_OC1Init(TIMx,TIM_OCInitStruct);break;
		case 2:TIM_OC2Init(TIMx,TIM_OCInitStruct);break;
		case 3:TIM_OC3Init(TIMx,TIM_OCInitStruct);break;
		case 4:TIM_OC4Init(TIMx,TIM_OCInitStruct);break;
	}
}
void TIM_PWM_Gpio_init(u8 TIMx,u16 TIM_channel,u8 remap_pwm)
{
	switch(TIMx)
	{
		case 1:TIM1_PWM_GPIO_Init(TIM_channel,remap_pwm);break;
		case 2:TIM2_PWM_GPIO_Init(TIM_channel,remap_pwm);break;
		case 3:TIM3_PWM_GPIO_Init(TIM_channel,remap_pwm);break;
		case 4:TIM4_PWM_GPIO_Init(TIM_channel,remap_pwm);break;
		case 5:TIM5_PWM_GPIO_Init(TIM_channel,remap_pwm);break;		
	}
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


//pwm初始化 （默认时钟分割为1，向上计数，TIM输出比较极性高，开使能）
//参数1：选用的定时器；(范围 1,2,3,4,5)
//参数2：时钟预分频值（不用减1）；
//参数3：装入活动的自动重装载寄存器周期的值（设定周期）
//参数4：待装入捕获比较寄存器的脉冲值（设定脉冲高电平时间）
//参数5：定时器通道(范围 1,2,3,4,)
//参数6：引脚重映射	
//返回值：0成功，1失败
//定时器引脚：

u8 TIM_PWM_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,u16 TIM_pulse,u16 TIM_channel,u8 remap_pwm)
{
	TIM_TypeDef* TIM;
	TIM_TimeBaseInitTypeDef tim_TimeBaseInitTypeDef;
	TIM_OCInitTypeDef Tim_OCInitTypeDef;
	TIM=get_tim_num(TIMx);
	TIM_PWM_Gpio_init(TIMx,TIM_channel,remap_pwm);
	if(0!=TIM)
	{
		tim_TimeBaseInitTypeDef.TIM_ClockDivision=TIM_CKD_DIV1;
		tim_TimeBaseInitTypeDef.TIM_CounterMode=TIM_CounterMode_Up;
		tim_TimeBaseInitTypeDef.TIM_Period=TIM_period-1;
		tim_TimeBaseInitTypeDef.TIM_Prescaler=TIM_prescaler-1;
		TIM_TimeBaseInit(TIM,&tim_TimeBaseInitTypeDef);
		
		Tim_OCInitTypeDef.TIM_OCMode=TIM_OCMode_PWM1;
		Tim_OCInitTypeDef.TIM_Pulse=TIM_pulse;
		Tim_OCInitTypeDef.TIM_OCPolarity = TIM_OCPolarity_High;
		Tim_OCInitTypeDef.TIM_OutputState=TIM_OutputState_Enable;
		TIM_OCInit(TIM,TIM_channel,&Tim_OCInitTypeDef);
		
		TIM_ARRPreloadConfig(TIM,ENABLE);
		TIM_Cmd(TIM,ENABLE);
		return 0;
	}
	return 1;
}

//功能：改变PWM周期
//参数1：选用的定时器；(范围 TIM1,TIM2,TIM3,TIM4,)
//参数2：设定周期
void Change_PWM_period(TIM_TypeDef* TIM,u16 TIM_period)
{
	TIM->ARR=TIM_period-1;
}

//功能：改变PWM脉冲宽度
//参数1：选用的定时器；(范围 TIM1,TIM2,TIM3,TIM4,)
//参数2：设定通道； (范围 1,2,3,4)
//参数3：设定脉冲宽度(高电平时间)
void Change_PWM_pulse(TIM_TypeDef* TIM,u8 TIM_channel,u16 pulse)

{
    switch(TIM_channel)
    {
        case 1:TIM->CCR1 = pulse-1;break;
        case 2:TIM->CCR2 = pulse-1;break;
        case 3:TIM->CCR3 = pulse-1;break;
        case 4:TIM->CCR4 = pulse-1;break;
    }
}
/*
  * log:

  *	2016年7月6日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/
