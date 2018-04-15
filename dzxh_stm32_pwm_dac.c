#include "dzxh_stm32_pwm_dac.h"
#include "dzxh_stm32_pwm.h"

#define TIM_DAC_period 155	//��ʱ������ֵ

/********PWMģ��DAC*************************************************************************************************/
/*

@��:	PWM_DAC_Set(TIM1,1,230);
		����1��ѡ�õĶ�ʱ����TIM1��TIM2��TIM3��TIM4��TIM5

		����2����ʱ��ͨ��(��Χ 1,2,3,4,)
		
		����3��//���������ѹ	ȡֵ��Χ(0~330,����0~3.3V)
		
@��:	PWM_DAC_Init(1,1,0);		//��ʼ��

		����1��ѡ�õĶ�ʱ����(��Χ 1,2,3,4,)
						1  	TIM1
						2	TIM2
						3	TIM3
						4	TIM4
						5	TIM5
						
		����2����ʱ��ͨ��(��Χ 1,2,3,4,)
		
		����3��������ӳ��	(��Χ �ο��±�)
		
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
*/
/****************************************************************************************************************/

//���������ѹ
//vol:0~330,����0~3.3V
void PWM_DAC_Set(TIM_TypeDef* TIMx,u16 TIM_channel,u16 vol)
{
	float temp=vol+6;	//������Ϊ����ֵ��׼ȷ
	temp/=100;
	temp=temp*TIM_DAC_period/3.3;
	switch(TIM_channel)
	{
		case 1:	TIM_SetCompare1(TIMx,temp);break;
		case 2:	TIM_SetCompare2(TIMx,temp);break;
		case 3:	TIM_SetCompare3(TIMx,temp);break;
		case 4:	TIM_SetCompare4(TIMx,temp);break;
	}	
//	TIM_SetCompare1(TIMx,temp);
}

static TIM_TypeDef* get_tim_num(u8 TIMx)
{
	switch(TIMx)
	{
		case 1:return TIM1;
		case 2:return TIM2;
		case 3:return TIM3;
		case 4:return TIM4;
		case 5:return TIM5;		
	}
	return 0;
}

void PWM_DAC_Init(u8 TIMx,u16 TIM_channel,u8 remap_pwm)
{
	TIM_TypeDef* TIM;
	TIM=get_tim_num(TIMx);
	TIM_PWM_Init(TIMx,0,TIM_DAC_period,100,TIM_channel,remap_pwm);	//PWM��ʼ��
	switch(TIM_channel)
	{
		case 1:	TIM_SetCompare1(TIM,100);break;//��ʼֵΪ0
		case 2:	TIM_SetCompare2(TIM,100);break;//��ʼֵΪ0
		case 3:	TIM_SetCompare3(TIM,100);break;//��ʼֵΪ0
		case 4:	TIM_SetCompare4(TIM,100);break;//��ʼֵΪ0
	}
}

/*
  * log:

  *	2016��7��7��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
