#include "dzxh_stm32_gpio.h"

/*******使用方法***********************************************************/
/*

@例:	GPIO_Common_Init(GPIOA,GPIO_Pin_2|GPIO_Pin_3,GPIO_Mode_Out_PP);	//GPIO初始化
		初始化GPIOA	;PA2，PA3;推挽输出
	
*/
/*************************************************************************/
/*
@例:	GPIO_ResetBits(GPIOD,GPIO_Pin_2);	//引脚拉低

@例:	GPIO_SetBits(GPIOD,GPIO_Pin_2);		//引脚置高

@例:	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)//读取指定端口管脚的输入	

@例:	GPIO_ReadInputData(GPIOD)	//读取指定的 GPIO 端口输入

@例:	GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_2)//读取指定端口管脚的输出

@例:	GPIO_Write(GPIOD, 0x55)//向指定 GPIO 数据端口写入数据
*/
/*************************************************************************/
/*
（默认速度50M，推挽输出）
//参数1：GPIO编号（范围：1,2,3,4,5,6,7）
										1 代表 GPIOA
										2 代表 GPIOB
										3 代表 GPIOC
										4 代表 GPIOD
										5 代表 GPIOE
										6 代表 GPIOF
										7 代表 GPIOG
//参数2：对应引脚	
					GPIO_Pin_0
					GPIO_Pin_1
					GPIO_Pin_2
					GPIO_Pin_3
					GPIO_Pin_4
					GPIO_Pin_5
					GPIO_Pin_6
					GPIO_Pin_7
					GPIO_Pin_8
					GPIO_Pin_9
					GPIO_Pin_10
					GPIO_Pin_11
					GPIO_Pin_12
					GPIO_Pin_13
					GPIO_Pin_14
					GPIO_Pin_15
					GPIO_Pin_ALL

//参数3：对应模式	 GPIO_Mode				描述			例子
					GPIO_Mode_AIN 			模拟输入		ADC引脚
					GPIO_Mode_IN_FLOATING 	浮空输入		按键
					GPIO_Mode_IPD 			下拉输入
					GPIO_Mode_IPU 			上拉输入		输入捕获
					GPIO_Mode_Out_OD 		开漏输出
					GPIO_Mode_Out_PP 		推挽输出		驱动小灯
					GPIO_Mode_AF_OD 		复用开漏输出
					GPIO_Mode_AF_PP 		复用推挽输出	PWM

*/
/********************************************************************/

/*
─ PA15： JTDI置于上拉模式
─ PA14： JTCK置于下拉模式
─ PA13： JTMS置于上拉模式
─ PB4： JNTRST置于上拉模式

JTMS/SWDIO 		输入 JTAG模式选择 输入/输出 串行数据输入/输出 		PA13
JTCK/SWCLK 		输入 JTAG时钟 		输入 	串行时钟 				PA14
JTDI 			输入 JTAG数据输入  ——  	——					PA15
JTDO/TRACESWO 	输出 JTAG数据输出  —— 	跟踪时为TRACESWO信号 	PB3
JNTRST 			输入 JTAG模块复位  ——  	——					PB4
若使用以上引脚：
//关闭jtag 改变指定管脚的映射	JTAG-DP 失能 + SW-DP 使能
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	
*/

void RCC_APB2PeriphClockCmd_init(u8 GPIOx)
{
	switch(GPIOx)
	{
		case 1:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);return;
		case 2:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);return;
		case 3:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);return;
		case 4:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);return;
		case 5:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);return;
		case 6:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);return;
		case 7:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);return;
	}
	return;
}

void init_gpio_struct(GPIO_InitTypeDef *GPIO_InitStructure,u16 gpio_pin,GPIOSpeed_TypeDef Speed,GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitStructure->GPIO_Pin = gpio_pin; 
	GPIO_InitStructure->GPIO_Speed =Speed; 
	GPIO_InitStructure->GPIO_Mode = GPIO_Mode ; 
}

////GPIO初始化 （默认速度50M，推挽输出）
////参数1：GPIO编号（范围：1,2,3,4,5,6,7）
////参数2：对应引脚
u8 get_GPIO_num(GPIO_TypeDef* GPIOx)
{
	if(GPIOx==GPIOA){return 1;}
	else if(GPIOx==GPIOB){return 2;}
	else if(GPIOx==GPIOC){return 3;}
	else if(GPIOx==GPIOD){return 4;}
	else if(GPIOx==GPIOE){return 5;}
	else if(GPIOx==GPIOF){return 6;}
	else if(GPIOx==GPIOG){return 7;}
	return 0;
}

//GPIO初始化 （默认速度50M，推挽输出）
//参数1：GPIO编号（范围：1,2,3,4,5,6,7）
//参数2：对应引脚
void GPIO_Common_Init(GPIO_TypeDef* GPIOx,u16 gpio_pin,GPIOMode_TypeDef GPIO_Mode)
{
	u8 GPIO_num;
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_num=get_GPIO_num(GPIOx);
	RCC_APB2PeriphClockCmd_init(GPIO_num);
	init_gpio_struct(&GPIO_InitStructure,gpio_pin,GPIO_Speed_50MHz,(GPIOMode_TypeDef)GPIO_Mode);
	GPIO_Init(GPIOx, &GPIO_InitStructure); 
}


/*
  * log:

  *	2018年4月6日
	修改初始化参数类型
	Programmer:陈述

  *	2016年7月8日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/
