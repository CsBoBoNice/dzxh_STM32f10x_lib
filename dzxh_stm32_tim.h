#ifndef _DZXH_STM32_TIM_
#define _DZXH_STM32_TIM_
#include "stm32f10x.h"
#define TIM_ENABLE 1
#define TIM_DISABLE 0


extern int tim2_ready_buf_ok;	//��ʱ��־ 1δ��ʱ 0��ʱ

//���ܣ�ʹ�ܻ�ʧ�ܶ�ʱ��
//����1����ʱ���ı��(��Χ 2~7)
//����2: 0�ر�(TIM_DISABLE)��1����(TIM_ENABLE)
//����Tim_Cmd(5,1);	//ʹ�ܶ�ʱ��5
void Tim_Cmd(u8 TIMx,u8 flag);

u8 TIM_Common_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority);
//����	TIM_Common_Init(5,7200,10000,TIM_CounterMode_Up,0,1);	//��ʱ����ʼ��
//������5��Ԥ��Ƶ7200,1�����һ���жϣ����ϼ���ģʽ���������ȼ�����0����Ӧ���ȼ�����1
/*******˵��******************************************************************/
/*
��ʱ����ʼ�� ��Ĭ��ʱ�ӷָ�ΪTIM_CKD_DIV1��TIM����Ƚϼ��Ըߣ�ʹ�ܹأ�
			(Ĭ�ϣ�4���������ȼ���4����Ӧ���ȼ�)
TIM_Common_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority)

����1��ѡ�õĶ�ʱ����(��Χ 2~7)
						2	TIM2
						3	TIM3
						4	TIM4
						5	TIM5
						6	TIM6
						7	TIM7
����2��ʱ��Ԥ��Ƶֵ�����ü�1����ȡֵ��Χ��0����65535

����3��װ�����Զ���װ�ؼĴ������ڵ�ֵ���趨���ڣ�ȡֵ��Χ��0����65535

����4������ģʽ
				TIM_CounterMode_Up 				TIM ���ϼ���ģʽ
				TIM_CounterMode_Down 			TIM ���¼���ģʽ
				TIM_CounterMode_CenterAligned1 	TIM �������ģʽ 1 ����ģʽ
				TIM_CounterMode_CenterAligned2 	TIM �������ģʽ 2 ����ģʽ
				TIM_CounterMode_CenterAligned3 	TIM �������ģʽ 3 ����ģʽ
				
����5����Ӧ�������ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��

����6����Ӧ��Ӧ���ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��

����ֵ��0�ɹ���1ʧ��
*/
/********************************************************************************/
#endif

