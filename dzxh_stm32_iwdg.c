#include "dzxh_stm32_iwdg.h"

/*******使用方法***********************************************************/
/*

@例:	IWDG_Init(IWDG_Prescaler_256,4095);	// 26208ms	看门狗复位时间
@例:	IWDG_Feed();//喂独立看门狗

	
*/
/*************************************************************************/


//初始化独立看门狗
//IWDG_Prescaler:分频数:0~6(只有低3位有效!)
//分频因子=4*2^IWDG_Prescaler.但最大值只能是256!
//Reload:重装载寄存器值:低11位有效.
//时间计算(大概):Tout=((4*2^IWDG_Prescaler)*Reload)/40 (ms).

/*		IWDG_Prescaler(0 to 6)
  *   This parameter can be one of the following values:
  *     0 @arg IWDG_Prescaler_4: IWDG prescaler set to 4
  *     1 @arg IWDG_Prescaler_8: IWDG prescaler set to 8
  *     2 @arg IWDG_Prescaler_16: IWDG prescaler set to 16
  *     3 @arg IWDG_Prescaler_32: IWDG prescaler set to 32
  *     4 @arg IWDG_Prescaler_64: IWDG prescaler set to 64
  *     5 @arg IWDG_Prescaler_128: IWDG prescaler set to 128
  *     6 @arg IWDG_Prescaler_256: IWDG prescaler set to 256
*/
/*		Reload(0 to 4095)
  *   This parameter must be a number between 0 and 0x0FFF.
*/

/*
IWDG_Init(IWDG_Prescaler_64,625)	//1000ms看门狗复位时间

IWDG_Init(IWDG_Prescaler_4,4095);	// 409.5ms	看门狗复位时间
IWDG_Init(IWDG_Prescaler_8,4095);	// 819ms	看门狗复位时间
IWDG_Init(IWDG_Prescaler_16,4095);	// 1538ms	看门狗复位时间
IWDG_Init(IWDG_Prescaler_32,4095);	// 3276ms	看门狗复位时间
IWDG_Init(IWDG_Prescaler_64,4095);	// 6552ms	看门狗复位时间
IWDG_Init(IWDG_Prescaler_128,4095);	// 13104ms	看门狗复位时间
IWDG_Init(IWDG_Prescaler_256,4095);	// 26208ms	看门狗复位时间
*/
void IWDG_Init(uint8_t IWDG_Prescaler,uint16_t Reload) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	
	IWDG_SetPrescaler(IWDG_Prescaler);  //设置IWDG预分频值:设置IWDG预分频值为64
	
	IWDG_SetReload(Reload);  //设置IWDG重装载值
	
	IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
	
	IWDG_Enable();  //使能IWDG
}
//喂独立看门狗
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();//reload										   
}

/*
  * log:

  *	2018年4月6日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/
