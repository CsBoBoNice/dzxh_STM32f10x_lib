#include "dzxh_stm32_systick.h"
/**********使用方法***************************************************************/
//
//	SysTick_delay_init();	//初始化SysTick定时器中断 每1/configTICK_RATE_HZ秒中断一次

//	SysTick_delay_ms(u16 nms);		//毫秒延时	取值范围	nms<=1864
//	SysTick_delay_us(u32 nus);		//微妙延时

//	SysTick_Handler(void)//SysTick定时器中断函数

//注意:SysTick延时与SysTick中断冲突，使用SysTick中断就不要使用SysTick延时与初始化SysTick延时
/*********************************************************************************/
/*************************************************************************/
static u8  fac_us=0;//us延时倍乘数
static u16 fac_ms=0;//ms延时倍乘数

//初始化延迟函数
//SYSTICK的时钟固定为AHB时钟，基础例程里面SYSTICK时钟频率为AHB/8
//这里为了兼容FreeRTOS，所以将SYSTICK的时钟频率改为AHB的频率！
//SYSCLK:系统时钟频率
void SysTick_delay_init()
{
	u32 reload;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);//选择外部时钟  HCLK
	fac_us=SystemCoreClock/1000000;				//不论是否使用OS,fac_us都需要使用
	reload=SystemCoreClock/1000000;				//每秒钟的计数次数 单位为M  
	reload*=1000000/configTICK_RATE_HZ;			//根据configTICK_RATE_HZ设定溢出时间
												//reload为24位寄存器,最大值:16777216,在72M下,约合0.233s左右	
	fac_ms=1000/configTICK_RATE_HZ;				//代表OS可以延时的最少单位	   

	SysTick->CTRL|=SysTick_CTRL_TICKINT_Msk;   	//开启SYSTICK中断
	SysTick->LOAD=reload; 						//每1/configTICK_RATE_HZ秒中断一次	
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;   	//开启SYSTICK  
//  NVIC_SetPriority (SysTick_IRQn, 1); //设置中断优先级	
}	

//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void SysTick_delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL=0x01 ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	  	    
} 


//延时nus
//nus为要延时的us数.		    								   
void SysTick_delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL=0x01 ;      //开始倒数 	 
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL=0x00;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}

/*
  * log:
  *	2018年4月15日

	为了为了兼容FreeRTOS，所以将SYSTICK的时钟频率改为AHB的频率
	将滴答延时函数与普通延时函数区别开
	Programmer:陈述

  *	2018年4月6日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

