#ifndef  _DZXH_STM32_ADC_H_
#define  _DZXH_STM32_ADC_H_

#include "stm32f10x.h"

#define ADC_PRECISON	10000 //����ADC�������ȣ���ֵ�൱�ڲ������ֵ


void  Adc_Init(u8 ADCx,u16 ADC_channel);	//ADC��ʼ��
u16 Get_Adc(u8 Adc_Channel,uint8_t Rank); 			//ȡ��ADC_Channel ADCֵ
u16 Get_Adc_Average(u8 Adc_Channel,uint8_t Rank,u8 times); //����ƽ��ֵ���ADCֵ�����ݸ�׼ȷ
void bubble_sort(u16 *a, int n);  //ð������
u16 Read_ADC(uint8_t Adc_Channel,uint8_t Rank);	//AD�������˲�
#endif
