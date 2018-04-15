#include "dzxh_stm32_catch.h"
//#define TIM2_IRQHandler_ENABLE
//#define TIM3_IRQHandler_ENABLE
//#define TIM4_IRQHandler_ENABLE
//#define TIM5_IRQHandler_ENABLE

/******使用方法******************************************************************/
/*
(默认：捕获低电平时间)

(注意：使用前将对应的中断打开，只需将上面对应的中断使能(#define TIM2_IRQHandler_ENABLE)//注释去掉即可)

@例:	Get_catch(5,1);	//函数返回值为捕获低电平时间
		参数1：选用定时器 取值范围（2,3,4,5）
									2	TIM2
									3	TIM3
									4	TIM4
									5	TIM5
		参数2：定时器通道(范围 1,2,3,4,)


@例:	TIM_Catch_Init(5,1,0,0,3);	//初始化输入捕获
		参数1：选用定时器 取值范围（2,3,4,5）
									2	TIM2
									3	TIM3
									4	TIM4
									5	TIM5
		参数2：定时器通道(范围 1,2,3,4,)
		参数3：是否重映射
		参数4：对应抢断优先级级别		取值范围(0,1,2,3)	数值越低优先级越高
		参数5：对应响应优先级级别		取值范围(0,1,2,3)	数值越低优先级越高

定时器	引脚重映像		通道	1	  2	   3	4

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
/********************************************************************************/

uint8_t  TIM2CH1_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM2CH1_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM2CH2_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM2CH2_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM2CH3_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM2CH3_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM2CH4_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM2CH4_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM3CH1_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM3CH1_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM3CH2_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM3CH2_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM3CH3_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM3CH3_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM3CH4_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM3CH4_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM4CH1_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM4CH1_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM4CH2_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM4CH2_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM4CH3_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM4CH3_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM4CH4_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM4CH4_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM5CH1_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM5CH1_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM5CH2_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM5CH2_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM5CH3_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM5CH3_CAPTURE_VAL;	//输入捕获值

uint8_t  TIM5CH4_CAPTURE_STA=0;	//输入捕获状态		    				
uint16_t	TIM5CH4_CAPTURE_VAL;	//输入捕获值

uint32_t Get_catch(u8 TIM,u16 TIM_channel)
{
	uint32_t temp=0;
	if(TIM==2)
	{
		switch(TIM_channel)
		{
			case 1:	if(TIM2CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM2CH1_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM2CH1_CAPTURE_VAL;//得到总的低电平时间
						TIM2CH1_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 2:	if(TIM2CH2_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM2CH2_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM2CH2_CAPTURE_VAL;//得到总的低电平时间
						TIM2CH2_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 3:	if(TIM2CH3_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM2CH3_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM2CH4_CAPTURE_VAL;//得到总的低电平时间
						TIM2CH4_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 4:	if(TIM2CH4_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM2CH4_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM2CH4_CAPTURE_VAL;//得到总的低电平时间
						TIM2CH4_CAPTURE_STA=0;//开启下一次捕获
					}break;
		}
	}

	if(TIM==3)
	{
		switch(TIM_channel)
		{
			case 1:	if(TIM3CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM3CH1_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM3CH1_CAPTURE_VAL;//得到总的低电平时间
						TIM3CH1_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 2:	if(TIM3CH2_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM3CH2_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM3CH2_CAPTURE_VAL;//得到总的低电平时间
						TIM3CH2_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 3:	if(TIM3CH3_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM3CH3_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM3CH4_CAPTURE_VAL;//得到总的低电平时间
						TIM3CH4_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 4:	if(TIM3CH4_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM3CH4_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM3CH4_CAPTURE_VAL;//得到总的低电平时间
						TIM3CH4_CAPTURE_STA=0;//开启下一次捕获
					}break;
		}
	}

	if(TIM==4)
	{
		switch(TIM_channel)
		{
			case 1:	if(TIM4CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM4CH1_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM4CH1_CAPTURE_VAL;//得到总的低电平时间
						TIM4CH1_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 2:	if(TIM4CH2_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM4CH2_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM4CH2_CAPTURE_VAL;//得到总的低电平时间
						TIM4CH2_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 3:	if(TIM4CH3_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM4CH3_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM4CH4_CAPTURE_VAL;//得到总的低电平时间
						TIM4CH4_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 4:	if(TIM4CH4_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM4CH4_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM4CH4_CAPTURE_VAL;//得到总的低电平时间
						TIM4CH4_CAPTURE_STA=0;//开启下一次捕获
					}break;
		}
	}

	if(TIM==5)
	{
		switch(TIM_channel)
		{
			case 1:	if(TIM5CH1_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM5CH1_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM5CH1_CAPTURE_VAL;//得到总的低电平时间
						TIM5CH1_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 2:	if(TIM5CH2_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM5CH2_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM5CH2_CAPTURE_VAL;//得到总的低电平时间
						TIM5CH2_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 3:	if(TIM5CH3_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM5CH3_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM5CH3_CAPTURE_VAL;//得到总的低电平时间
						TIM5CH3_CAPTURE_STA=0;//开启下一次捕获
					}break;
			case 4:	if(TIM5CH4_CAPTURE_STA&0X80)//成功捕获到了一次上升沿
					{
						temp=TIM5CH4_CAPTURE_STA&0X3F;
						temp*=65536;//溢出时间总和
						temp+=TIM5CH4_CAPTURE_VAL;//得到总的低电平时间
						TIM5CH4_CAPTURE_STA=0;//开启下一次捕获
					}break;
		}
	}
	return temp;
}


#ifdef TIM2_IRQHandler_ENABLE
void TIM2_IRQHandler(void)
{
	if((TIM2CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM2CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//捕获1发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);//获得 TIMx 输入捕获 1 的值
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling); //CC1P=0 设置为下降沿捕获
																	//设置 TIMx 通道 1 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH1_CAPTURE_STA=0;			//清空
				TIM2CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//设置 TIMx 计数器寄存器值
				TIM2CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising);		//CC1P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM2CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM2CH2_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM2CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH2_CAPTURE_VAL=0XFFFF;
				}else TIM2CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//捕获2发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM2CH2_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM2CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM2CH2_CAPTURE_VAL=TIM_GetCapture2(TIM2);//获得 TIMx 输入捕获 2 的值
		   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling); //CC2P=0 设置为下降沿捕获
																	//设置 TIMx 通道 2 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH2_CAPTURE_STA=0;			//清空
				TIM2CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//设置 TIMx 计数器寄存器值
				TIM2CH2_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising);		//CC2P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM2CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM2CH3_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM2CH3_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM2CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH3_CAPTURE_VAL=0XFFFF;
				}else TIM2CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)//捕获3发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM2CH3_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM2CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM2CH3_CAPTURE_VAL=TIM_GetCapture3(TIM2);//获得 TIMx 输入捕获 3 的值
		   		TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling); //CC3P=0 设置为下降沿捕获
																	//设置 TIMx 通道 3 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH3_CAPTURE_STA=0;			//清空
				TIM2CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//设置 TIMx 计数器寄存器值
				TIM2CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising);		//CC3P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM2CH4_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM2CH4_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM2CH4_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM2CH4_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM2CH4_CAPTURE_VAL=0XFFFF;
				}else TIM2CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)//捕获4发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM2CH4_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM2CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM2CH4_CAPTURE_VAL=TIM_GetCapture4(TIM2);//获得 TIMx 输入捕获 4 的值
		   		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Falling); //CC4P=0 设置为下降沿捕获
																	//设置 TIMx 通道 4 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM2CH4_CAPTURE_STA=0;			//清空
				TIM2CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//设置 TIMx 计数器寄存器值
				TIM2CH4_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Rising);		//CC4P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //清除中断标志位
}
#endif /* TIM2_IRQHandler_ENABLE */

#ifdef TIM3_IRQHandler_ENABLE
void TIM3_IRQHandler(void)
{
	if((TIM3CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM3CH1_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM3CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM3CH1_CAPTURE_VAL=0XFFFF;
				}else TIM3CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//捕获1发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM3CH1_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM3CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);//获得 TIMx 输入捕获 1 的值
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC1P=0 设置为下降沿捕获
																	//设置 TIMx 通道 1 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH1_CAPTURE_STA=0;			//清空
				TIM3CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);//设置 TIMx 计数器寄存器值
				TIM3CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC1P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM3CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM3CH2_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM3CH2_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM3CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM3CH2_CAPTURE_VAL=0XFFFF;
				}else TIM3CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)//捕获2发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM3CH2_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM3CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM3CH2_CAPTURE_VAL=TIM_GetCapture2(TIM3);//获得 TIMx 输入捕获 2 的值
		   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC2P=0 设置为下降沿捕获
																	//设置 TIMx 通道 2 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH2_CAPTURE_STA=0;			//清空
				TIM3CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);//设置 TIMx 计数器寄存器值
				TIM3CH2_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC2P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM3CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM3CH3_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM3CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM3CH3_CAPTURE_VAL=0XFFFF;
				}else TIM3CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//捕获3发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM3CH3_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM3CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM3CH3_CAPTURE_VAL=TIM_GetCapture3(TIM3);//获得 TIMx 输入捕获 3 的值
		   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC3P=0 设置为下降沿捕获
																	//设置 TIMx 通道 3 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH3_CAPTURE_STA=0;			//清空
				TIM3CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);//设置 TIMx 计数器寄存器值
				TIM3CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC3P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM3CH4_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM3CH4_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM3CH4_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM3CH4_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM3CH4_CAPTURE_VAL=0XFFFF;
				}else TIM3CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)//捕获4发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM3CH4_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM3CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM3CH4_CAPTURE_VAL=TIM_GetCapture4(TIM3);//获得 TIMx 输入捕获 4 的值
		   		TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC4P=0 设置为下降沿捕获
																	//设置 TIMx 通道 4 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3CH4_CAPTURE_STA=0;			//清空
				TIM3CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);//设置 TIMx 计数器寄存器值
				TIM3CH4_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC4P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //清除中断标志位
}
#endif /* TIM3_IRQHandler_ENABLE */

#ifdef TIM4_IRQHandler_ENABLE
void TIM4_IRQHandler(void)
{
	if((TIM4CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM4CH1_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM4CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM4CH1_CAPTURE_VAL=0XFFFF;
				}else TIM4CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//捕获1发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM4CH1_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM4CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM4CH1_CAPTURE_VAL=TIM_GetCapture1(TIM4);//获得 TIMx 输入捕获 1 的值
		   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC1P=0 设置为下降沿捕获
																	//设置 TIMx 通道 1 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM4CH1_CAPTURE_STA=0;			//清空
				TIM4CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);//设置 TIMx 计数器寄存器值
				TIM4CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC1P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM4CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM4CH2_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM4CH2_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM4CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM4CH2_CAPTURE_VAL=0XFFFF;
				}else TIM4CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)//捕获2发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM4CH2_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM4CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM4CH2_CAPTURE_VAL=TIM_GetCapture2(TIM4);//获得 TIMx 输入捕获 2 的值
		   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC2P=0 设置为下降沿捕获
																	//设置 TIMx 通道 2 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM4CH2_CAPTURE_STA=0;			//清空
				TIM4CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);//设置 TIMx 计数器寄存器值
				TIM4CH2_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC2P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM4CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM4CH3_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM4CH3_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM4CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM4CH3_CAPTURE_VAL=0XFFFF;
				}else TIM4CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//捕获3发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM4CH3_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM4CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM4CH3_CAPTURE_VAL=TIM_GetCapture3(TIM4);//获得 TIMx 输入捕获 3 的值
		   		TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC3P=0 设置为下降沿捕获
																	//设置 TIMx 通道 3 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM4CH3_CAPTURE_STA=0;			//清空
				TIM4CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);//设置 TIMx 计数器寄存器值
				TIM4CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC3P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM4CH4_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM4CH4_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM4CH4_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM4CH4_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM4CH4_CAPTURE_VAL=0XFFFF;
				}else TIM4CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)//捕获4发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM4CH4_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM4CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM4CH4_CAPTURE_VAL=TIM_GetCapture4(TIM4);//获得 TIMx 输入捕获 4 的值
		   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC4P=0 设置为下降沿捕获
																	//设置 TIMx 通道 4 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM4CH4_CAPTURE_STA=0;			//清空
				TIM4CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);//设置 TIMx 计数器寄存器值
				TIM4CH4_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC4P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //清除中断标志位
}
#endif /* TIM4_IRQHandler_ENABLE */

#ifdef TIM5_IRQHandler_ENABLE
void TIM5_IRQHandler(void)
{
	if((TIM5CH1_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM5CH1_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//捕获1发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//获得 TIMx 输入捕获 1 的值
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling); //CC1P=0 设置为下降沿捕获
																	//设置 TIMx 通道 1 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH1_CAPTURE_STA=0;			//清空
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);//设置 TIMx 计数器寄存器值
				TIM5CH1_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC1P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM5CH2_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM5CH2_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM5CH2_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH2_CAPTURE_VAL=0XFFFF;
				}else TIM5CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)//捕获2发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM5CH2_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM5CH2_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM5CH2_CAPTURE_VAL=TIM_GetCapture2(TIM5);//获得 TIMx 输入捕获 2 的值
		   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling); //CC2P=0 设置为下降沿捕获
																	//设置 TIMx 通道 2 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH2_CAPTURE_STA=0;			//清空
				TIM5CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);//设置 TIMx 计数器寄存器值
				TIM5CH2_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC2P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM5CH3_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM5CH3_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM5CH3_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH3_CAPTURE_VAL=0XFFFF;
				}else TIM5CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//捕获3发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM5CH3_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM5CH3_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM5CH3_CAPTURE_VAL=TIM_GetCapture3(TIM5);//获得 TIMx 输入捕获 3 的值
		   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling); //CC3P=0 设置为下降沿捕获
																	//设置 TIMx 通道 3 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH3_CAPTURE_STA=0;			//清空
				TIM5CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);//设置 TIMx 计数器寄存器值
				TIM5CH3_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC3P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM5CH4_CAPTURE_STA&0X80)==0)//还未成功捕获	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM 中断源
		 
		{	    
			if(TIM5CH4_CAPTURE_STA&0X40)//已经捕获到低电平了
			{
				if((TIM5CH4_CAPTURE_STA&0X3F)==0X3F)//低电平太长了
				{
					TIM5CH4_CAPTURE_STA|=0X80;//标记成功捕获了一次
					TIM5CH4_CAPTURE_VAL=0XFFFF;
				}else TIM5CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)//捕获4发生捕获事件	检查指定的 TIM 中断发生与否
		{	
			if(TIM5CH4_CAPTURE_STA&0X40)		//捕获到一个上升沿 		
			{	  			
				TIM5CH4_CAPTURE_STA|=0X80;		//标记成功捕获到一次低电平脉宽
				TIM5CH4_CAPTURE_VAL=TIM_GetCapture4(TIM5);//获得 TIMx 输入捕获 4 的值
		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling); //CC4P=0 设置为下降沿捕获
																	//设置 TIMx 通道 4 极性
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM5CH4_CAPTURE_STA=0;			//清空
				TIM5CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);//设置 TIMx 计数器寄存器值
				TIM5CH4_CAPTURE_STA|=0X40;		//标记捕获到了上升沿
		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC4P=1 设置为上升沿捕获
															/*TIM_ICPolarity_Rising TIM 输入捕获上升沿
																TIM_ICPolarity_Falling TIM 输入捕获下降沿			
															*/
			}		    
		}			     	    					   
 	}

    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //清除中断标志位
}
#endif /* TIM5_IRQHandler_ENABLE */


void TIM2_CATCH_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
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
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
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
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
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
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
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
void TIM3_CATCH_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;		
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
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //TIM3 复用功能部分映射
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;		
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
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;		
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
void TIM4_CATCH_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
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
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
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
void TIM5_CATCH_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		//使能TIM5
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;		//复用推挽输出	
//		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		
		switch(TIM_channel)
		{
			case 1:	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);//PA0 上拉
					break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PA1 上拉				
					break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2 上拉
					break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA3 上拉			
			break;	
		}
	}

}

void TIM_CATCH_Gpio_init(u8 TIMx,u16 TIM_channel,u8 remap_pwm)
{
	switch(TIMx)
	{
		case 2:TIM2_CATCH_GPIO_Init(TIM_channel,remap_pwm);break;
		case 3:TIM3_CATCH_GPIO_Init(TIM_channel,remap_pwm);break;
		case 4:TIM4_CATCH_GPIO_Init(TIM_channel,remap_pwm);break;
		case 5:TIM5_CATCH_GPIO_Init(TIM_channel,remap_pwm);break;		
	}
}
TIM_TypeDef* get_CATCH_num(u8 TIMx)
{
	switch(TIMx)
	{
		case 2:return TIM2;
		case 3:return TIM3;
		case 4:return TIM4;
		case 5:return TIM5;		
	}
	return 0;
}


void TIM_Catch_Init(u8 TIMx,u16 TIM_channel,u8 remap_pwm,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	TIM_TypeDef* TIM;
    uint16_t channel;
	NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM=get_CATCH_num(TIMx);
	TIM_CATCH_Gpio_init(TIMx,TIM_channel,remap_pwm);


	
	    //这个就是自动装载的计数值，由于计数是从0开始的，计数10000次后为9999
    TIM_TimeBaseStructure.TIM_Period =65535;
    // 这个就是预分频系数，当由于为0时表示不分频所以要减1
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
    // 高级应用本次不涉及。定义在定时器时钟(CK_INT)频率与数字滤波器(ETR,TIx)
    // 使用的采样频率之间的分频比例
    TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;
    //向上计数
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //初始化定时器5
    TIM_TimeBaseInit(TIM, &TIM_TimeBaseStructure);

    /* Clear TIM5 update pending flag[清除TIM5溢出中断标志] */

	switch(TIM_channel)
	{
		case 1:channel=TIM_Channel_1;break;
		case 2:channel=TIM_Channel_2;break;
		case 3:channel=TIM_Channel_3;break;
		case 4:channel=TIM_Channel_4;break;		
	}
		//初始化TIM5输入捕获参数
	TIM_ICInitStructure.TIM_Channel = channel; //CC1S=01 	选择输入端 IC1映射到TI1上
  	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	//下升沿捕获
  	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
  	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //配置输入分频,不分频 
  	TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 配置输入滤波器 不滤波
  	TIM_ICInit(TIM, &TIM_ICInitStructure);
    /* TIM5 enable counter */
    TIM_Cmd(TIM, ENABLE);  //计数器使能，开始工作

 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
#ifdef STM32F10X_MD
	switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;break;     
    }
#endif /* STM32F10X_MD */
	
#ifdef STM32F10X_HD
	switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;break;
        case 5:NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ;break;      
    }
#endif /* STM32F10X_HD */

#ifdef STM32F10X_CL
	switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;break;
        case 5:NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ;break;      
    }
#endif /* STM32F10X_CL */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	switch(TIM_channel)
	{
		case 1:	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC1,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
				break;
		case 2:	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC2,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
				break;
		case 3:	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC3,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
				break;
		case 4:	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
				break;		
	}
//	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//允许更新中断 ,允许CC1IE捕获中断
	
}
/*
  * log:

  *	2016年7月12日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/

