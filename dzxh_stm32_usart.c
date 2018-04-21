#include "dzxh_stm32_usart.h"
#include "include.h"
/******使用方法****************************************************************************************************/
/*

@例:	USART_SendByte(USART1,c);	//发送一个字符串
		参数1：USART_TypeDef* 型
					USART1
					USART2
					USART3
					UART4
					UART5
		参数2：unsigned char 型数据
		
@例:	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//发送一段数据

		参数1：USART_TypeDef* 型
					USART1
					USART2
					USART3
					UART4
					UART5
		参数2：unsigned char 型指针
		参数3：数据个数

@例:	USART_init(1,115200,0,3,0);	//串口初始化

		参数1：USART编号（范围：1,2,3,4,5）
								1	USART1
								2	USART2
								3	USART3
								4	UART4
								5	UART5
										
	参数2：波特率取值范围(600,1200,2400,4800,9600,14400,19200,28800,38400,57600,115200,230400,460800)
	
	参数3：对应抢断优先级级别		取值范围(0,1,2,3)	数值越低优先级越高

	参数4：对应响应优先级级别		取值范围(0,1,2,3)	数值越低优先级越高
	
	参数5：引脚重映射	(范围 参考下表)
串口引脚:
串口		引脚重映像		TX		RX
USART1		0 没重映像		PA9		PA10
			1 完全重映像	PB6		PB7

USART2		0 没重映像		PA2		PA3
			1 完全从映像	PD5		PD6 

USART3		0 没重映像		PB10	PB11
			1 部分重映像1	PC10	PC11
			2 部分重映像2	PD8		PD9
			
UART4		0 没重映像		PC10	PC11

UART5		0 没重映像		PC12	PD2

************************************************************************
@注:

	接收串口数据通过中断接收，通过滴答中断 SysTick_Handler判断是否超时，
在dzxh_stm32_usart.h里设置超时时间，与接收缓存区大小,如果未用到的串口可以注释，节约内存，
由于需要滴答中断，所以需要初始化滴答中断

	当然，如果不希望用滴答定时器可以改用TIM定时器,只需要在定时器中断函数中加上
串口中断处理函数即可	USART_ReceiveOvertimeProcess();

以下为滴答定时器添加超时算法的代码:
void SysTick_Handler(void)
{
	#if defined (USING_USART1) || defined (USING_USART2) || defined (USING_USART3)|| defined (USING_UART4)|| defined (USING_UART5)
	USART_ReceiveOvertimeProcess();
	#endif
}

中断处理函数尽量写在 stm32f10x_it.c文件中:
以下是使用超时处理的中断处理函数:
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

以下是使用带超时的串口接收代码

NVIC_Configuration();//设置优先级分组：抢断优先级和相应优先级
SysTick_delay_init();	//初始化SysTick定时器中断 每1/configTICK_RATE_HZ秒中断一次
USART_init(1,115200,0,3,0);	//串口初始化

if(USART1_ready_buf_ok)	//判断超时，一帧数据接收成功
{
	USART_SendChars(USART1,USART1_ready_buf,USART1_ready_buf_len);	//回发
	USART1_ready_buf_ok = 0;
}

USART1_ready_buf 接收到的数据
USART1_ready_buf_len 接收数据长度

*/
/******************************************************************************************************************/
USART_TypeDef* USART_printf;

#ifdef USING_USART1
uint8_t USART1_receive_buf[USART1_BUF_SIZE];	//数据接收缓存区
uint8_t USART1_ready_buf[USART1_BUF_SIZE];		//接收成功后的数据区
static int32_t USART1_ReceiveTimeCounter = 0;	//超时剩余时间
__IO uint16_t USART1_receive_index=0; 		//正在接收的数据长度
__IO uint8_t USART1_ready_buf_ok = 0;		//是否成功接收
__IO uint16_t USART1_ready_buf_len = 0;		//成功接收后的数据长度
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

/**********************中断函数***************************************************************************************************/

/**********************串口1中断接收一个字符***************************************************************************************************/
/*
在中断服务程序中，由于主机响应中断时并不知道是哪个中断源发出中断请求，
因此必须在中断服务程序中对中断源进行判别，然后分别进行处理。
当然，如果只涉及到一个中断请求，是不用做上述判别的。但是无论什么情况，做上述判别是个好习惯
*/
#ifdef USING_USART1
void USART1_ISR(void)   
{

	if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//判断是否是中断
	{
		USART1_ReceiveTimeCounter = USART1_RECEIVE_OVERTIME;

		if(USART1_receive_index >= USART1_BUF_SIZE)//若接收位置越界，那么重头开始存放
			USART1_receive_index = 0;
		
		USART1_receive_buf[USART1_receive_index++] = (uint8_t)USART_ReceiveData(USART1);//接收字符，并位置加1		
	}	
	if (USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)//过载处理，只要读状态寄存器和数据寄存器就可自动清理此标志
	{
		(void)USART_ReceiveData(USART1);
	}

} 
#endif

#ifdef USING_USART2
void USART2_ISR(void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //判断是否是中断
	{	
		USART2_ReceiveTimeCounter = USART2_RECEIVE_OVERTIME;
		
		if(USART2_receive_index >= USART2_BUF_SIZE)	//若接收位置越界，那么重头开始存放
			USART2_receive_index = 0;
		
		USART2_receive_buf[USART2_receive_index++] = (uint8_t)USART_ReceiveData(USART2);//接收字符，并位置加1
		
	}		
	if (USART_GetFlagStatus(USART2, USART_FLAG_ORE) != RESET)//过载处理，只要读状态寄存器和数据寄存器就可自动清理此标志
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
							GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//USART1 复用功能映射
							USARTy=USART1;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_6;
							GPIO_Pin_Rx=GPIO_Pin_7;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB, ENABLE);break;
				case 2:
							GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//USART2 复用功能映射				
							USARTy=USART2;
							GPIOy=GPIOD;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_5;
							GPIO_Pin_Rx=GPIO_Pin_6;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);	//USART3 复用功能部分映射
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
		GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//USART3 复用功能部分映射
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
		
	USART_InitStructure.USART_BaudRate = BaudRate;		//串口的波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据字长度(8位或9位)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//可配置的停止位-支持1或2个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;			//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//双工模式，使能发送和接收
	USART_Init(USARTy, &USART_InitStructure);		/* 根据传入的参数初始化STM32的USART配置 */
	 
	/* 如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USARTy, USART_FLAG_TC);     // 清标志 
	USART_ITConfig(USARTy,USART_IT_RXNE,ENABLE); //开启接受中断，必须要在开启串口前
	
	USART_Cmd(USARTy, ENABLE);/* 使能STM32的USART功能模块 */

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//4个抢断优先级，4个相应优先级
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQChannelx;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器  
	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);//开启中断
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
							GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//USART1 复用功能映射
							USARTy=USART1;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_6;
							GPIO_Pin_Rx=GPIO_Pin_7;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB, ENABLE);break;
				case 2:
							GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//USART2 复用功能映射				
							USARTy=USART2;
							GPIOy=GPIOD;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_5;
							GPIO_Pin_Rx=GPIO_Pin_6;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);	//USART3 复用功能部分映射
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
		GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//USART3 复用功能部分映射
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
		
	USART_InitStructure.USART_BaudRate = BaudRate;		//串口的波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据字长度(8位或9位)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//可配置的停止位-支持1或2个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;			//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//双工模式，使能发送和接收
	USART_Init(USARTy, &USART_InitStructure);		/* 根据传入的参数初始化STM32的USART配置 */
	 
	/* 如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USARTy, USART_FLAG_TC);     // 清标志 
	USART_ITConfig(USARTy,USART_IT_RXNE,ENABLE); //开启接受中断，必须要在开启串口前
	
	USART_Cmd(USARTy, ENABLE);/* 使能STM32的USART功能模块 */

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//4个抢断优先级，4个相应优先级
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQChannelx;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器  
	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);//开启中断
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
							GPIO_PinRemapConfig(GPIO_Remap_USART1, ENABLE);//USART1 复用功能映射
							USARTy=USART1;
							GPIOy=GPIOB;
							USART_IRQChannelx=USART1_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_6;
							GPIO_Pin_Rx=GPIO_Pin_7;
							USART_printf=USART1;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOB, ENABLE);break;
				case 2:
							GPIO_PinRemapConfig(GPIO_Remap_USART2, ENABLE);//USART2 复用功能映射				
							USARTy=USART2;
							GPIOy=GPIOD;
							USART_IRQChannelx=USART2_IRQn;
							GPIO_Pin_Tx=GPIO_Pin_5;
							GPIO_Pin_Rx=GPIO_Pin_6;
							USART_printf=USART2;
							RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
							RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);break;
				case 3:
							GPIO_PinRemapConfig(GPIO_PartialRemap_USART3, ENABLE);	//USART3 复用功能部分映射
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
		GPIO_PinRemapConfig(GPIO_FullRemap_USART3, ENABLE);//USART3 复用功能部分映射
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
		
	USART_InitStructure.USART_BaudRate = BaudRate;		//串口的波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据字长度(8位或9位)
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//可配置的停止位-支持1或2个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No ;			//无奇偶校验
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//双工模式，使能发送和接收
	USART_Init(USARTy, &USART_InitStructure);		/* 根据传入的参数初始化STM32的USART配置 */
	 
	/* 如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USARTy, USART_FLAG_TC);     // 清标志 
	USART_ITConfig(USARTy,USART_IT_RXNE,ENABLE); //开启接受中断，必须要在开启串口前
	
	USART_Cmd(USARTy, ENABLE);/* 使能STM32的USART功能模块 */

//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//4个抢断优先级，4个相应优先级
	
	NVIC_InitStructure.NVIC_IRQChannel = USART_IRQChannelx;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=PreemptionPriority ;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;		//子优先级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器  
	USART_ITConfig(USARTy, USART_IT_RXNE, ENABLE);//开启中断
}
#endif /* STM32F10X_CL */

//void Change_printf(USART_TypeDef* USART_prt)//重定向串口选择
//{
//	USART_printf=USART_prt;
//}

//void USART_Putc(unsigned char c)  //发送一个字符串
//{  
//    USART_SendData(USART_printf, c);  
//    while(USART_GetFlagStatus(USART_printf, USART_FLAG_TXE) == RESET );  /* 循环，直到传输结束 */
//}

//void USART_Puts(unsigned char *str,int num)  //发送一串数据
//{  
//	int i;
//	for(i=0;i<num;i++)
//	{
//		USART_SendData(USART_printf,*str++);  
//		while(USART_GetFlagStatus(USART_printf, USART_FLAG_TXE) == RESET);  /* 循环，直到传输结束 */
//	}	
//}

//发送一个字节
void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte)	//发送一个字节
{

    	USARTx->DR = (SendByte & (uint16_t)0x01FF);
  		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}
//发送一串数据
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len)	//发送一串数据
{
	uint16_t i = 0;
	for(i = 0; i < len; i++)
	{
    	USARTx->DR = (*(SendChars + i) & (uint16_t)0x01FF);
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}
}

//USART发送字符串
void UART_SendString(USART_TypeDef* USARTx,char* s)
{
	while(*s)//检测字符串结束符
	{
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET); 
		USART_SendData(USARTx ,*s++);//发送当前字符
	}
}

//在滴答中断 SysTick_Handler中执行的代码
void USART_ReceiveOvertimeProcess(void)		//在滴答中断 SysTick_Handler中执行的代码
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
    加入以下代码,支持printf函数,不需要选择use MicroLIB	  
*/
#ifndef MicroLIB
//#pragma import(__use_no_semihosting)             //没有实现fgetc时需要声明该参数   
/* 标准库需要的支持函数 使用printf()调试打印不需要实现该函数 */               
struct __FILE 
{ 
	int handle; 
    /* Whatever you require here. If the only file you are using is */    
    /* standard output using printf() for debugging, no file handling */    
    /* is required. */
}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
_sys_exit(int x) 
{ 
	x = x; 
} 
/* 重定义fputc函数 如果使用MicroLIB只需要重定义fputc函数即可 */  
int fputc(int ch, FILE *f)
{
		while (USART_GetFlagStatus(USART_printf, USART_FLAG_TC) == RESET);		
		/* 发送一个字节数据到USART1 */
		USART_SendData(USART_printf, (u8) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USART_printf, USART_FLAG_TC) == RESET);		
	
		return (ch);
}
/*
可以直接使用putchar
不需要再定义 int putchar(int ch)，因为stdio.h中有如下定义
 #define putchar(c) putc(c, stdout)
*/

int ferror(FILE *f) {  
    /* Your implementation of ferror */  
    return EOF;  
} 
#endif 

FILE __stdin;

///重定向c库函数scanf到USART1
int fgetc(FILE *fp)
{
		/* 等待串口1输入数据 */
		while (USART_GetFlagStatus(USART_printf, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART_printf);
}
/******************************************************************************************************************/

//判断串口是否接收完毕
//接收成功返回 UART_OK
//接收失败返回 UART_ERROR
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

//清除串口是否接收完毕标志
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

//清除串口缓存数据
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

  *	2018年4月15日
	增加条件编译，未用到的串口不使用超时缓存区,减少内存占用
	增加注释
	Programmer:陈述

  *	2018年4月6日
	新增超时接收代码:
		void USART_ReceiveOvertimeProcess(void);	//在滴答中断 SysTick_Handler中执行的代码
	删除以下函数：
		void USART_Putc(unsigned char c);	//发送一个字符串
		void USART_Puts(unsigned char *str,int num);   //发送num个数据
		void Change_printf(USART_TypeDef* USART_prt);//重定向串口选择
	取而代之的是：
		void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte);	//发送一个字节
		void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len);	//发送一串数据
	发送数据时确认使用什么串口发送

	中断函数转到stm32f10x_it.c中,更加规范(应该所有的中断函数都应该放到stm32f10x_it.c中)
	
	Programmer:陈述

  *	2016年7月8日
	新建工程
	实现基本初始化功能
	实现基本发送与接收功能
	Programmer:陈述
	
*/

