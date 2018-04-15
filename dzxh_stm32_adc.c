#include "dzxh_stm32_adc.h"
#include "dzxh_stm32_delay.h"

/*********使用方法***********************************************************************************/
/*
注：可修改adc采样精度 ADC_PRECISON
@例:	Adc_Init(1,10);		//ADC初始化，通道10
		参数1：	选取ADC	(取值范围：1,2)	
										1	ADC1
										2	ADC2
										
		参数2：初始化ADC通道(取值范围：0到15)
										 ADC 通道		 对应IO口
										ADC_Channel_0		PA0
										ADC_Channel_1		PA1
										ADC_Channel_2		PA2
										ADC_Channel_3		PA3
										ADC_Channel_4		PA4
										ADC_Channel_5		PA5
										ADC_Channel_6		PA6
										ADC_Channel_7		PA7
										ADC_Channel_8		PB0
										ADC_Channel_9		PB1
										ADC_Channel_10		PC0
										ADC_Channel_11		PC1
										ADC_Channel_12		PC2
										ADC_Channel_13		PC3
										ADC_Channel_14		PC4
										ADC_Channel_15		PC5

		u16 adcx;
		
@例:	adcx=Get_Adc(ADC_Channel_10,1);	//取得ADC_Channel_10 ADC值(该值是百分比值，取值范围0到100)
		参数1：ADC通道	取值范围：
								ADC_Channel_0 	选择 ADC 通道 0
								ADC_Channel_1 	选择 ADC 通道 1
								ADC_Channel_2 	选择 ADC 通道 2
								ADC_Channel_3 	选择 ADC 通道 3
								ADC_Channel_4 	选择 ADC 通道 4
								ADC_Channel_5 	选择 ADC 通道 5
								ADC_Channel_6 	选择 ADC 通道 6
								ADC_Channel_7 	选择 ADC 通道 7
								ADC_Channel_8 	选择 ADC 通道 8
								ADC_Channel_9 	选择 ADC 通道 9
								ADC_Channel_10 	选择 ADC 通道 10
								ADC_Channel_11 	选择 ADC 通道 11
								ADC_Channel_12 	选择 ADC 通道 12
								ADC_Channel_13 	选择 ADC 通道 13
								ADC_Channel_14 	选择 ADC 通道 14
								ADC_Channel_15 	选择 ADC 通道 15
								ADC_Channel_16 	选择 ADC 通道 16
								ADC_Channel_17 	选择 ADC 通道 17
								
		参数2：规则组采样顺序;取值范围 1 到 16

@例:	adcx=Get_Adc_Average(ADC_Channel_10,1,10);	//计算平均值后的ADC值，数据更准确(该值是百分比值，取值范围0到100)
		参数1：ADC通道	取值范围：
								ADC_Channel_0 	选择 ADC 通道 0
								ADC_Channel_1 	选择 ADC 通道 1
								ADC_Channel_2 	选择 ADC 通道 2
								ADC_Channel_3 	选择 ADC 通道 3
								ADC_Channel_4 	选择 ADC 通道 4
								ADC_Channel_5 	选择 ADC 通道 5
								ADC_Channel_6 	选择 ADC 通道 6
								ADC_Channel_7 	选择 ADC 通道 7
								ADC_Channel_8 	选择 ADC 通道 8
								ADC_Channel_9 	选择 ADC 通道 9
								ADC_Channel_10 	选择 ADC 通道 10
								ADC_Channel_11 	选择 ADC 通道 11
								ADC_Channel_12 	选择 ADC 通道 12
								ADC_Channel_13 	选择 ADC 通道 13
								ADC_Channel_14 	选择 ADC 通道 14
								ADC_Channel_15 	选择 ADC 通道 15
								ADC_Channel_16 	选择 ADC 通道 16
								ADC_Channel_17 	选择 ADC 通道 17
								
		参数2：规则组采样顺序;取值范围 1 到 16
		
		参数3：采多少次取平均值；第一次与第二次ADC相隔5ms
		

*/
/****************************************************************************************************/

/****************************************************************************************************/

ADC_TypeDef* ADC;
void ADC_Channel_Gpio_init(u16 ADC_channel)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	switch(ADC_channel)
	{
		case 0:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能ADC通道时钟
				/*PA0 作为模拟通道0输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //管脚0
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 1:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能ADC通道时钟
				/*PA1 作为模拟通道1输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       //管脚1
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 2:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能ADC通道时钟
				/*PA2 作为模拟通道2输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;       //管脚2
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 3:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能ADC通道时钟
				/*PA3 作为模拟通道3输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;       //管脚3
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 4:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能ADC通道时钟
				/*PA4 作为模拟通道4输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;       //管脚4
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 5:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能ADC通道时钟
				/*PA5 作为模拟通道5输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       //管脚5
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 6:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能ADC通道时钟
				/*PA6 作为模拟通道6输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;       //管脚6
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 7:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能ADC通道时钟
				/*PA7 作为模拟通道7输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;       //管脚7
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 8:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	  //使能ADC通道时钟
				/*PB0 作为模拟通道8输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //管脚8
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				break;
		case 9:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	  //使能ADC通道时钟
				/*PB0 作为模拟通道9输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       //管脚9
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				break;
		case 10:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //使能ADC通道时钟
				/*PC0 作为模拟通道10输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //管脚10
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;	
		case 11:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //使能ADC通道时钟
				/*PC1 作为模拟通道11输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       //管脚11
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
		case 12:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //使能ADC通道时钟
				/*PC2 作为模拟通道12输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;       //管脚12
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
		case 13:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //使能ADC通道时钟
				/*PC3 作为模拟通道13输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;       //管脚13
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
		case 14:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //使能ADC通道时钟
				/*PC4 作为模拟通道14输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;       //管脚14
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
		case 15:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //使能ADC通道时钟
				/*PC5 作为模拟通道15输入引脚 */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       //管脚15
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //输入模式
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
	}
}


void  Adc_Init(u8 ADCx,u16 ADC_channel)
{

	ADC_InitTypeDef ADC_InitStructure;
	
	switch(ADCx)
	{
		case 1:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );ADC=ADC1;break;
		case 2:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE );ADC=ADC2;break;
	
	}
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	ADC_Channel_Gpio_init(ADC_channel);

	ADC_DeInit(ADC);  //复位ADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

  
	ADC_Cmd(ADC, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC));	//等待复位校准结束
	
	ADC_StartCalibration(ADC);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//参数1：Adc_Channel 值
//Rank：规则组采样顺序。取值范围 1 到 16
u16 Get_Adc(u8 Adc_Channel,uint8_t Rank)   
{
	u32 temp_val=0;
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC, Adc_Channel, Rank, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC, ADC_FLAG_EOC ));//等待转换结束
	temp_val=ADC_GetConversionValue(ADC);
	temp_val=temp_val * ADC_PRECISON/0x1000;
	return temp_val;	//返回最近一次ADC1规则组的转换结果
}

u16 Get_Adc_Average(u8 Adc_Channel,uint8_t Rank,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(Adc_Channel,Rank);
		delay_ms(5);
	}
	temp_val=temp_val/times;
	return temp_val;
} 

u16 AD_V[16][3];

/*
AD采样加滤波
//参数1：Adc_Channel 值
//Rank：规则组采样顺序。取值范围 1 到 16

滤波算法：中位值平均滤波法（又称防脉冲干扰平均滤法）
*/
u16 Read_ADC(uint8_t Adc_Channel,uint8_t Rank)
{
    u16 ad_valu=0;      //adc采样值
    u16 ad_valu_buf[5];
    u16 ad_sum=0;
    int i;
    int n;
    
    for(i=0;i<5;i++)
    {
        ad_valu_buf[i]=Get_Adc(Adc_Channel,Rank);
    }
    
    n = sizeof (ad_valu_buf) / sizeof (ad_valu_buf[0]);	//计算出数组长度
    bubble_sort(ad_valu_buf, n);	//排序  
    
///*******************求中间3相的值**************************************/       
/*******************去掉最大值最小值求中间相的值**************************************/   		
    ad_sum=ad_valu_buf[1]+ad_valu_buf[2]+ad_valu_buf[3];
    ad_valu = ad_sum / 3;

        
/*******************滑动平均滤波**************************************/
    for(i=0;i<3;i++)         //将每一项往前移动一个位置，最前面的一项舍弃
    {
        AD_V[Adc_Channel][i] = AD_V[Adc_Channel][i + 1];  
    }  
    
    AD_V[Adc_Channel][2]=ad_valu;//将最新的数值放在数组最后一位
 
    ad_sum=0;
    for(i=0;i<3;i++)             //将滑动平均滤波数组的每一个数求和
    {
        ad_sum += AD_V[Adc_Channel][i];
    }
    
    ad_valu=ad_sum / 3;
    ad_sum = 0; 
    
    return ad_valu;
}

void bubble_sort(u16 *a, int n)  //冒泡排序
{
    int i, j;
    u16 temp;
    for (j = 0; j < n - 1; j++)
        for (i = 0; i < n - 1 - j; i++)
        {
            if(a[i] > a[i + 1])
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
}

/*
  * log:

  *	2018年4月7日
	新增了中位值平均滤波法
	将默认的 ADC_SampleTime_55Cycles5 改成了ADC_SampleTime_239Cycles5 提高了精度
	在dzxh_stm32_adc.h中可以修改adc精度
	Programmer:陈述

  *	2016年7月9日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/
