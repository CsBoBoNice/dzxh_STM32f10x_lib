#include "dzxh_stm32_iwdg.h"

/*******ʹ�÷���***********************************************************/
/*

@��:	IWDG_Init(IWDG_Prescaler_256,4095);	// 26208ms	���Ź���λʱ��
@��:	IWDG_Feed();//ι�������Ź�

	
*/
/*************************************************************************/


//��ʼ���������Ź�
//IWDG_Prescaler:��Ƶ��:0~6(ֻ�е�3λ��Ч!)
//��Ƶ����=4*2^IWDG_Prescaler.�����ֵֻ����256!
//Reload:��װ�ؼĴ���ֵ:��11λ��Ч.
//ʱ�����(���):Tout=((4*2^IWDG_Prescaler)*Reload)/40 (ms).

/*		IWDG_Prescaler(0 to 6)
  *   This parameter can be one of the following values:
  *     0 @arg IWDG_Prescaler_4: IWDG prescaler set to 4
  *     1 @arg IWDG_Prescaler_8: IWDG prescaler set to 8
  *     2 @arg IWDG_Prescaler_16: IWDG prescaler set to 16
  *     3 @arg IWDG_Prescaler_32: IWDG prescaler set to 32
  *     4 @arg IWDG_Prescaler_64: IWDG prescaler set to 64
  *     5 @arg IWDG_Prescaler_128: IWDG prescaler set to 128
  *     6 @arg IWDG_Prescaler_256: IWDG prescaler set to 256
*/
/*		Reload(0 to 4095)
  *   This parameter must be a number between 0 and 0x0FFF.
*/

/*
IWDG_Init(IWDG_Prescaler_64,625)	//1000ms���Ź���λʱ��

IWDG_Init(IWDG_Prescaler_4,4095);	// 409.5ms	���Ź���λʱ��
IWDG_Init(IWDG_Prescaler_8,4095);	// 819ms	���Ź���λʱ��
IWDG_Init(IWDG_Prescaler_16,4095);	// 1538ms	���Ź���λʱ��
IWDG_Init(IWDG_Prescaler_32,4095);	// 3276ms	���Ź���λʱ��
IWDG_Init(IWDG_Prescaler_64,4095);	// 6552ms	���Ź���λʱ��
IWDG_Init(IWDG_Prescaler_128,4095);	// 13104ms	���Ź���λʱ��
IWDG_Init(IWDG_Prescaler_256,4095);	// 26208ms	���Ź���λʱ��
*/
void IWDG_Init(uint8_t IWDG_Prescaler,uint16_t Reload) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //ʹ�ܶԼĴ���IWDG_PR��IWDG_RLR��д����
	
	IWDG_SetPrescaler(IWDG_Prescaler);  //����IWDGԤ��Ƶֵ:����IWDGԤ��ƵֵΪ64
	
	IWDG_SetReload(Reload);  //����IWDG��װ��ֵ
	
	IWDG_ReloadCounter();  //����IWDG��װ�ؼĴ�����ֵ��װ��IWDG������
	
	IWDG_Enable();  //ʹ��IWDG
}
//ι�������Ź�
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();//reload										   
}

/*
  * log:

  *	2018��4��6��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
