#include "dzxh_stm32_exti.h"

/*******使用方法***********************************************************/
/*

@例:	EXTIX_Init(3,4,EXTI_Trigger_Falling,0,0);

*/
/*******说明******************************************************************/
/*	
说明：	初始化结束后编写对应中断函数，中断函数在本页
		中断线0-4每个中断线对应一个中断函数，
		中断线5-9共用中断函数EXTI9_5_IRQHandler，
		中断线10-15共用中断函数EXTI15_10_IRQHandler。	
*/
/*******说明******************************************************************/
/*
(默认：4个抢断优先级，4个相应优先级)
(默认：EXTI_Mode_Interrupt中断模式，可换为EXTI_Mode_Event事件请求)
//参数1：GPIO编号（范围：1,2,3,4,5）
										1 代表 GPIOA
										2 代表 GPIOB
										3 代表 GPIOC
										4 代表 GPIOD
										5 代表 GPIOE
										6 代表 GPIOF
										7 代表 GPIOG
										
//参数2：对应引脚	(范围: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)	
					
//参数3：对应模式	 

						EXTI_Trigger 					描述
					EXTI_Trigger_Falling 			设置输入线路下降沿为中断请求
					EXTI_Trigger_Rising 			设置输入线路上升沿为中断请求
					EXTI_Trigger_Rising_Falling 	设置输入线路上升沿和下降沿为中断请求

//参数4：对应抢断优先级级别		取值范围(0,1,2,3)	数值越低优先级越高

//参数5：对应响应优先级级别		取值范围(0,1,2,3)	数值越低优先级越高

*/
/*****************************************************************************/

//抢断优先级高的能将抢断优先级低的打断
//两个中断同时到达，内核就会首先响应响应优先级高的

/***中断函数**********************************************************************/

void EXTI0_IRQHandler(void)
{
	/* 清除中断挂起标志位，否则会被认为中断没有被处理而循环再次进入中断 */
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line2);
	
}

void EXTI3_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line3);
	
}

void EXTI4_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line4);

}

void EXTI9_5_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line5);
 	EXTI_ClearITPendingBit(EXTI_Line6);
 	EXTI_ClearITPendingBit(EXTI_Line7);
 	EXTI_ClearITPendingBit(EXTI_Line8);
 	EXTI_ClearITPendingBit(EXTI_Line9);
	
}

void EXTI15_10_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line10);
 	EXTI_ClearITPendingBit(EXTI_Line11);
 	EXTI_ClearITPendingBit(EXTI_Line12);
 	EXTI_ClearITPendingBit(EXTI_Line13);
 	EXTI_ClearITPendingBit(EXTI_Line14);
 	EXTI_ClearITPendingBit(EXTI_Line15);

}

/*****************************************************************************/
/*
	中断初始化函数
*/
void EXTIX_Init(u8 GPIOx,u8 GPIO_PIN,EXTITrigger_TypeDef  EXTI_Mode,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	uint8_t	PinSource;
	GPIO_TypeDef* GPIO_P;
	EXTITrigger_TypeDef EXTI_Mode_P;
	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//4个抢断优先级，4个相应优先级

	/* 开启AFIO的时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	EXTI_Mode_P=EXTI_Mode;
	switch(GPIOx)
	{
		case 1:	GPIO_P=GPIOA;break;
		case 2:	GPIO_P=GPIOB;break;
		case 3:	GPIO_P=GPIOC;break;
		case 4:	GPIO_P=GPIOD;break;
		case 5:	GPIO_P=GPIOE;break;
		case 6:	GPIO_P=GPIOF;break;
		case 7:	GPIO_P=GPIOG;break;	
	}
	
	if(EXTI_Mode_P==EXTI_Trigger_Falling)
	{
		switch(GPIO_PIN)
		{
			case 0:	GPIO_SetBits(GPIO_P,GPIO_Pin_0);break;		//引脚置高
			case 1:	GPIO_SetBits(GPIO_P,GPIO_Pin_1);break;		//引脚置高
			case 2:	GPIO_SetBits(GPIO_P,GPIO_Pin_2);break;		//引脚置高
			case 3:	GPIO_SetBits(GPIO_P,GPIO_Pin_3);break;		//引脚置高
			case 4:	GPIO_SetBits(GPIO_P,GPIO_Pin_4);break;		//引脚置高
			case 5:	GPIO_SetBits(GPIO_P,GPIO_Pin_5);break;		//引脚置高
			case 6:	GPIO_SetBits(GPIO_P,GPIO_Pin_6);break;		//引脚置高
			case 7:	GPIO_SetBits(GPIO_P,GPIO_Pin_7);break;		//引脚置高
			case 8:	GPIO_SetBits(GPIO_P,GPIO_Pin_8);break;		//引脚置高
			case 9:	GPIO_SetBits(GPIO_P,GPIO_Pin_9);break;		//引脚置高
			case 10:	GPIO_SetBits(GPIO_P,GPIO_Pin_10);break;		//引脚置高
			case 11:	GPIO_SetBits(GPIO_P,GPIO_Pin_11);break;		//引脚置高
			case 12:	GPIO_SetBits(GPIO_P,GPIO_Pin_12);break;		//引脚置高
			case 13:	GPIO_SetBits(GPIO_P,GPIO_Pin_13);break;		//引脚置高
			case 14:	GPIO_SetBits(GPIO_P,GPIO_Pin_14);break;		//引脚置高
			case 15:	GPIO_SetBits(GPIO_P,GPIO_Pin_15);break;		//引脚置高
		}		
	}
	
	if(EXTI_Mode_P==EXTI_Trigger_Rising)
	{
		switch(GPIO_PIN)
		{
			case 0: GPIO_ResetBits(GPIO_P,GPIO_Pin_0);break;	//引脚拉低
			case 1: GPIO_ResetBits(GPIO_P,GPIO_Pin_1);break;	//引脚拉低
			case 2: GPIO_ResetBits(GPIO_P,GPIO_Pin_2);break;	//引脚拉低
			case 3: GPIO_ResetBits(GPIO_P,GPIO_Pin_3);break;	//引脚拉低
			case 4: GPIO_ResetBits(GPIO_P,GPIO_Pin_4);break;	//引脚拉低
			case 5: GPIO_ResetBits(GPIO_P,GPIO_Pin_5);break;	//引脚拉低
			case 6: GPIO_ResetBits(GPIO_P,GPIO_Pin_6);break;	//引脚拉低
			case 7: GPIO_ResetBits(GPIO_P,GPIO_Pin_7);break;	//引脚拉低
			case 8: GPIO_ResetBits(GPIO_P,GPIO_Pin_8);break;	//引脚拉低
			case 9: GPIO_ResetBits(GPIO_P,GPIO_Pin_9);break;	//引脚拉低
			case 10: GPIO_ResetBits(GPIO_P,GPIO_Pin_10);break;	//引脚拉低
			case 11: GPIO_ResetBits(GPIO_P,GPIO_Pin_11);break;	//引脚拉低
			case 12: GPIO_ResetBits(GPIO_P,GPIO_Pin_12);break;	//引脚拉低
			case 13: GPIO_ResetBits(GPIO_P,GPIO_Pin_13);break;	//引脚拉低
			case 14: GPIO_ResetBits(GPIO_P,GPIO_Pin_14);break;	//引脚拉低
			case 15: GPIO_ResetBits(GPIO_P,GPIO_Pin_15);break;	//引脚拉低

		}
	}
	
	switch(GPIO_PIN)
	{
		case 0:	    EXTI_InitStructure.EXTI_Line = EXTI_Line0;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource0;
					break;
		case 1:	    EXTI_InitStructure.EXTI_Line = EXTI_Line1;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource1;
					break;
		case 2:	    EXTI_InitStructure.EXTI_Line = EXTI_Line2;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource2;
					break;
		case 3:	    EXTI_InitStructure.EXTI_Line = EXTI_Line3;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource3;
					break;
		case 4:	    EXTI_InitStructure.EXTI_Line = EXTI_Line4;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource4;
					break;
		case 5:	    EXTI_InitStructure.EXTI_Line = EXTI_Line5;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource5;
					break;		
		case 6:	    EXTI_InitStructure.EXTI_Line = EXTI_Line6;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource6;
					break;		
		case 7:	    EXTI_InitStructure.EXTI_Line = EXTI_Line7;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource7;
					break;		
		case 8:	    EXTI_InitStructure.EXTI_Line = EXTI_Line8;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource8;
					break;		
		case 9:	    EXTI_InitStructure.EXTI_Line = EXTI_Line9;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource9;
					break;		
		case 10:	EXTI_InitStructure.EXTI_Line = EXTI_Line10;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource10;
					break;		
		case 11:	EXTI_InitStructure.EXTI_Line = EXTI_Line11;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource11;
					break;		
		case 12:	EXTI_InitStructure.EXTI_Line = EXTI_Line12;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource12;
					break;		
		case 13:	EXTI_InitStructure.EXTI_Line = EXTI_Line13;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource13;
					break;		
		case 14:	EXTI_InitStructure.EXTI_Line = EXTI_Line14;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource14;
					break;		
		case 15:	EXTI_InitStructure.EXTI_Line = EXTI_Line15;			   //中断线
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//使能外部中断通道
					PinSource=GPIO_PinSource15;
					break;		
	}
	
		switch(GPIOx)
	{
		case 1:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, PinSource);break;
		case 2:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, PinSource);break;
		case 3:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, PinSource);break;
		case 4:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, PinSource);break;
		case 5:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, PinSource);break;
		case 6:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, PinSource);break;
		case 7:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, PinSource);break;
		
	}
	
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		 //中断模式
    EXTI_InitStructure.EXTI_Trigger = EXTI_Mode;  			//触发模式
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;   //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		  //响应优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //使能外部中断通道
    NVIC_Init(&NVIC_InitStructure);				 //根据NVIC_InitStructure中指定的参数初始化外设NVIC	
}
/*
  * log:

  *	2016年7月6日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

