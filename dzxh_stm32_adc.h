#ifndef  _DZXH_STM32_ADC_H_
#define  _DZXH_STM32_ADC_H_

#include "stm32f10x.h"

#define ADC_PRECISON	10000 //定义ADC采样精度，这值相当于采样最大值


void  Adc_Init(u8 ADCx,u16 ADC_channel);	//ADC初始化
u16 Get_Adc(u8 Adc_Channel,uint8_t Rank); 			//取得ADC_Channel ADC值
u16 Get_Adc_Average(u8 Adc_Channel,uint8_t Rank,u8 times); //计算平均值后的ADC值，数据更准确
void bubble_sort(u16 *a, int n);  //冒泡排序
u16 Read_ADC(uint8_t Adc_Channel,uint8_t Rank);	//AD采样加滤波
#endif
