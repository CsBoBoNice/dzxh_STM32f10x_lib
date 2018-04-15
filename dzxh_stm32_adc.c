#include "dzxh_stm32_adc.h"
#include "dzxh_stm32_delay.h"

/*********ʹ�÷���***********************************************************************************/
/*
ע�����޸�adc�������� ADC_PRECISON
@��:	Adc_Init(1,10);		//ADC��ʼ����ͨ��10
		����1��	ѡȡADC	(ȡֵ��Χ��1,2)	
										1	ADC1
										2	ADC2
										
		����2����ʼ��ADCͨ��(ȡֵ��Χ��0��15)
										 ADC ͨ��		 ��ӦIO��
										ADC_Channel_0		PA0
										ADC_Channel_1		PA1
										ADC_Channel_2		PA2
										ADC_Channel_3		PA3
										ADC_Channel_4		PA4
										ADC_Channel_5		PA5
										ADC_Channel_6		PA6
										ADC_Channel_7		PA7
										ADC_Channel_8		PB0
										ADC_Channel_9		PB1
										ADC_Channel_10		PC0
										ADC_Channel_11		PC1
										ADC_Channel_12		PC2
										ADC_Channel_13		PC3
										ADC_Channel_14		PC4
										ADC_Channel_15		PC5

		u16 adcx;
		
@��:	adcx=Get_Adc(ADC_Channel_10,1);	//ȡ��ADC_Channel_10 ADCֵ(��ֵ�ǰٷֱ�ֵ��ȡֵ��Χ0��100)
		����1��ADCͨ��	ȡֵ��Χ��
								ADC_Channel_0 	ѡ�� ADC ͨ�� 0
								ADC_Channel_1 	ѡ�� ADC ͨ�� 1
								ADC_Channel_2 	ѡ�� ADC ͨ�� 2
								ADC_Channel_3 	ѡ�� ADC ͨ�� 3
								ADC_Channel_4 	ѡ�� ADC ͨ�� 4
								ADC_Channel_5 	ѡ�� ADC ͨ�� 5
								ADC_Channel_6 	ѡ�� ADC ͨ�� 6
								ADC_Channel_7 	ѡ�� ADC ͨ�� 7
								ADC_Channel_8 	ѡ�� ADC ͨ�� 8
								ADC_Channel_9 	ѡ�� ADC ͨ�� 9
								ADC_Channel_10 	ѡ�� ADC ͨ�� 10
								ADC_Channel_11 	ѡ�� ADC ͨ�� 11
								ADC_Channel_12 	ѡ�� ADC ͨ�� 12
								ADC_Channel_13 	ѡ�� ADC ͨ�� 13
								ADC_Channel_14 	ѡ�� ADC ͨ�� 14
								ADC_Channel_15 	ѡ�� ADC ͨ�� 15
								ADC_Channel_16 	ѡ�� ADC ͨ�� 16
								ADC_Channel_17 	ѡ�� ADC ͨ�� 17
								
		����2�����������˳��;ȡֵ��Χ 1 �� 16

@��:	adcx=Get_Adc_Average(ADC_Channel_10,1,10);	//����ƽ��ֵ���ADCֵ�����ݸ�׼ȷ(��ֵ�ǰٷֱ�ֵ��ȡֵ��Χ0��100)
		����1��ADCͨ��	ȡֵ��Χ��
								ADC_Channel_0 	ѡ�� ADC ͨ�� 0
								ADC_Channel_1 	ѡ�� ADC ͨ�� 1
								ADC_Channel_2 	ѡ�� ADC ͨ�� 2
								ADC_Channel_3 	ѡ�� ADC ͨ�� 3
								ADC_Channel_4 	ѡ�� ADC ͨ�� 4
								ADC_Channel_5 	ѡ�� ADC ͨ�� 5
								ADC_Channel_6 	ѡ�� ADC ͨ�� 6
								ADC_Channel_7 	ѡ�� ADC ͨ�� 7
								ADC_Channel_8 	ѡ�� ADC ͨ�� 8
								ADC_Channel_9 	ѡ�� ADC ͨ�� 9
								ADC_Channel_10 	ѡ�� ADC ͨ�� 10
								ADC_Channel_11 	ѡ�� ADC ͨ�� 11
								ADC_Channel_12 	ѡ�� ADC ͨ�� 12
								ADC_Channel_13 	ѡ�� ADC ͨ�� 13
								ADC_Channel_14 	ѡ�� ADC ͨ�� 14
								ADC_Channel_15 	ѡ�� ADC ͨ�� 15
								ADC_Channel_16 	ѡ�� ADC ͨ�� 16
								ADC_Channel_17 	ѡ�� ADC ͨ�� 17
								
		����2�����������˳��;ȡֵ��Χ 1 �� 16
		
		����3���ɶ��ٴ�ȡƽ��ֵ����һ����ڶ���ADC���5ms
		

*/
/****************************************************************************************************/

/****************************************************************************************************/

ADC_TypeDef* ADC;
void ADC_Channel_Gpio_init(u16 ADC_channel)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	switch(ADC_channel)
	{
		case 0:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PA0 ��Ϊģ��ͨ��0�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //�ܽ�0
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 1:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PA1 ��Ϊģ��ͨ��1�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       //�ܽ�1
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 2:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PA2 ��Ϊģ��ͨ��2�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;       //�ܽ�2
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 3:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PA3 ��Ϊģ��ͨ��3�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;       //�ܽ�3
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 4:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PA4 ��Ϊģ��ͨ��4�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;       //�ܽ�4
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 5:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PA5 ��Ϊģ��ͨ��5�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       //�ܽ�5
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 6:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PA6 ��Ϊģ��ͨ��6�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;       //�ܽ�6
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 7:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PA7 ��Ϊģ��ͨ��7�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;       //�ܽ�7
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOA, &GPIO_InitStructure);
				break;
		case 8:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PB0 ��Ϊģ��ͨ��8�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //�ܽ�8
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				break;
		case 9:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PB0 ��Ϊģ��ͨ��9�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       //�ܽ�9
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOB, &GPIO_InitStructure);
				break;
		case 10:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PC0 ��Ϊģ��ͨ��10�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       //�ܽ�10
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;	
		case 11:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PC1 ��Ϊģ��ͨ��11�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       //�ܽ�11
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
		case 12:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PC2 ��Ϊģ��ͨ��12�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;       //�ܽ�12
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
		case 13:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PC3 ��Ϊģ��ͨ��13�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;       //�ܽ�13
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
		case 14:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PC4 ��Ϊģ��ͨ��14�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;       //�ܽ�14
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
		case 15:
				RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );	  //ʹ��ADCͨ��ʱ��
				/*PC5 ��Ϊģ��ͨ��15�������� */                       
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;       //�ܽ�15
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;   //����ģʽ
				GPIO_Init(GPIOC, &GPIO_InitStructure);
				break;
	}
}


void  Adc_Init(u8 ADCx,u16 ADC_channel)
{

	ADC_InitTypeDef ADC_InitStructure;
	
	switch(ADCx)
	{
		case 1:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );ADC=ADC1;break;
		case 2:	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE );ADC=ADC2;break;
	
	}
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	ADC_Channel_Gpio_init(ADC_channel);

	ADC_DeInit(ADC);  //��λADC1 

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

  
	ADC_Cmd(ADC, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//����1��Adc_Channel ֵ
//Rank�����������˳��ȡֵ��Χ 1 �� 16
u16 Get_Adc(u8 Adc_Channel,uint8_t Rank)   
{
	u32 temp_val=0;
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC, Adc_Channel, Rank, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC, ADC_FLAG_EOC ));//�ȴ�ת������
	temp_val=ADC_GetConversionValue(ADC);
	temp_val=temp_val * ADC_PRECISON/0x1000;
	return temp_val;	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average(u8 Adc_Channel,uint8_t Rank,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(Adc_Channel,Rank);
		delay_ms(5);
	}
	temp_val=temp_val/times;
	return temp_val;
} 

u16 AD_V[16][3];

/*
AD�������˲�
//����1��Adc_Channel ֵ
//Rank�����������˳��ȡֵ��Χ 1 �� 16

�˲��㷨����λֵƽ���˲������ֳƷ��������ƽ���˷���
*/
u16 Read_ADC(uint8_t Adc_Channel,uint8_t Rank)
{
    u16 ad_valu=0;      //adc����ֵ
    u16 ad_valu_buf[5];
    u16 ad_sum=0;
    int i;
    int n;
    
    for(i=0;i<5;i++)
    {
        ad_valu_buf[i]=Get_Adc(Adc_Channel,Rank);
    }
    
    n = sizeof (ad_valu_buf) / sizeof (ad_valu_buf[0]);	//��������鳤��
    bubble_sort(ad_valu_buf, n);	//����  
    
///*******************���м�3���ֵ**************************************/       
/*******************ȥ�����ֵ��Сֵ���м����ֵ**************************************/   		
    ad_sum=ad_valu_buf[1]+ad_valu_buf[2]+ad_valu_buf[3];
    ad_valu = ad_sum / 3;

        
/*******************����ƽ���˲�**************************************/
    for(i=0;i<3;i++)         //��ÿһ����ǰ�ƶ�һ��λ�ã���ǰ���һ������
    {
        AD_V[Adc_Channel][i] = AD_V[Adc_Channel][i + 1];  
    }  
    
    AD_V[Adc_Channel][2]=ad_valu;//�����µ���ֵ�����������һλ
 
    ad_sum=0;
    for(i=0;i<3;i++)             //������ƽ���˲������ÿһ�������
    {
        ad_sum += AD_V[Adc_Channel][i];
    }
    
    ad_valu=ad_sum / 3;
    ad_sum = 0; 
    
    return ad_valu;
}

void bubble_sort(u16 *a, int n)  //ð������
{
    int i, j;
    u16 temp;
    for (j = 0; j < n - 1; j++)
        for (i = 0; i < n - 1 - j; i++)
        {
            if(a[i] > a[i + 1])
            {
                temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
}

/*
  * log:

  *	2018��4��7��
	��������λֵƽ���˲���
	��Ĭ�ϵ� ADC_SampleTime_55Cycles5 �ĳ���ADC_SampleTime_239Cycles5 ����˾���
	��dzxh_stm32_adc.h�п����޸�adc����
	Programmer:����

  *	2016��7��9��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
