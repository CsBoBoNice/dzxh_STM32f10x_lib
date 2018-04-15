#include "dzxh_stm32_dac.h"
/************************************************************************************************************/
/*
@��:	Dac_Init(1);	//DAC��ʼ��

		����1��ѡ��DACͨ��	(ȡֵ��Χ��1,2)
								1	ADC1	PA4
								2	ADC2	PA5
		
@��:	Dac_Set_Vol(1,2600);	//����ͨ�������ѹ

		����1��ѡ��DACͨ��	(ȡֵ��Χ��1,2)
		
		����2������ͨ�������ѹ	ȡֵ��Χ��0~3300,���� 0~3.3V

*/
/************************************************************************************************************/
void Dac_Init(u8 DACx)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
   	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	switch(DACx)
	{
		case 1:	
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
					GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 �����
									
					DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
					DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
					DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
					DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
					DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

					DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
				  
					DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ
		
		case 2 :	
					GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;				 // �˿�����
					GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
					GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
					GPIO_Init(GPIOA, &GPIO_InitStructure);
					GPIO_SetBits(GPIOA,GPIO_Pin_5)	;//PA.4 �����
									
					DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
					DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
					DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
					DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC2�������ر� BOFF1=1
					DAC_Init(DAC_Channel_2,&DAC_InitType);	 //��ʼ��DACͨ��1

					DAC_Cmd(DAC_Channel_2, ENABLE);  //ʹ��DAC2
				  
					DAC_SetChannel2Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ
	}	
}


//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac_Set_Vol(u8 DACx,u16 vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	switch(DACx)
	{
		case 1:	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
		
		case 2:	DAC_SetChannel2Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
	}

}
/*
  * log:

  *	2016��7��7��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
