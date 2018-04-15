#include "dzxh_stm32_delay.h"

/**********使用方法***************************************************************/
/*
	delay_us(1024);	//延时1024us
	delay_ms(1024);	//延时1024ms

注:
当延时时间不准确在delay_us函数中增加或减少__NOP();
*/

/*********************************************************************************/

//普通延时函数
void delay_us(u32 nTimer)  
{  
	u32 i=0;  
	for(i=0;i<nTimer;i++){  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();  
		__NOP();__NOP();__NOP();__NOP();__NOP();
//		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();
//		__NOP();  
	}  
}  
//普通延时函数
void delay_ms(u32 nTimer)  
{  
    u32 i=1000*nTimer;  
    delay_us(i);  
} 

/*
  * log:

  *	2018年4月15日
	修改函数名字
	本文件只放普通延时函数
	Programmer:陈述

  *	2018年4月6日
	修改函数名字
	区分了普通延时与滴答延时
	Programmer:陈述

  *	2016年7月6日
	新建工程
	实现基本初始化功能
	实现基本发送与接收功能
	Programmer:陈述
	
*/


