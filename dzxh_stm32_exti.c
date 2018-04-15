#include "dzxh_stm32_exti.h"

/*******ʹ�÷���***********************************************************/
/*

@��:	EXTIX_Init(3,4,EXTI_Trigger_Falling,0,0);

*/
/*******˵��******************************************************************/
/*	
˵����	��ʼ���������д��Ӧ�жϺ������жϺ����ڱ�ҳ
		�ж���0-4ÿ���ж��߶�Ӧһ���жϺ�����
		�ж���5-9�����жϺ���EXTI9_5_IRQHandler��
		�ж���10-15�����жϺ���EXTI15_10_IRQHandler��	
*/
/*******˵��******************************************************************/
/*
(Ĭ�ϣ�4���������ȼ���4����Ӧ���ȼ�)
(Ĭ�ϣ�EXTI_Mode_Interrupt�ж�ģʽ���ɻ�ΪEXTI_Mode_Event�¼�����)
//����1��GPIO��ţ���Χ��1,2,3,4,5��
										1 ���� GPIOA
										2 ���� GPIOB
										3 ���� GPIOC
										4 ���� GPIOD
										5 ���� GPIOE
										6 ���� GPIOF
										7 ���� GPIOG
										
//����2����Ӧ����	(��Χ: 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)	
					
//����3����Ӧģʽ	 

						EXTI_Trigger 					����
					EXTI_Trigger_Falling 			����������·�½���Ϊ�ж�����
					EXTI_Trigger_Rising 			����������·������Ϊ�ж�����
					EXTI_Trigger_Rising_Falling 	����������·�����غ��½���Ϊ�ж�����

//����4����Ӧ�������ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��

//����5����Ӧ��Ӧ���ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��

*/
/*****************************************************************************/

//�������ȼ��ߵ��ܽ��������ȼ��͵Ĵ��
//�����ж�ͬʱ����ں˾ͻ�������Ӧ��Ӧ���ȼ��ߵ�

/***�жϺ���**********************************************************************/

void EXTI0_IRQHandler(void)
{
	/* ����жϹ����־λ������ᱻ��Ϊ�ж�û�б������ѭ���ٴν����ж� */
	EXTI_ClearITPendingBit(EXTI_Line0);
}

void EXTI1_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line1);
}

void EXTI2_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line2);
	
}

void EXTI3_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line3);
	
}

void EXTI4_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line4);

}

void EXTI9_5_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line5);
 	EXTI_ClearITPendingBit(EXTI_Line6);
 	EXTI_ClearITPendingBit(EXTI_Line7);
 	EXTI_ClearITPendingBit(EXTI_Line8);
 	EXTI_ClearITPendingBit(EXTI_Line9);
	
}

void EXTI15_10_IRQHandler(void)
{
 	EXTI_ClearITPendingBit(EXTI_Line10);
 	EXTI_ClearITPendingBit(EXTI_Line11);
 	EXTI_ClearITPendingBit(EXTI_Line12);
 	EXTI_ClearITPendingBit(EXTI_Line13);
 	EXTI_ClearITPendingBit(EXTI_Line14);
 	EXTI_ClearITPendingBit(EXTI_Line15);

}

/*****************************************************************************/
/*
	�жϳ�ʼ������
*/
void EXTIX_Init(u8 GPIOx,u8 GPIO_PIN,EXTITrigger_TypeDef  EXTI_Mode,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	uint8_t	PinSource;
	GPIO_TypeDef* GPIO_P;
	EXTITrigger_TypeDef EXTI_Mode_P;
	
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//4���������ȼ���4����Ӧ���ȼ�

	/* ����AFIO��ʱ�� */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	EXTI_Mode_P=EXTI_Mode;
	switch(GPIOx)
	{
		case 1:	GPIO_P=GPIOA;break;
		case 2:	GPIO_P=GPIOB;break;
		case 3:	GPIO_P=GPIOC;break;
		case 4:	GPIO_P=GPIOD;break;
		case 5:	GPIO_P=GPIOE;break;
		case 6:	GPIO_P=GPIOF;break;
		case 7:	GPIO_P=GPIOG;break;	
	}
	
	if(EXTI_Mode_P==EXTI_Trigger_Falling)
	{
		switch(GPIO_PIN)
		{
			case 0:	GPIO_SetBits(GPIO_P,GPIO_Pin_0);break;		//�����ø�
			case 1:	GPIO_SetBits(GPIO_P,GPIO_Pin_1);break;		//�����ø�
			case 2:	GPIO_SetBits(GPIO_P,GPIO_Pin_2);break;		//�����ø�
			case 3:	GPIO_SetBits(GPIO_P,GPIO_Pin_3);break;		//�����ø�
			case 4:	GPIO_SetBits(GPIO_P,GPIO_Pin_4);break;		//�����ø�
			case 5:	GPIO_SetBits(GPIO_P,GPIO_Pin_5);break;		//�����ø�
			case 6:	GPIO_SetBits(GPIO_P,GPIO_Pin_6);break;		//�����ø�
			case 7:	GPIO_SetBits(GPIO_P,GPIO_Pin_7);break;		//�����ø�
			case 8:	GPIO_SetBits(GPIO_P,GPIO_Pin_8);break;		//�����ø�
			case 9:	GPIO_SetBits(GPIO_P,GPIO_Pin_9);break;		//�����ø�
			case 10:	GPIO_SetBits(GPIO_P,GPIO_Pin_10);break;		//�����ø�
			case 11:	GPIO_SetBits(GPIO_P,GPIO_Pin_11);break;		//�����ø�
			case 12:	GPIO_SetBits(GPIO_P,GPIO_Pin_12);break;		//�����ø�
			case 13:	GPIO_SetBits(GPIO_P,GPIO_Pin_13);break;		//�����ø�
			case 14:	GPIO_SetBits(GPIO_P,GPIO_Pin_14);break;		//�����ø�
			case 15:	GPIO_SetBits(GPIO_P,GPIO_Pin_15);break;		//�����ø�
		}		
	}
	
	if(EXTI_Mode_P==EXTI_Trigger_Rising)
	{
		switch(GPIO_PIN)
		{
			case 0: GPIO_ResetBits(GPIO_P,GPIO_Pin_0);break;	//��������
			case 1: GPIO_ResetBits(GPIO_P,GPIO_Pin_1);break;	//��������
			case 2: GPIO_ResetBits(GPIO_P,GPIO_Pin_2);break;	//��������
			case 3: GPIO_ResetBits(GPIO_P,GPIO_Pin_3);break;	//��������
			case 4: GPIO_ResetBits(GPIO_P,GPIO_Pin_4);break;	//��������
			case 5: GPIO_ResetBits(GPIO_P,GPIO_Pin_5);break;	//��������
			case 6: GPIO_ResetBits(GPIO_P,GPIO_Pin_6);break;	//��������
			case 7: GPIO_ResetBits(GPIO_P,GPIO_Pin_7);break;	//��������
			case 8: GPIO_ResetBits(GPIO_P,GPIO_Pin_8);break;	//��������
			case 9: GPIO_ResetBits(GPIO_P,GPIO_Pin_9);break;	//��������
			case 10: GPIO_ResetBits(GPIO_P,GPIO_Pin_10);break;	//��������
			case 11: GPIO_ResetBits(GPIO_P,GPIO_Pin_11);break;	//��������
			case 12: GPIO_ResetBits(GPIO_P,GPIO_Pin_12);break;	//��������
			case 13: GPIO_ResetBits(GPIO_P,GPIO_Pin_13);break;	//��������
			case 14: GPIO_ResetBits(GPIO_P,GPIO_Pin_14);break;	//��������
			case 15: GPIO_ResetBits(GPIO_P,GPIO_Pin_15);break;	//��������

		}
	}
	
	switch(GPIO_PIN)
	{
		case 0:	    EXTI_InitStructure.EXTI_Line = EXTI_Line0;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource0;
					break;
		case 1:	    EXTI_InitStructure.EXTI_Line = EXTI_Line1;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource1;
					break;
		case 2:	    EXTI_InitStructure.EXTI_Line = EXTI_Line2;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource2;
					break;
		case 3:	    EXTI_InitStructure.EXTI_Line = EXTI_Line3;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource3;
					break;
		case 4:	    EXTI_InitStructure.EXTI_Line = EXTI_Line4;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource4;
					break;
		case 5:	    EXTI_InitStructure.EXTI_Line = EXTI_Line5;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource5;
					break;		
		case 6:	    EXTI_InitStructure.EXTI_Line = EXTI_Line6;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource6;
					break;		
		case 7:	    EXTI_InitStructure.EXTI_Line = EXTI_Line7;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource7;
					break;		
		case 8:	    EXTI_InitStructure.EXTI_Line = EXTI_Line8;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource8;
					break;		
		case 9:	    EXTI_InitStructure.EXTI_Line = EXTI_Line9;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource9;
					break;		
		case 10:	EXTI_InitStructure.EXTI_Line = EXTI_Line10;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource10;
					break;		
		case 11:	EXTI_InitStructure.EXTI_Line = EXTI_Line11;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource11;
					break;		
		case 12:	EXTI_InitStructure.EXTI_Line = EXTI_Line12;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource12;
					break;		
		case 13:	EXTI_InitStructure.EXTI_Line = EXTI_Line13;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource13;
					break;		
		case 14:	EXTI_InitStructure.EXTI_Line = EXTI_Line14;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource14;
					break;		
		case 15:	EXTI_InitStructure.EXTI_Line = EXTI_Line15;			   //�ж���
					NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	 	//ʹ���ⲿ�ж�ͨ��
					PinSource=GPIO_PinSource15;
					break;		
	}
	
		switch(GPIOx)
	{
		case 1:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, PinSource);break;
		case 2:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, PinSource);break;
		case 3:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, PinSource);break;
		case 4:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, PinSource);break;
		case 5:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, PinSource);break;
		case 6:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOF, PinSource);break;
		case 7:		GPIO_EXTILineConfig(GPIO_PortSourceGPIOG, PinSource);break;
		
	}
	
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		 //�ж�ģʽ
    EXTI_InitStructure.EXTI_Trigger = EXTI_Mode;  			//����ģʽ
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;   //��ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		  //��Ӧ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure);				 //����NVIC_InitStructure��ָ���Ĳ�����ʼ������NVIC	
}
/*
  * log:

  *	2016��7��6��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

