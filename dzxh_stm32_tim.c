#include "dzxh_stm32_tim.h"
#include "include.h"
/*******ʹ�÷���**************************************************************/
/*
@��:	TIM_Common_Init(5,7200,10000,TIM_CounterMode_Up,0,1);	//��ʱ����ʼ��
	
	//��ʱ��5��Ԥ��Ƶ7200,1�����һ���жϣ����ϼ���ģʽ���������ȼ�����0����Ӧ���ȼ�����1
	
@��:	Tim_Cmd(5,1);	//ʹ�ܶ�ʱ��5
	
	//���ܣ�ʹ�ܻ�ʧ�ܶ�ʱ��
	//����1����ʱ���ı��(��Χ 2~7)
	//����2: 0�ر�(TIM_DISABLE)��1����(TIM_ENABLE)
*/
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

//�������ȼ��ߵ��ܽ��������ȼ��͵Ĵ��
//�����ж�ͬʱ����ں˾ͻ�������Ӧ��Ӧ���ȼ��ߵ�

/***�жϺ���**********************************************************************/


void TIM2_IRQHandler(void)
{ 
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {	
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); /* �������жϱ�־ */
		#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
		USART_ReceiveOvertimeProcess();
		#endif
    }
	
}
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); /* �������жϱ�־ */
    }	
}
void TIM4_IRQHandler(void)
{

}
void TIM5_IRQHandler(void)
{
	
}
void TIM6_IRQHander(void)
{

}
void TIM7_IRQHander(void)
{
    TIM_ClearITPendingBit(TIM7,TIM_IT_Update);/* �������жϱ�־ */
}

/********************************************************************************/

TIM_TypeDef* get_tim(u8 TIMx)
{
	switch(TIMx)
	{
		case 2:return TIM2;
		case 3:return TIM3;
		case 4:return TIM4;
        case 5:return TIM5;
		case 6:return TIM6;
		case 7:return TIM7;
	}
	return 0;
}

#ifdef STM32F10X_MD
void time_nvic_init(u8 TIMx,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	 
	NVIC_InitTypeDef NVIC_InitStructure; 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);break;        
    }
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
#endif /* STM32F10X_MD */

#ifdef STM32F10X_HD
void time_nvic_init(u8 TIMx,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	 
	NVIC_InitTypeDef NVIC_InitStructure; 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);break;
        case 5:NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);break;
        case 6:NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);break;
        case 7:NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);break;        
    }
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
#endif /* STM32F10X_HD */ 

#ifdef STM32F10X_CL	
void time_nvic_init(u8 TIMx,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	 
	NVIC_InitTypeDef NVIC_InitStructure; 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
    switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);break;
        case 5:NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);break;
        case 6:NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn ; 
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);break;
        case 7:NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn ;
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7,ENABLE);break;        
    }
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
}
#endif /* STM32F10X_CL */ 

u8 TIM_Common_Init(u8 TIMx,u16 TIM_prescaler,u16 TIM_period,uint16_t TIM_CounterMode,uint8_t PreemptionPriority,uint8_t SubPriority)
//pwm��ʼ�� ��Ĭ��ʱ�ӷָ�Ϊ1�����ϼ�����TIM����Ƚϼ��Ըߣ�ʹ�ܹأ�
//����1��ѡ�õĶ�ʱ����(��Χ 2~7)
//����2��ʱ��Ԥ��Ƶֵ�����ü�1����
//����3��װ�����Զ���װ�ؼĴ������ڵ�ֵ���趨���ڣ�
//����ֵ��0�ɹ���1ʧ��
{
	TIM_TypeDef* TIM;
	TIM_TimeBaseInitTypeDef tim_TimeBaseInitTypeDef;
	TIM=get_tim(TIMx);
	if(0!=TIM)
	{
        time_nvic_init(TIMx,PreemptionPriority,SubPriority);
		tim_TimeBaseInitTypeDef.TIM_ClockDivision=TIM_CKD_DIV1;/* ������Ƶ */
		tim_TimeBaseInitTypeDef.TIM_CounterMode=TIM_CounterMode;/* ����ģʽ */
		tim_TimeBaseInitTypeDef.TIM_Period=TIM_period-1; /* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */ 
		tim_TimeBaseInitTypeDef.TIM_Prescaler=TIM_prescaler-1;/* Ԥ��Ƶϵ��*/
		
		TIM_ARRPreloadConfig(TIM,ENABLE);/*ʹ�� TIMx �� ARR �ϵ�Ԥװ�ؼĴ���*/
		
		/***���¼��д���˳�򲻿ɸ��ģ�����˳�ʼ����ʱ�������Ͻ���һ�ζ�ʱ��������***/	    
        TIM_TimeBaseInit(TIM,&tim_TimeBaseInitTypeDef);/* ��ʼ����ʱ�� */
		TIM_ClearITPendingBit(TIM, TIM_IT_Update);/* �������жϱ�־ */
        TIM_ITConfig(TIM,TIM_IT_Update,ENABLE);/* ����ж�ʹ�� */
		TIM_Cmd(TIM,DISABLE);/* ��������ʹ�� */

		return 0;
	}
	return 1;
}
void Tim_Cmd(u8 TIMx,u8 flag)
{
    TIM_TypeDef* TIM;
	TIM=get_tim(TIMx);
    if(flag)
    {
        TIM_Cmd(TIM,ENABLE);/* ������ʹ�� */
    }
    else
    {
        TIM_Cmd(TIM,DISABLE);/* ��������ʹ�� */
    }
}
/*
  * log:

  *	2018��4��6��
	�޸��˳�ʼ����ʱ�������Ͻ���һ�ζ�ʱ��������
	ɾ�����ж����ȼ���ʼ������dzxh_stm32_nvic.c��ͳһ��ʼ��
	Programmer:����

  *	2016��7��7��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

