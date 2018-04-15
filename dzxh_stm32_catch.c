#include "dzxh_stm32_catch.h"
//#define TIM2_IRQHandler_ENABLE
//#define TIM3_IRQHandler_ENABLE
//#define TIM4_IRQHandler_ENABLE
//#define TIM5_IRQHandler_ENABLE

/******ʹ�÷���******************************************************************/
/*
(Ĭ�ϣ�����͵�ƽʱ��)

(ע�⣺ʹ��ǰ����Ӧ���жϴ򿪣�ֻ�轫�����Ӧ���ж�ʹ��(#define TIM2_IRQHandler_ENABLE)//ע��ȥ������)

@��:	Get_catch(5,1);	//��������ֵΪ����͵�ƽʱ��
		����1��ѡ�ö�ʱ�� ȡֵ��Χ��2,3,4,5��
									2	TIM2
									3	TIM3
									4	TIM4
									5	TIM5
		����2����ʱ��ͨ��(��Χ 1,2,3,4,)


@��:	TIM_Catch_Init(5,1,0,0,3);	//��ʼ�����벶��
		����1��ѡ�ö�ʱ�� ȡֵ��Χ��2,3,4,5��
									2	TIM2
									3	TIM3
									4	TIM4
									5	TIM5
		����2����ʱ��ͨ��(��Χ 1,2,3,4,)
		����3���Ƿ���ӳ��
		����4����Ӧ�������ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��
		����5����Ӧ��Ӧ���ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��

��ʱ��	������ӳ��		ͨ��	1	  2	   3	4

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
/********************************************************************************/

uint8_t  TIM2CH1_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM2CH1_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM2CH2_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM2CH2_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM2CH3_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM2CH3_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM2CH4_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM2CH4_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM3CH1_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM3CH1_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM3CH2_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM3CH2_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM3CH3_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM3CH3_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM3CH4_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM3CH4_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM4CH1_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM4CH1_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM4CH2_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM4CH2_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM4CH3_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM4CH3_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM4CH4_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM4CH4_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM5CH1_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM5CH1_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM5CH2_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM5CH2_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM5CH3_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM5CH3_CAPTURE_VAL;	//���벶��ֵ

uint8_t  TIM5CH4_CAPTURE_STA=0;	//���벶��״̬		    				
uint16_t	TIM5CH4_CAPTURE_VAL;	//���벶��ֵ

uint32_t Get_catch(u8 TIM,u16 TIM_channel)
{
	uint32_t temp=0;
	if(TIM==2)
	{
		switch(TIM_channel)
		{
			case 1:	if(TIM2CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM2CH1_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM2CH1_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM2CH1_CAPTURE_STA=0;//������һ�β���
					}break;
			case 2:	if(TIM2CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM2CH2_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM2CH2_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM2CH2_CAPTURE_STA=0;//������һ�β���
					}break;
			case 3:	if(TIM2CH3_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM2CH3_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM2CH4_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM2CH4_CAPTURE_STA=0;//������һ�β���
					}break;
			case 4:	if(TIM2CH4_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM2CH4_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM2CH4_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM2CH4_CAPTURE_STA=0;//������һ�β���
					}break;
		}
	}

	if(TIM==3)
	{
		switch(TIM_channel)
		{
			case 1:	if(TIM3CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM3CH1_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM3CH1_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM3CH1_CAPTURE_STA=0;//������һ�β���
					}break;
			case 2:	if(TIM3CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM3CH2_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM3CH2_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM3CH2_CAPTURE_STA=0;//������һ�β���
					}break;
			case 3:	if(TIM3CH3_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM3CH3_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM3CH4_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM3CH4_CAPTURE_STA=0;//������һ�β���
					}break;
			case 4:	if(TIM3CH4_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM3CH4_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM3CH4_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM3CH4_CAPTURE_STA=0;//������һ�β���
					}break;
		}
	}

	if(TIM==4)
	{
		switch(TIM_channel)
		{
			case 1:	if(TIM4CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM4CH1_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM4CH1_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM4CH1_CAPTURE_STA=0;//������һ�β���
					}break;
			case 2:	if(TIM4CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM4CH2_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM4CH2_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM4CH2_CAPTURE_STA=0;//������һ�β���
					}break;
			case 3:	if(TIM4CH3_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM4CH3_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM4CH4_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM4CH4_CAPTURE_STA=0;//������һ�β���
					}break;
			case 4:	if(TIM4CH4_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM4CH4_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM4CH4_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM4CH4_CAPTURE_STA=0;//������һ�β���
					}break;
		}
	}

	if(TIM==5)
	{
		switch(TIM_channel)
		{
			case 1:	if(TIM5CH1_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM5CH1_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM5CH1_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM5CH1_CAPTURE_STA=0;//������һ�β���
					}break;
			case 2:	if(TIM5CH2_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM5CH2_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM5CH2_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM5CH2_CAPTURE_STA=0;//������һ�β���
					}break;
			case 3:	if(TIM5CH3_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM5CH3_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM5CH3_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM5CH3_CAPTURE_STA=0;//������һ�β���
					}break;
			case 4:	if(TIM5CH4_CAPTURE_STA&0X80)//�ɹ�������һ��������
					{
						temp=TIM5CH4_CAPTURE_STA&0X3F;
						temp*=65536;//���ʱ���ܺ�
						temp+=TIM5CH4_CAPTURE_VAL;//�õ��ܵĵ͵�ƽʱ��
						TIM5CH4_CAPTURE_STA=0;//������һ�β���
					}break;
		}
	}
	return temp;
}


#ifdef TIM2_IRQHandler_ENABLE
void TIM2_IRQHandler(void)
{
	if((TIM2CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM2CH1_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM2CH1_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM2CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH1_CAPTURE_VAL=0XFFFF;
				}else TIM2CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)//����1���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM2CH1_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM2CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM2CH1_CAPTURE_VAL=TIM_GetCapture1(TIM2);//��� TIMx ���벶�� 1 ��ֵ
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Falling); //CC1P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 1 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH1_CAPTURE_STA=0;			//���
				TIM2CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//���� TIMx �������Ĵ���ֵ
				TIM2CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM2,TIM_ICPolarity_Rising);		//CC1P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM2CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM2CH2_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM2CH2_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM2CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH2_CAPTURE_VAL=0XFFFF;
				}else TIM2CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)//����2���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM2CH2_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM2CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM2CH2_CAPTURE_VAL=TIM_GetCapture2(TIM2);//��� TIMx ���벶�� 2 ��ֵ
		   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Falling); //CC2P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 2 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH2_CAPTURE_STA=0;			//���
				TIM2CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//���� TIMx �������Ĵ���ֵ
				TIM2CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC2PolarityConfig(TIM2,TIM_ICPolarity_Rising);		//CC2P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM2CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM2CH3_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM2CH3_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM2CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH3_CAPTURE_VAL=0XFFFF;
				}else TIM2CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)//����3���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM2CH3_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM2CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM2CH3_CAPTURE_VAL=TIM_GetCapture3(TIM2);//��� TIMx ���벶�� 3 ��ֵ
		   		TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Falling); //CC3P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 3 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH3_CAPTURE_STA=0;			//���
				TIM2CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//���� TIMx �������Ĵ���ֵ
				TIM2CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC3PolarityConfig(TIM2,TIM_ICPolarity_Rising);		//CC3P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM2CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM2CH4_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM2CH4_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM2CH4_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM2CH4_CAPTURE_VAL=0XFFFF;
				}else TIM2CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)//����4���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM2CH4_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM2CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM2CH4_CAPTURE_VAL=TIM_GetCapture4(TIM2);//��� TIMx ���벶�� 4 ��ֵ
		   		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Falling); //CC4P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 4 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM2CH4_CAPTURE_STA=0;			//���
				TIM2CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM2,0);//���� TIMx �������Ĵ���ֵ
				TIM2CH4_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC4PolarityConfig(TIM2,TIM_ICPolarity_Rising);		//CC4P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

    TIM_ClearITPendingBit(TIM2, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ
}
#endif /* TIM2_IRQHandler_ENABLE */

#ifdef TIM3_IRQHandler_ENABLE
void TIM3_IRQHandler(void)
{
	if((TIM3CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM3CH1_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM3CH1_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM3CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH1_CAPTURE_VAL=0XFFFF;
				}else TIM3CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)//����1���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM3CH1_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM3CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM3CH1_CAPTURE_VAL=TIM_GetCapture1(TIM3);//��� TIMx ���벶�� 1 ��ֵ
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC1P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 1 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH1_CAPTURE_STA=0;			//���
				TIM3CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);//���� TIMx �������Ĵ���ֵ
				TIM3CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC1P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM3CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM3CH2_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM3CH2_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM3CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH2_CAPTURE_VAL=0XFFFF;
				}else TIM3CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)//����2���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM3CH2_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM3CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM3CH2_CAPTURE_VAL=TIM_GetCapture2(TIM3);//��� TIMx ���벶�� 2 ��ֵ
		   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC2P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 2 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH2_CAPTURE_STA=0;			//���
				TIM3CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);//���� TIMx �������Ĵ���ֵ
				TIM3CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC2PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC2P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM3CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM3CH3_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM3CH3_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM3CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH3_CAPTURE_VAL=0XFFFF;
				}else TIM3CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)//����3���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM3CH3_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM3CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM3CH3_CAPTURE_VAL=TIM_GetCapture3(TIM3);//��� TIMx ���벶�� 3 ��ֵ
		   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC3P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 3 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH3_CAPTURE_STA=0;			//���
				TIM3CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);//���� TIMx �������Ĵ���ֵ
				TIM3CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC3PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC3P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM3CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM3CH4_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM3CH4_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM3CH4_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM3CH4_CAPTURE_VAL=0XFFFF;
				}else TIM3CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)//����4���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM3CH4_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM3CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM3CH4_CAPTURE_VAL=TIM_GetCapture4(TIM3);//��� TIMx ���벶�� 4 ��ֵ
		   		TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Falling); //CC4P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 4 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3CH4_CAPTURE_STA=0;			//���
				TIM3CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM3,0);//���� TIMx �������Ĵ���ֵ
				TIM3CH4_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC4PolarityConfig(TIM3,TIM_ICPolarity_Rising);		//CC4P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ
}
#endif /* TIM3_IRQHandler_ENABLE */

#ifdef TIM4_IRQHandler_ENABLE
void TIM4_IRQHandler(void)
{
	if((TIM4CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM4CH1_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM4CH1_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM4CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM4CH1_CAPTURE_VAL=0XFFFF;
				}else TIM4CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)//����1���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM4CH1_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM4CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM4CH1_CAPTURE_VAL=TIM_GetCapture1(TIM4);//��� TIMx ���벶�� 1 ��ֵ
		   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC1P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 1 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM4CH1_CAPTURE_STA=0;			//���
				TIM4CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);//���� TIMx �������Ĵ���ֵ
				TIM4CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC1P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM4CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM4CH2_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM4CH2_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM4CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM4CH2_CAPTURE_VAL=0XFFFF;
				}else TIM4CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)//����2���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM4CH2_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM4CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM4CH2_CAPTURE_VAL=TIM_GetCapture2(TIM4);//��� TIMx ���벶�� 2 ��ֵ
		   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC2P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 2 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM4CH2_CAPTURE_STA=0;			//���
				TIM4CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);//���� TIMx �������Ĵ���ֵ
				TIM4CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC2PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC2P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM4CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM4CH3_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM4CH3_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM4CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM4CH3_CAPTURE_VAL=0XFFFF;
				}else TIM4CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)//����3���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM4CH3_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM4CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM4CH3_CAPTURE_VAL=TIM_GetCapture3(TIM4);//��� TIMx ���벶�� 3 ��ֵ
		   		TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC3P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 3 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM4CH3_CAPTURE_STA=0;			//���
				TIM4CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);//���� TIMx �������Ĵ���ֵ
				TIM4CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC3PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC3P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM4CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM4CH4_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM4CH4_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM4CH4_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM4CH4_CAPTURE_VAL=0XFFFF;
				}else TIM4CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)//����4���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM4CH4_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM4CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM4CH4_CAPTURE_VAL=TIM_GetCapture4(TIM4);//��� TIMx ���벶�� 4 ��ֵ
		   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Falling); //CC4P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 4 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM4CH4_CAPTURE_STA=0;			//���
				TIM4CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM4,0);//���� TIMx �������Ĵ���ֵ
				TIM4CH4_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC4PolarityConfig(TIM4,TIM_ICPolarity_Rising);		//CC4P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

    TIM_ClearITPendingBit(TIM4, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ
}
#endif /* TIM4_IRQHandler_ENABLE */

#ifdef TIM5_IRQHandler_ENABLE
void TIM5_IRQHandler(void)
{
	if((TIM5CH1_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM5CH1_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM5CH1_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM5CH1_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH1_CAPTURE_VAL=0XFFFF;
				}else TIM5CH1_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)//����1���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM5CH1_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM5CH1_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM5CH1_CAPTURE_VAL=TIM_GetCapture1(TIM5);//��� TIMx ���벶�� 1 ��ֵ
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Falling); //CC1P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 1 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH1_CAPTURE_STA=0;			//���
				TIM5CH1_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);//���� TIMx �������Ĵ���ֵ
				TIM5CH1_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC1PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC1P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM5CH2_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM5CH2_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM5CH2_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM5CH2_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH2_CAPTURE_VAL=0XFFFF;
				}else TIM5CH2_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)//����2���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM5CH2_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM5CH2_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM5CH2_CAPTURE_VAL=TIM_GetCapture2(TIM5);//��� TIMx ���벶�� 2 ��ֵ
		   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Falling); //CC2P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 2 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH2_CAPTURE_STA=0;			//���
				TIM5CH2_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);//���� TIMx �������Ĵ���ֵ
				TIM5CH2_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC2PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC2P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM5CH3_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM5CH3_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM5CH3_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM5CH3_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH3_CAPTURE_VAL=0XFFFF;
				}else TIM5CH3_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)//����3���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM5CH3_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM5CH3_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM5CH3_CAPTURE_VAL=TIM_GetCapture3(TIM5);//��� TIMx ���벶�� 3 ��ֵ
		   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Falling); //CC3P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 3 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH3_CAPTURE_STA=0;			//���
				TIM5CH3_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);//���� TIMx �������Ĵ���ֵ
				TIM5CH3_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC3PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC3P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

	if((TIM5CH4_CAPTURE_STA&0X80)==0)//��δ�ɹ�����	
	{	  
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)	//TIM_IT_Update TIM �ж�Դ
		 
		{	    
			if(TIM5CH4_CAPTURE_STA&0X40)//�Ѿ����񵽵͵�ƽ��
			{
				if((TIM5CH4_CAPTURE_STA&0X3F)==0X3F)//�͵�ƽ̫����
				{
					TIM5CH4_CAPTURE_STA|=0X80;//��ǳɹ�������һ��
					TIM5CH4_CAPTURE_VAL=0XFFFF;
				}else TIM5CH4_CAPTURE_STA++;
			}	 
		}
		if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)//����4���������¼�	���ָ���� TIM �жϷ������
		{	
			if(TIM5CH4_CAPTURE_STA&0X40)		//����һ�������� 		
			{	  			
				TIM5CH4_CAPTURE_STA|=0X80;		//��ǳɹ�����һ�ε͵�ƽ����
				TIM5CH4_CAPTURE_VAL=TIM_GetCapture4(TIM5);//��� TIMx ���벶�� 4 ��ֵ
		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Falling); //CC4P=0 ����Ϊ�½��ز���
																	//���� TIMx ͨ�� 4 ����
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM5CH4_CAPTURE_STA=0;			//���
				TIM5CH4_CAPTURE_VAL=0;
	 			TIM_SetCounter(TIM5,0);//���� TIMx �������Ĵ���ֵ
				TIM5CH4_CAPTURE_STA|=0X40;		//��ǲ�����������
		   		TIM_OC4PolarityConfig(TIM5,TIM_ICPolarity_Rising);		//CC4P=1 ����Ϊ�����ز���
															/*TIM_ICPolarity_Rising TIM ���벶��������
																TIM_ICPolarity_Falling TIM ���벶���½���			
															*/
			}		    
		}			     	    					   
 	}

    TIM_ClearITPendingBit(TIM5, TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4|TIM_IT_Update); //����жϱ�־λ
}
#endif /* TIM5_IRQHandler_ENABLE */


void TIM2_CATCH_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;	
		}
	}

	if(remap_pwm==1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2, ENABLE); //TIM2 ���ù��ܲ���ӳ��1
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;	
		}		
	}
	
	if(remap_pwm==2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE); //TIM2 ���ù��ܲ���ӳ��2
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}		
	}

	if(remap_pwm==3)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); //TIM2 ���ù�����ȫӳ��
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_11;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}		
	}	
}
void TIM3_CATCH_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;		
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;		
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
						GPIO_Init(GPIOA,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}
	}

	if(remap_pwm==1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); //TIM3 ���ù��ܲ���ӳ��
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;		
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_4;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
						GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}		
	}
	
	if(remap_pwm==2)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE); //TIM3 ���ù�����ȫӳ��
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;		
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		switch(TIM_channel)
		{
				case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
						GPIO_Init(GPIOC,&GPIO_InitStruct);break;
				case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
						GPIO_Init(GPIOC,&GPIO_InitStruct);break;
				case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
						GPIO_Init(GPIOC,&GPIO_InitStruct);break;
				case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
						GPIO_Init(GPIOC,&GPIO_InitStruct);break;	
		}
	}
}
void TIM4_CATCH_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;		
		switch(TIM_channel)
		{
			case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
					GPIO_Init(GPIOB,&GPIO_InitStruct);break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
					GPIO_Init(GPIOB,&GPIO_InitStruct);break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
					GPIO_Init(GPIOB,&GPIO_InitStruct);break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
					GPIO_Init(GPIOB,&GPIO_InitStruct);break;	
		}		
	}

	if(remap_pwm==1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_AFIO,ENABLE);
		GPIO_PinRemapConfig(GPIO_Remap_TIM4, ENABLE); //TIM4 ���ù���ӳ��
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;		
		switch(TIM_channel)
		{
			case 1:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12;
					GPIO_Init(GPIOD,&GPIO_InitStruct);break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_13;
					GPIO_Init(GPIOD,&GPIO_InitStruct);break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_14;
					GPIO_Init(GPIOD,&GPIO_InitStruct);break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_15;
					GPIO_Init(GPIOD,&GPIO_InitStruct);break;	
		}		
	}
}
void TIM5_CATCH_GPIO_Init(u16 TIM_channel,u8 remap_pwm)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);		//ʹ��TIM5
	if(remap_pwm==0)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IPU;		//�����������	
//		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
		
		switch(TIM_channel)
		{
			case 1:	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					GPIO_ResetBits(GPIOA,GPIO_Pin_0);//PA0 ����
					break;
			case 2:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					GPIO_ResetBits(GPIOA,GPIO_Pin_1);//PA1 ����				
					break;
			case 3:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					GPIO_ResetBits(GPIOA,GPIO_Pin_2);//PA2 ����
					break;
			case 4:GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
					GPIO_Init(GPIOA,&GPIO_InitStruct);
					GPIO_ResetBits(GPIOA,GPIO_Pin_3);//PA3 ����			
			break;	
		}
	}

}

void TIM_CATCH_Gpio_init(u8 TIMx,u16 TIM_channel,u8 remap_pwm)
{
	switch(TIMx)
	{
		case 2:TIM2_CATCH_GPIO_Init(TIM_channel,remap_pwm);break;
		case 3:TIM3_CATCH_GPIO_Init(TIM_channel,remap_pwm);break;
		case 4:TIM4_CATCH_GPIO_Init(TIM_channel,remap_pwm);break;
		case 5:TIM5_CATCH_GPIO_Init(TIM_channel,remap_pwm);break;		
	}
}
TIM_TypeDef* get_CATCH_num(u8 TIMx)
{
	switch(TIMx)
	{
		case 2:return TIM2;
		case 3:return TIM3;
		case 4:return TIM4;
		case 5:return TIM5;		
	}
	return 0;
}


void TIM_Catch_Init(u8 TIMx,u16 TIM_channel,u8 remap_pwm,uint8_t PreemptionPriority,uint8_t SubPriority)
{
	TIM_TypeDef* TIM;
    uint16_t channel;
	NVIC_InitTypeDef NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;	
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	TIM=get_CATCH_num(TIMx);
	TIM_CATCH_Gpio_init(TIMx,TIM_channel,remap_pwm);


	
	    //��������Զ�װ�صļ���ֵ�����ڼ����Ǵ�0��ʼ�ģ�����10000�κ�Ϊ9999
    TIM_TimeBaseStructure.TIM_Period =65535;
    // �������Ԥ��Ƶϵ����������Ϊ0ʱ��ʾ����Ƶ����Ҫ��1
    TIM_TimeBaseStructure.TIM_Prescaler = (72 - 1);
    // �߼�Ӧ�ñ��β��漰�������ڶ�ʱ��ʱ��(CK_INT)Ƶ���������˲���(ETR,TIx)
    // ʹ�õĲ���Ƶ��֮��ķ�Ƶ����
    TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;
    //���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    //��ʼ����ʱ��5
    TIM_TimeBaseInit(TIM, &TIM_TimeBaseStructure);

    /* Clear TIM5 update pending flag[���TIM5����жϱ�־] */

	switch(TIM_channel)
	{
		case 1:channel=TIM_Channel_1;break;
		case 2:channel=TIM_Channel_2;break;
		case 3:channel=TIM_Channel_3;break;
		case 4:channel=TIM_Channel_4;break;		
	}
		//��ʼ��TIM5���벶�����
	TIM_ICInitStructure.TIM_Channel = channel; //CC1S=01 	ѡ������� IC1ӳ�䵽TI1��
  	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;	//�����ز���
  	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //ӳ�䵽TI1��
  	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;	 //���������Ƶ,����Ƶ 
  	TIM_ICInitStructure.TIM_ICFilter = 0x00;//IC1F=0000 ���������˲��� ���˲�
  	TIM_ICInit(TIM, &TIM_ICInitStructure);
    /* TIM5 enable counter */
    TIM_Cmd(TIM, ENABLE);  //������ʹ�ܣ���ʼ����

 
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 
#ifdef STM32F10X_MD
	switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;break;     
    }
#endif /* STM32F10X_MD */
	
#ifdef STM32F10X_HD
	switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;break;
        case 5:NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ;break;      
    }
#endif /* STM32F10X_HD */

#ifdef STM32F10X_CL
	switch(TIMx)
    {
        case 2:NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ;break;
        case 3:NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn ;break;
        case 4:NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;break;
        case 5:NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn ;break;      
    }
#endif /* STM32F10X_CL */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure);
	switch(TIM_channel)
	{
		case 1:	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC1,ENABLE);//��������ж� ,����CC1IE�����ж�
				break;
		case 2:	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC2,ENABLE);//��������ж� ,����CC1IE�����ж�
				break;
		case 3:	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC3,ENABLE);//��������ж� ,����CC1IE�����ж�
				break;
		case 4:	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�
				break;		
	}
//	TIM_ITConfig(TIM,TIM_IT_Update|TIM_IT_CC1|TIM_IT_CC2|TIM_IT_CC3|TIM_IT_CC4,ENABLE);//��������ж� ,����CC1IE�����ж�
	
}
/*
  * log:

  *	2016��7��12��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

