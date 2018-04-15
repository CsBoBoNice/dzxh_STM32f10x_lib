#include "dzxh_stm32_dac.h"
/************************************************************************************************************/
/*
@例:	Dac_Init(1);	//DAC初始化

		参数1：选择DAC通道	(取值范围：1,2)
								1	ADC1	PA4
								2	ADC2	PA5
		
@例:	Dac_Set_Vol(1,2600);	//设置通道输出电压

		参数1：选择DAC通道	(取值范围：1,2)
		
		参数2：设置通道输出电压	取值范围：0~3300,代表 0~3.3V

*/
/************************************************************************************************************/
void Dac_Init(u8 DACx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能PORTA通道时钟
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //使能DAC通道时钟 

	switch(DACx)
	{
		case 1:	
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // 端口配置
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //模拟输入
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
					GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 输出高
									
					DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
					DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
					DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
					DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
					DAC_Init(DAC_Channel_1,&DAC_InitType);	 //初始化DAC通道1

					DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC1
				  
					DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
		
		case 2 :	
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 // 端口配置
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //模拟输入
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
					GPIO_SetBits(GPIOA,GPIO_Pin_5)	;//PA.4 输出高
									
					DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
					DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
					DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
					DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC2输出缓存关闭 BOFF1=1
					DAC_Init(DAC_Channel_2,&DAC_InitType);	 //初始化DAC通道1

					DAC_Cmd(DAC_Channel_2, ENABLE);  //使能DAC2
				  
					DAC_SetChannel2Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值
	}	
}


//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac_Set_Vol(u8 DACx,u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	switch(DACx)
	{
		case 1:	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
		
		case 2:	DAC_SetChannel2Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
	}

}
/*
  * log:

  *	2016年7月7日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/
