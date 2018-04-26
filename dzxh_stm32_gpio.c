#include "dzxh_stm32_gpio.h"

/*******ʹ�÷���***********************************************************/
/*

@��:	GPIO_Common_Init(GPIOA,GPIO_Pin_2|GPIO_Pin_3,GPIO_Mode_Out_PP);	//GPIO��ʼ��
		��ʼ��GPIOA	;PA2��PA3;�������
	
*/
/*************************************************************************/
/*
@��:	GPIO_ResetBits(GPIOD,GPIO_Pin_2);	//��������

@��:	GPIO_SetBits(GPIOD,GPIO_Pin_2);		//�����ø�

@��:	GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2)//��ȡָ���˿ڹܽŵ�����	

@��:	GPIO_ReadInputData(GPIOD)	//��ȡָ���� GPIO �˿�����

@��:	GPIO_ReadOutputDataBit(GPIOD, GPIO_Pin_2)//��ȡָ���˿ڹܽŵ����

@��:	GPIO_Write(GPIOD, 0x55)//��ָ�� GPIO ���ݶ˿�д������
*/
/*************************************************************************/
/*
��Ĭ���ٶ�50M�����������
//����1��GPIO��ţ���Χ��1,2,3,4,5,6,7��
										1 ���� GPIOA
										2 ���� GPIOB
										3 ���� GPIOC
										4 ���� GPIOD
										5 ���� GPIOE
										6 ���� GPIOF
										7 ���� GPIOG
//����2����Ӧ����	
					GPIO_Pin_0
					GPIO_Pin_1
					GPIO_Pin_2
					GPIO_Pin_3
					GPIO_Pin_4
					GPIO_Pin_5
					GPIO_Pin_6
					GPIO_Pin_7
					GPIO_Pin_8
					GPIO_Pin_9
					GPIO_Pin_10
					GPIO_Pin_11
					GPIO_Pin_12
					GPIO_Pin_13
					GPIO_Pin_14
					GPIO_Pin_15
					GPIO_Pin_ALL

//����3����Ӧģʽ	 GPIO_Mode				����			����
					GPIO_Mode_AIN 			ģ������		ADC����
					GPIO_Mode_IN_FLOATING 	��������		����
					GPIO_Mode_IPD 			��������
					GPIO_Mode_IPU 			��������		���벶��
					GPIO_Mode_Out_OD 		��©���
					GPIO_Mode_Out_PP 		�������		����С��
					GPIO_Mode_AF_OD 		���ÿ�©���
					GPIO_Mode_AF_PP 		�����������	PWM

*/
/********************************************************************/

/*
�� PA15�� JTDI��������ģʽ
�� PA14�� JTCK��������ģʽ
�� PA13�� JTMS��������ģʽ
�� PB4�� JNTRST��������ģʽ

JTMS/SWDIO 		���� JTAGģʽѡ�� ����/��� ������������/��� 		PA13
JTCK/SWCLK 		���� JTAGʱ�� 		���� 	����ʱ�� 				PA14
JTDI 			���� JTAG��������  ����  	����					PA15
JTDO/TRACESWO 	��� JTAG�������  ���� 	����ʱΪTRACESWO�ź� 	PB3
JNTRST 			���� JTAGģ�鸴λ  ����  	����					PB4
��ʹ���������ţ�
//�ر�jtag �ı�ָ���ܽŵ�ӳ��	JTAG-DP ʧ�� + SW-DP ʹ��
GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	
*/

void RCC_APB2PeriphClockCmd_init(u8 GPIOx)
{
	switch(GPIOx)
	{
		case 1:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);return;
		case 2:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);return;
		case 3:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);return;
		case 4:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);return;
		case 5:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);return;
		case 6:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF,ENABLE);return;
		case 7:RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOG,ENABLE);return;
	}
	return;
}

void init_gpio_struct(GPIO_InitTypeDef *GPIO_InitStructure,u16 gpio_pin,GPIOSpeed_TypeDef Speed,GPIOMode_TypeDef GPIO_Mode)
{
	GPIO_InitStructure->GPIO_Pin = gpio_pin; 
	GPIO_InitStructure->GPIO_Speed =Speed; 
	GPIO_InitStructure->GPIO_Mode = GPIO_Mode ; 
}

////GPIO��ʼ�� ��Ĭ���ٶ�50M�����������
////����1��GPIO��ţ���Χ��1,2,3,4,5,6,7��
////����2����Ӧ����
u8 get_GPIO_num(GPIO_TypeDef* GPIOx)
{
	if(GPIOx==GPIOA){return 1;}
	else if(GPIOx==GPIOB){return 2;}
	else if(GPIOx==GPIOC){return 3;}
	else if(GPIOx==GPIOD){return 4;}
	else if(GPIOx==GPIOE){return 5;}
	else if(GPIOx==GPIOF){return 6;}
	else if(GPIOx==GPIOG){return 7;}
	return 0;
}

//GPIO��ʼ�� ��Ĭ���ٶ�50M�����������
//����1��GPIO��ţ���Χ��1,2,3,4,5,6,7��
//����2����Ӧ����
void GPIO_Common_Init(GPIO_TypeDef* GPIOx,u16 gpio_pin,GPIOMode_TypeDef GPIO_Mode)
{
	u8 GPIO_num;
	GPIO_InitTypeDef GPIO_InitStructure; 
	GPIO_num=get_GPIO_num(GPIOx);
	RCC_APB2PeriphClockCmd_init(GPIO_num);
	init_gpio_struct(&GPIO_InitStructure,gpio_pin,GPIO_Speed_50MHz,(GPIOMode_TypeDef)GPIO_Mode);
	GPIO_Init(GPIOx, &GPIO_InitStructure); 
}


/*
  * log:

  *	2018��4��6��
	�޸ĳ�ʼ����������
	Programmer:����

  *	2016��7��8��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
