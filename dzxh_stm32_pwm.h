#ifndef _DZXH_STM32_PWM_H_ 
#define _DZXH_STM32_PWM_H_
#include "stm32f10x.h"

u8 TIM_PWM_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,u16 TIM_pulse,u16 TIM_channel,u8 remap_pwm);//���ܣ��ı�PWMռ�ձ�

void Change_PWM_pulse(TIM_TypeDef* TIM,u8 TIM_channel,u16 pulse);//���ܣ��ı�PWM����

void Change_PWM_period(TIM_TypeDef* TIM,u16 TIM_period);//���ܣ��ı�PWM������


/******ʹ�÷���******************************************************************/
/*
	TIM_PWM_Init(1,72,20000,1100,1��0);	//PWM��ʼ��
	
	Change_PWM_period( TIM1,10000);		//�ı�PWM����
	
	Change_PWM_pulse(TIM1,2,600);		//�ı�PWMռ�ձ�
*/
/***************************************************************************/
/*
//pwm��ʼ�� ��Ĭ��ʱ�ӷָ�Ϊ1�����ϼ�����TIM����Ƚϼ��Ըߣ���ʹ�ܣ�
//����1��ѡ�õĶ�ʱ����(��Χ 1,2,3,4,)
						1  	TIM1
						2	TIM2
						3	TIM3
						4	TIM4
						5	TIM5
//����2��ʱ��Ԥ��Ƶֵ�����ü�1����
//����3��װ�����Զ���װ�ؼĴ������ڵ�ֵ���趨���ڣ�
//����4����װ�벶��ȽϼĴ���������ֵ���趨����ߵ�ƽʱ�䣩
//����5����ʱ��ͨ��(��Χ 1,2,3,4,)
//����6��������ӳ��	(��Χ �ο��±�)
//��ʱ�����ţ�

��ʱ��	������ӳ��		ͨ��	1	  2	   3	4

TIM1	0 û��ӳ�� 				PA8   PA9  PA10  PA11 
		1 ��ȫ��ӳ��			PE9	  PE11 PE13	 PE14

TIM2	0 û��ӳ��				PA0   PA1  PA2   PA3 
		1 ������ӳ��1			PA15  PB3  PA2	 PA3
		2 ������ӳ��2			PA0   PA1  PB10	 PB11
		3 ��ȫ��ӳ��			PA15  PB3  PB10  PB11

TIM3	0 û��ӳ��				PA6   PA7  PB0   PB1
		1 ������ӳ��			PB4   PB5  PB0   PB1
		2 ��ȫ��ӳ��			PC6   PC7  PC8   PC9

TIM4	0 û��ӳ��				PB6   PB7  PB8   PB9
		1 ��ȫ��ӳ��			PD12  PD13 PD14  PD15

TIM5    0 û��ӳ��				PA0   PA1  PA2   PA3

				��ʱ��	ͨ��	1	 2	  3	    4
				TIM1 			PA8  PA9  PA10  PA11 
				TIM2 			PA0  PA1  PA2   PA3 
				TIM3 			PA6  PA7  PB0   PB1 
				TIM4 			PB6  PB7  PB8   PB9
				TIM5			PA0  PA1  PA2   PA3
//����ֵ��0�ɹ���1ʧ��

*/
/***************************************************************************/

#endif
