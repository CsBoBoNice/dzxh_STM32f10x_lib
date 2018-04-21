#include "dzxh_stm32_usart.h"
#include "include.h"
/******ʹ�÷���****************************************************************************************************/
/*

@��:	USART_SendByte(USART1,c);	//����һ���ַ���
		����1��USART_TypeDef* ��
					USART1
					USART2
					USART3
					UART4
					UART5
		����2��unsigned char ������
		
@��:	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//����һ������

		����1��USART_TypeDef* ��
					USART1
					USART2
					USART3
					UART4
					UART5
		����2��unsigned char ��ָ��
		����3�����ݸ���

@��:	USART_init(1,115200,0,3,0);	//���ڳ�ʼ��

		����1��USART��ţ���Χ��1,2,3,4,5��
								1	USART1
								2	USART2
								3	USART3
								4	UART4
								5	UART5
										
	����2��������ȡֵ��Χ(600,1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,230400,460800)
	
	����3����Ӧ�������ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��

	����4����Ӧ��Ӧ���ȼ�����		ȡֵ��Χ(0,1,2,3)	��ֵԽ�����ȼ�Խ��
	
	����5��������ӳ��	(��Χ �ο��±�)
��������:
����		������ӳ��		TX		RX
USART1		0 û��ӳ��		PA9		PA10
			1 ��ȫ��ӳ��	PB6		PB7

USART2		0 û��ӳ��		PA2		PA3
			1 ��ȫ��ӳ��	PD5		PD6 

USART3		0 û��ӳ��		PB10	PB11
			1 ������ӳ��1	PC10	PC11
			2 ������ӳ��2	PD8		PD9
			
UART4		0 û��ӳ��		PC10	PC11

UART5		0 û��ӳ��		PC12	PD2

************************************************************************
@ע:

	���մ�������ͨ���жϽ��գ�ͨ���δ��ж� SysTick_Handler�ж��Ƿ�ʱ��
��dzxh_stm32_usart.h�����ó�ʱʱ�䣬����ջ�������С,���δ�õ��Ĵ��ڿ���ע�ͣ���Լ�ڴ棬
������Ҫ�δ��жϣ�������Ҫ��ʼ���δ��ж�

	��Ȼ�������ϣ���õδ�ʱ�����Ը���TIM��ʱ��,ֻ��Ҫ�ڶ�ʱ���жϺ����м���
�����жϴ���������	USART_ReceiveOvertimeProcess();

����Ϊ�δ�ʱ����ӳ�ʱ�㷨�Ĵ���:
void SysTick_Handler(void)
{
	#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
	USART_ReceiveOvertimeProcess();
	#endif
}

�жϴ���������д�� stm32f10x_it.c�ļ���:
������ʹ�ó�ʱ������жϴ�����:
void USART1_IRQHandler(void)
{
	#ifdef USING_USART1
	USART1_ISR();
	#endif
}

void USART2_IRQHandler(void)
{
	#ifdef USING_USART2
	USART2_ISR();
	#endif
}

void USART3_IRQHandler(void)
{
	#ifdef USING_USART3
	USART3_ISR();
	#endif
}
//void UART4_IRQHandler(void)
//{
//	#ifdef USING_UART4
//	UART4_ISR();
//	#endif
//}

//void UART5_IRQHandler(void)
//{
//	#ifdef USING_UART5
//	UART5_ISR();
//	#endif
//}

������ʹ�ô���ʱ�Ĵ��ڽ��մ���

NVIC_Configuration();//�������ȼ����飺�������ȼ�����Ӧ���ȼ�
SysTick_delay_init();	//��ʼ��SysTick��ʱ���ж� ÿ1/configTICK_RATE_HZ���ж�һ��
USART_init(1,115200,0,3,0);	//���ڳ�ʼ��

if(USART1_ready_buf_ok)	//�жϳ�ʱ��һ֡���ݽ��ճɹ�
{
	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//�ط�
	USART1_ready_buf_ok = 0;
}

USART1_ready_buf ���յ�������
USART1_ready_buf_len �������ݳ���

*/
/******************************************************************************************************************/
USART_TypeDef* USART_printf;

#ifdef USING_USART1
uint8_t USART1_receive_buf[USART1_BUF_SIZE];	//���ݽ��ջ�����
uint8_t USART1_ready_buf[USART1_BUF_SIZE];		//���ճɹ����������
static int32_t USART1_ReceiveTimeCounter = 0;	//��ʱʣ��ʱ��
__IO uint16_t USART1_receive_index=0; 		//���ڽ��յ����ݳ���
__IO uint8_t USART1_ready_buf_ok = 0;		//�Ƿ�ɹ�����
__IO uint16_t USART1_ready_buf_len = 0;		//�ɹ����պ�����ݳ���
#endif

#ifdef USING_USART2
uint8_t USART2_receive_buf[USART2_BUF_SIZE],USART2_ready_buf[USART2_BUF_SIZE];
static int32_t USART2_ReceiveTimeCounter = 0;
__IO uint16_t USART2_receive_index=0; 
__IO uint8_t USART2_ready_buf_ok = 0;
__IO uint16_t USART2_ready_buf_len=0;
#endif

#ifdef USING_USART3
static int32_t USART3_ReceiveTimeCounter = 0;
uint8_t USART3_receive_buf[USART3_BUF_SIZE],USART3_ready_buf[USART3_BUF_SIZE];
__IO uint16_t USART3_receive_index=0; 
__IO uint8_t USART3_ready_buf_ok = 0;
__IO uint16_t USART3_ready_buf_len=0;
#endif

#ifdef USING_UART4
uint8_t UART4_receive_buf[UART4_BUF_SIZE],UART4_ready_buf[UART4_BUF_SIZE];
static int32_t UART4_ReceiveTimeCounter = 0;
__IO uint16_t UART4_receive_index=0; 
__IO uint8_t UART4_ready_buf_ok = 0;
__IO uint16_t UART4_ready_buf_len=0;
#endif

#ifdef USING_UART5
uint8_t UART5_receive_buf[USART1_BUF_SIZE],UART5_ready_buf[UART5_BUF_SIZE];
static int32_t UART5_ReceiveTimeCounter = 0;
__IO uint16_t UART5_receive_index=0; 
__IO uint8_t UART5_ready_buf_ok = 0;
__IO uint16_t UART5_ready_buf_len=0;
#endif

/**********************�жϺ���***************************************************************************************************/

/**********************����1�жϽ���һ���ַ�***************************************************************************************************/
/*
���жϷ�������У�����������Ӧ�ж�ʱ����֪�����ĸ��ж�Դ�����ж�����
��˱������жϷ�������ж��ж�Դ�����б�Ȼ��ֱ���д���
��Ȼ�����ֻ�漰��һ���ж������ǲ����������б�ġ���������ʲô������������б��Ǹ���ϰ��
*/
#ifdef USING_USART1
void USART1_ISR(void)   
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//�ж��Ƿ����ж�
	{
		USART1_ReceiveTimeCounter = USART1_RECEIVE_OVERTIME;

		if(USART1_receive_index >= USART1_BUF_SIZE)//������λ��Խ�磬��ô��ͷ��ʼ���
			USART1_receive_index = 0;
		
		USART1_receive_buf[USART1_receive_index++] = (uint8_t)USART_ReceiveData(USART1);//�����ַ�����λ�ü�1		
	}	
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//���ش���ֻҪ��״̬�Ĵ��������ݼĴ����Ϳ��Զ�����˱�־
	{
		(void)USART_ReceiveData(USART1);
	}

} 
#endif

#ifdef USING_USART2
void USART2_ISR(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //�ж��Ƿ����ж�
	{	
		USART2_ReceiveTimeCounter = USART2_RECEIVE_OVERTIME;
		
		if(USART2_receive_index >= USART2_BUF_SIZE)	//������λ��Խ�磬��ô��ͷ��ʼ���
			USART2_receive_index = 0;
		
		USART2_receive_buf[USART2_receive_index++] = (uint8_t)USART_ReceiveData(USART2);//�����ַ�����λ�ü�1
		
	}		
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//���ش���ֻҪ��״̬�Ĵ��������ݼĴ����Ϳ��Զ�����˱�־
	{
		(void)USART_ReceiveData(USART2);
	}
}
#endif

#ifdef USING_USART3
void USART3_ISR(void)
{
	if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
	{
		USART3_ReceiveTimeCounter = USART3_RECEIVE_OVERTIME;
		if(USART3_receive_index >= USART3_BUF_SIZE)
			USART3_receive_index = 0;
		
		USART3_receive_buf[USART3_receive_index++] = (uint8_t)USART_ReceiveData(USART3);
		
	}
		
	if (USART_GetFlagStatus(USART3, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(USART3);
	}
}
#endif

#ifdef USING_UART4
void USART4_ISR(void)
{
	if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
	{
		UART4_ReceiveTimeCounter = UART4_RECEIVE_OVERTIME;
		if(UART4_receive_index >= UART4_BUF_SIZE)
			UART4_receive_index = 0;
		
		UART4_receive_buf[UART4_receive_index++] = (uint8_t)USART_ReceiveData(UART4);
		
	}
		
	if (USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(UART4);
	}
}
#endif

#ifdef USING_UART5
void USART5_ISR(void)
{
	if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
	{		
		UART5_ReceiveTimeCounter = UART5_RECEIVE_OVERTIME;
		if(UART5_receive_index >= UART5_BUF_SIZE)
			UART5_receive_index = 0;
		
		UART5_receive_buf[UART5_receive_index++] = (uint8_t)USART_ReceiveData(UART5);
		
	}
		
	if (USART_GetFlagStatus(UART5, USART_FLAG_ORE) != RESET)
	{
		(void)USART_ReceiveData(UART5);
	}
}
#endif

/****************************************************************************************************************************************/

#ifdef STM32F10X_MD
void USART_init(u8 USARTx,u32 BaudRate,uint8_t PreemptionPriority,uint8_t SubPriority,u8 remap_usart)
{
	u16 GPIO_Pin_Tx;
	u16 GPIO_Pin_Rx;
	u8  USART_IRQChannelx;
	USART_TypeDef* USARTy;
	GPIO_TypeDef*  GPIOy;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	if(remap_usart==0)
	{
		switch(USARTx)
		{
				case 1:
							USARTy=USART1;
							GPIOy=GPIOA;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_9;
							GPIO_Pin_Rx=GPIO_Pin_10;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);break;
				case 2:
							USARTy=USART2;
							GPIOy=GPIOA;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_2;
							GPIO_Pin_Rx=GPIO_Pin_3;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							USARTy=USART3;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART3_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_10;
							GPIO_Pin_Rx=GPIO_Pin_11;
							USART_printf=USART3;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);break;
		}

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOy, &GPIO_InitStructure);    

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOy, &GPIO_InitStructure);
	}

	if(remap_usart==1)
	{
		switch(USARTx)
		{
				case 1:
							GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//USART1 ���ù���ӳ��
							USARTy=USART1;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_6;
							GPIO_Pin_Rx=GPIO_Pin_7;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB, ENABLE);break;
				case 2:
							GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//USART2 ���ù���ӳ��				
							USARTy=USART2;
							GPIOy=GPIOD;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_5;
							GPIO_Pin_Rx=GPIO_Pin_6;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);	//USART3 ���ù��ܲ���ӳ��
							USARTy=USART3;
							GPIOy=GPIOC;
							USART_IRQChannelx=USART3_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_10;
							GPIO_Pin_Rx=GPIO_Pin_11;
							USART_printf=USART3;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);break;
		}
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOy, &GPIO_InitStructure);    

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOy, &GPIO_InitStructure);
	}		

	if(remap_usart==2)
	{
		GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//USART3 ���ù��ܲ���ӳ��
		USARTy=USART3;
		GPIOy=GPIOD;
		USART_IRQChannelx=USART3_IRQn;
		GPIO_Pin_Tx=GPIO_Pin_8;
		GPIO_Pin_Rx=GPIO_Pin_9;
		USART_printf=USART3;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOy, &GPIO_InitStructure);    

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOy, &GPIO_InitStructure);
	}	
		
	USART_InitStructure.USART_BaudRate = BaudRate;		//���ڵĲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�����ֳ���(8λ��9λ)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//�����õ�ֹͣλ-֧��1��2��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;			//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//˫��ģʽ��ʹ�ܷ��ͺͽ���
	USART_Init(USARTy, &USART_InitStructure);		/* ���ݴ���Ĳ�����ʼ��STM32��USART���� */
	 
	/* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USARTy, USART_FLAG_TC);     // ���־ 
	USART_ITConfig(USARTy,USART_IT_RXNE,ENABLE); //���������жϣ�����Ҫ�ڿ�������ǰ
	
	USART_Cmd(USARTy, ENABLE);/* ʹ��STM32��USART����ģ�� */

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//4���������ȼ���4����Ӧ���ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQChannelx;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority ;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���  
	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);//�����ж�
}
#endif /* STM32F10X_MD */

#ifdef STM32F10X_HD
void USART_init(u8 USARTx,u32 BaudRate,uint8_t PreemptionPriority,uint8_t SubPriority,u8 remap_usart)
{
	u16 GPIO_Pin_Tx;
	u16 GPIO_Pin_Rx;
	u8  USART_IRQChannelx;
	USART_TypeDef* USARTy;
	GPIO_TypeDef*  GPIOy;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	if(remap_usart==0)
	{
		switch(USARTx)
		{
				case 1:
							USARTy=USART1;
							GPIOy=GPIOA;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_9;
							GPIO_Pin_Rx=GPIO_Pin_10;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);break;
				case 2:
							USARTy=USART2;
							GPIOy=GPIOA;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_2;
							GPIO_Pin_Rx=GPIO_Pin_3;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							USARTy=USART3;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART3_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_10;
							GPIO_Pin_Rx=GPIO_Pin_11;
							USART_printf=USART3;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);break;
				case 4:
							USARTy=UART4;
							GPIOy=GPIOC;
							USART_IRQChannelx=UART4_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_10;
							GPIO_Pin_Rx=GPIO_Pin_11;
							USART_printf=UART4;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);break;
				case 5:
							USARTy=UART5;
							USART_IRQChannelx=UART5_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_12;
							GPIO_Pin_Rx=GPIO_Pin_2;
							USART_printf=UART5;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);break;
		}

		if(USARTx!=5)
		{

				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOy, &GPIO_InitStructure);    

				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_Init(GPIOy, &GPIO_InitStructure);
		}
		else
		{
				/* Configure USART5 Tx (PC.12) as alternate function push-pull */
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOC, &GPIO_InitStructure);    
				/* Configure USART5 Rx (PD.2) as input floating */
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_Init(GPIOD, &GPIO_InitStructure);
		}
	}

	if(remap_usart==1)
	{
		switch(USARTx)
		{
				case 1:
							GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//USART1 ���ù���ӳ��
							USARTy=USART1;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_6;
							GPIO_Pin_Rx=GPIO_Pin_7;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB, ENABLE);break;
				case 2:
							GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//USART2 ���ù���ӳ��				
							USARTy=USART2;
							GPIOy=GPIOD;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_5;
							GPIO_Pin_Rx=GPIO_Pin_6;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);	//USART3 ���ù��ܲ���ӳ��
							USARTy=USART3;
							GPIOy=GPIOC;
							USART_IRQChannelx=USART3_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_10;
							GPIO_Pin_Rx=GPIO_Pin_11;
							USART_printf=USART3;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);break;
		}
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOy, &GPIO_InitStructure);    

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOy, &GPIO_InitStructure);
	}		

	if(remap_usart==2)
	{
		GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//USART3 ���ù��ܲ���ӳ��
		USARTy=USART3;
		GPIOy=GPIOD;
		USART_IRQChannelx=USART3_IRQn;
		GPIO_Pin_Tx=GPIO_Pin_8;
		GPIO_Pin_Rx=GPIO_Pin_9;
		USART_printf=USART3;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOy, &GPIO_InitStructure);    

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOy, &GPIO_InitStructure);
	}	
		
	USART_InitStructure.USART_BaudRate = BaudRate;		//���ڵĲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�����ֳ���(8λ��9λ)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//�����õ�ֹͣλ-֧��1��2��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;			//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//˫��ģʽ��ʹ�ܷ��ͺͽ���
	USART_Init(USARTy, &USART_InitStructure);		/* ���ݴ���Ĳ�����ʼ��STM32��USART���� */
	 
	/* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USARTy, USART_FLAG_TC);     // ���־ 
	USART_ITConfig(USARTy,USART_IT_RXNE,ENABLE); //���������жϣ�����Ҫ�ڿ�������ǰ
	
	USART_Cmd(USARTy, ENABLE);/* ʹ��STM32��USART����ģ�� */

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//4���������ȼ���4����Ӧ���ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQChannelx;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority ;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���  
	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);//�����ж�
}
#endif /* STM32F10X_HD */

#ifdef STM32F10X_CL
void USART_init(u8 USARTx,u32 BaudRate,uint8_t PreemptionPriority,uint8_t SubPriority,u8 remap_usart)
{
	u16 GPIO_Pin_Tx;
	u16 GPIO_Pin_Rx;
	u8  USART_IRQChannelx;
	USART_TypeDef* USARTy;
	GPIO_TypeDef*  GPIOy;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	if(remap_usart==0)
	{
		switch(USARTx)
		{
				case 1:
							USARTy=USART1;
							GPIOy=GPIOA;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_9;
							GPIO_Pin_Rx=GPIO_Pin_10;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);break;
				case 2:
							USARTy=USART2;
							GPIOy=GPIOA;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_2;
							GPIO_Pin_Rx=GPIO_Pin_3;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							USARTy=USART3;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART3_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_10;
							GPIO_Pin_Rx=GPIO_Pin_11;
							USART_printf=USART3;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);break;
				case 4:
							USARTy=UART4;
							GPIOy=GPIOC;
							USART_IRQChannelx=UART4_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_10;
							GPIO_Pin_Rx=GPIO_Pin_11;
							USART_printf=UART4;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);break;
				case 5:
							USARTy=UART5;
							USART_IRQChannelx=UART5_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_12;
							GPIO_Pin_Rx=GPIO_Pin_2;
							USART_printf=UART5;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);break;
		}

		if(USARTx!=5)
		{

				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOy, &GPIO_InitStructure);    

				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_Init(GPIOy, &GPIO_InitStructure);
		}
		else
		{
				/* Configure USART5 Tx (PC.12) as alternate function push-pull */
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
				GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
				GPIO_Init(GPIOC, &GPIO_InitStructure);    
				/* Configure USART5 Rx (PD.2) as input floating */
				GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
				GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
				GPIO_Init(GPIOD, &GPIO_InitStructure);
		}
	}

	if(remap_usart==1)
	{
		switch(USARTx)
		{
				case 1:
							GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//USART1 ���ù���ӳ��
							USARTy=USART1;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_6;
							GPIO_Pin_Rx=GPIO_Pin_7;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB, ENABLE);break;
				case 2:
							GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//USART2 ���ù���ӳ��				
							USARTy=USART2;
							GPIOy=GPIOD;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_5;
							GPIO_Pin_Rx=GPIO_Pin_6;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);	//USART3 ���ù��ܲ���ӳ��
							USARTy=USART3;
							GPIOy=GPIOC;
							USART_IRQChannelx=USART3_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_10;
							GPIO_Pin_Rx=GPIO_Pin_11;
							USART_printf=USART3;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);break;
		}
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOy, &GPIO_InitStructure);    

			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_Init(GPIOy, &GPIO_InitStructure);
	}		

	if(remap_usart==2)
	{
		GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//USART3 ���ù��ܲ���ӳ��
		USARTy=USART3;
		GPIOy=GPIOD;
		USART_IRQChannelx=USART3_IRQn;
		GPIO_Pin_Tx=GPIO_Pin_8;
		GPIO_Pin_Rx=GPIO_Pin_9;
		USART_printf=USART3;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Tx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOy, &GPIO_InitStructure);    

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_Rx;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_Init(GPIOy, &GPIO_InitStructure);
	}	
		
	USART_InitStructure.USART_BaudRate = BaudRate;		//���ڵĲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//�����ֳ���(8λ��9λ)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//�����õ�ֹͣλ-֧��1��2��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No ;			//����żУ��
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ��������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//˫��ģʽ��ʹ�ܷ��ͺͽ���
	USART_Init(USARTy, &USART_InitStructure);		/* ���ݴ���Ĳ�����ʼ��STM32��USART���� */
	 
	/* �����������1���ֽ��޷���ȷ���ͳ�ȥ������ */
	USART_ClearFlag(USARTy, USART_FLAG_TC);     // ���־ 
	USART_ITConfig(USARTy,USART_IT_RXNE,ENABLE); //���������жϣ�����Ҫ�ڿ�������ǰ
	
	USART_Cmd(USARTy, ENABLE);/* ʹ��STM32��USART����ģ�� */

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//4���������ȼ���4����Ӧ���ȼ�
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQChannelx;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority ;//��ռ���ȼ�
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//�����ȼ�
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���  
	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);//�����ж�
}
#endif /* STM32F10X_CL */

//void Change_printf(USART_TypeDef* USART_prt)//�ض��򴮿�ѡ��
//{
//	USART_printf=USART_prt;
//}

//void USART_Putc(unsigned char c)  //����һ���ַ���
//{  
//    USART_SendData(USART_printf, c);  
//    while(USART_GetFlagStatus(USART_printf, USART_FLAG_TXE) == RESET );  /* ѭ����ֱ��������� */
//}

//void USART_Puts(unsigned char *str,int num)  //����һ������
//{  
//	int i;
//	for(i=0;i<num;i++)
//	{
//		USART_SendData(USART_printf,*str++);  
//		while(USART_GetFlagStatus(USART_printf, USART_FLAG_TXE) == RESET);  /* ѭ����ֱ��������� */
//	}	
//}

//����һ���ֽ�
void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte)	//����һ���ֽ�
{

    	USARTx->DR = (SendByte & (uint16_t)0x01FF);
  		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}
//����һ������
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len)	//����һ������
{
	uint16_t i = 0;
	for(i = 0; i < len; i++)
	{
    	USARTx->DR = (*(SendChars + i) & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

//USART�����ַ���
void UART_SendString(USART_TypeDef* USARTx,char* s)
{
	while(*s)//����ַ���������
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET); 
		USART_SendData(USARTx ,*s++);//���͵�ǰ�ַ�
	}
}

//�ڵδ��ж� SysTick_Handler��ִ�еĴ���
void USART_ReceiveOvertimeProcess(void)		//�ڵδ��ж� SysTick_Handler��ִ�еĴ���
{
	uint16_t i = 0;	

	#ifdef USING_USART1
	if(USART1_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART1_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART1_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART1_ready_buf_len = USART1_receive_index;

			for(i = 0;i <= USART1_ready_buf_len; i ++)
				USART1_ready_buf[i] = USART1_receive_buf[i];
	
			USART1_ready_buf_ok = UART_OK;
			USART1_receive_index=0;
			USART1_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_USART2
	if(USART2_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART2_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART2_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART2_ready_buf_len = USART2_receive_index;

			for(i = 0;i <= USART2_ready_buf_len; i ++)
				USART2_ready_buf[i] = USART2_receive_buf[i];
	
			USART2_ready_buf_ok = UART_OK;
			USART2_receive_index=0;
			USART2_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_USART3
	if(USART3_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		USART3_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(USART3_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			USART3_ready_buf_len = USART3_receive_index;

			for(i = 0;i <= USART3_ready_buf_len; i ++)
				USART3_ready_buf[i] = USART3_receive_buf[i];
	
			USART3_ready_buf_ok = UART_OK;
			USART3_receive_index=0;
			USART3_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_UART4
	if(UART4_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		UART4_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(UART4_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			UART4_ready_buf_len = UART4_receive_index;

			for(i = 0;i <= UART4_ready_buf_len; i ++)
				UART4_ready_buf[i] = UART4_receive_buf[i];
	
			UART4_ready_buf_ok = UART_OK;
			UART4_receive_index=0;
			UART4_ReceiveTimeCounter = 0;
		}
	}
	#endif

	#ifdef USING_UART5
	if(UART5_ReceiveTimeCounter>=USART_PERIOD_MS)
	{
		UART5_ReceiveTimeCounter -= USART_PERIOD_MS;

		if(UART5_ReceiveTimeCounter<USART_PERIOD_MS)
		{
			UART5_ready_buf_len = UART5_receive_index;

			for(i = 0;i <= UART5_ready_buf_len; i ++)
				UART5_ready_buf[i] = UART5_receive_buf[i];
	
			UART5_ready_buf_ok = UART_OK;
			UART5_receive_index=0;
			UART5_ReceiveTimeCounter = 0;
		}
	}
	#endif
}

/******************************************************************************************************************/
/*
    �������´���,֧��printf����,����Ҫѡ��use MicroLIB	  
*/
#ifndef MicroLIB
//#pragma import(__use_no_semihosting)             //û��ʵ��fgetcʱ��Ҫ�����ò���   
/* ��׼����Ҫ��֧�ֺ��� ʹ��printf()���Դ�ӡ����Ҫʵ�ָú��� */               
struct __FILE 
{ 
	int handle; 
    /* Whatever you require here. If the only file you are using is */    
    /* standard output using printf() for debugging, no file handling */    
    /* is required. */
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
_sys_exit(int x) 
{ 
	x = x; 
} 
/* �ض���fputc���� ���ʹ��MicroLIBֻ��Ҫ�ض���fputc�������� */  
int fputc(int ch, FILE *f)
{
		while (USART_GetFlagStatus(USART_printf, USART_FLAG_TC) == RESET);		
		/* ����һ���ֽ����ݵ�USART1 */
		USART_SendData(USART_printf, (u8) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART_printf, USART_FLAG_TC) == RESET);		
	
		return (ch);
}
/*
����ֱ��ʹ��putchar
����Ҫ�ٶ��� int putchar(int ch)����Ϊstdio.h�������¶���
 #define putchar(c) putc(c, stdout)
*/

int ferror(FILE *f) {  
    /* Your implementation of ferror */  
    return EOF;  
} 
#endif 

FILE __stdin;

///�ض���c�⺯��scanf��USART1
int fgetc(FILE *fp)
{
		/* �ȴ�����1�������� */
		while (USART_GetFlagStatus(USART_printf, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART_printf);
}
/******************************************************************************************************************/

//�жϴ����Ƿ�������
//���ճɹ����� UART_OK
//����ʧ�ܷ��� UART_ERROR
int Get_USART_ready_buf_ok(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)return USART1_ready_buf_ok;
#endif	
	
#ifdef USING_USART2
	else if(usart==USART2)return USART2_ready_buf_ok;
#endif

#ifdef USING_USART3
	else if(usart==USART3)return USART3_ready_buf_ok;
#endif
	
#ifdef USING_UART4
	else if(usart==UART4)return UART4_ready_buf_ok;
#endif	
	
#ifdef USING_UART5
	else if(usart==UART5)return UART5_ready_buf_ok;
#endif			
	return UART_ERROR;
}

//��������Ƿ������ϱ�־
void Clean_USART_ready_buf_OK(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)
	{
		USART1_ready_buf_ok=UART_ERROR;
	}
#endif	
	
#ifdef USING_USART2
	else if(usart==USART2)
	{
		USART2_ready_buf_ok=UART_ERROR;
	}
#endif

#ifdef USING_USART3
	else if(usart==USART3)
	{
		USART3_ready_buf_ok=UART_ERROR;
	}		
#endif
	
#ifdef USING_UART4
	else if(usart==UART4)
	{
		UART4_ready_buf_ok=UART_ERROR;
	}		
#endif	
	
#ifdef USING_UART5
	else if(usart==UART5)
	{
		UART5_ready_buf_ok=UART_ERROR;
	}
#endif			

}

//������ڻ�������
void Clean_USART_ready_buf(USART_TypeDef * usart)
{
#ifdef USING_USART1
	if(usart==USART1)
	{
		memset(USART1_ready_buf,0,USART1_BUF_SIZE);
	}
#endif	
	
#ifdef USING_USART2
	else if(usart==USART2)
	{
		memset(USART2_ready_buf,0,USART2_BUF_SIZE);
	}
#endif

#ifdef USING_USART3
	else if(usart==USART3)
	{
		memset(USART3_ready_buf,0,USART3_BUF_SIZE);
	}		
#endif
	
#ifdef USING_UART4
	else if(usart==UART4)
	{
		memset(UART4_ready_buf,0,UART4_BUF_SIZE);
	}		
#endif	
	
#ifdef USING_UART5
	else if(usart==UART5)
	{
		memset(UART5_ready_buf,0,UART5_BUF_SIZE);
	}
#endif			

}


/*
  * log:

  *	2018��4��15��
	�����������룬δ�õ��Ĵ��ڲ�ʹ�ó�ʱ������,�����ڴ�ռ��
	����ע��
	Programmer:����

  *	2018��4��6��
	������ʱ���մ���:
		void USART_ReceiveOvertimeProcess(void);	//�ڵδ��ж� SysTick_Handler��ִ�еĴ���
	ɾ�����º�����
		void USART_Putc(unsigned char c);	//����һ���ַ���
		void USART_Puts(unsigned char *str,int num);   //����num������
		void Change_printf(USART_TypeDef* USART_prt);//�ض��򴮿�ѡ��
	ȡ����֮���ǣ�
		void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte);	//����һ���ֽ�
		void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len);	//����һ������
	��������ʱȷ��ʹ��ʲô���ڷ���

	�жϺ���ת��stm32f10x_it.c��,���ӹ淶(Ӧ�����е��жϺ�����Ӧ�÷ŵ�stm32f10x_it.c��)
	
	Programmer:����

  *	2016��7��8��
	�½�����
	ʵ�ֻ�����ʼ������
	ʵ�ֻ�����������չ���
	Programmer:����
	
*/

