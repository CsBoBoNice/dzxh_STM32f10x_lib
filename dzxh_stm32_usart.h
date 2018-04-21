#ifndef __DZXH_STM32_USART_H
#define __DZXH_STM32_USART_H

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

		
#define USART_PERIOD_MS	1	//����ʹ�õĶ�ʱ�������жϵ�ʱ�䵥λMS

#define USING_USART1	//�����ÿ�ע��,��ʡRAM
#define USING_USART2
//#define USING_USART3
//#define USING_UART4
//#define USING_UART5
/********************����������������ѡ��***********************/
/***********************************USART1***************************************/
#ifdef USING_USART1
#define USART1_BUF_SIZE 			256		//����һ��������������С
#define USART1_RECEIVE_OVERTIME		20			//�ֽڳ�ʱʱ��, ��λΪms

extern uint8_t USART1_ready_buf[];
extern __IO uint8_t USART1_ready_buf_ok;
extern __IO uint16_t USART1_ready_buf_len;
void USART1_ISR(void);
#endif
/*************************************USART2**************************************/

#ifdef USING_USART2
#define USART2_BUF_SIZE				256	//����һ��������������С	
#define USART2_RECEIVE_OVERTIME		200		//�ֽڳ�ʱʱ��, ��λΪms
extern uint8_t USART2_ready_buf[];
extern __IO uint8_t USART2_ready_buf_ok;
extern __IO uint16_t USART2_ready_buf_len;
void USART2_ISR(void);
#endif
/*************************************USART3**************************************/

#ifdef USING_USART3
#define USART3_BUF_SIZE				128	//����һ��������������С
#define USART3_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms

extern uint8_t USART3_ready_buf[];
extern __IO uint8_t USART3_ready_buf_ok;
extern __IO uint16_t USART3_ready_buf_len;
void USART3_Init(void);
#endif
/*************************************USART4**************************************/

#ifdef USING_UART4
#define UART4_BUF_SIZE				128	//����һ��������������С
#define UART4_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms	

extern uint8_t UART4_ready_buf[];
extern __IO uint8_t UART4_ready_buf_ok;
extern __IO uint16_t UART4_ready_buf_len;
void UART4_Init(void);
#endif
/*************************************USART5**************************************/

#ifdef USING_UART5
#define UART5_BUF_SIZE				128	//����һ��������������С
#define UART5_RECEIVE_OVERTIME		10		//�ֽڳ�ʱʱ��, ��λΪms	

extern uint8_t UART5_ready_buf[];
extern __IO uint8_t UART5_ready_buf_ok;
extern __IO uint16_t UART5_ready_buf_len;
void UART5_ISR(void);
#endif

#define UART_OK 1
#define UART_ERROR 0

/******************************API************************************************/

void USART_init(u8 USARTx,u32 BaudRate,uint8_t PreemptionPriority,uint8_t SubPriority,u8 remap_usart);//���ڳ�ʼ��
//void USART_Putc(unsigned char c);	//����һ���ַ���
//void USART_Puts(unsigned char *str,int num);   //����num������
//void Change_printf(USART_TypeDef* USART_prt);//�ض��򴮿�ѡ��

void USART1_ISR(void); //�����жϺ���
void USART2_ISR(void); //�����жϺ���
void USART3_ISR(void); //�����жϺ���
void USART4_ISR(void); //�����жϺ���
void USART5_ISR(void); //�����жϺ���

void USART_SendByte(USART_TypeDef* USARTx,uint8_t SendByte);	//����һ���ֽ�
void USART_SendChars(USART_TypeDef* USARTx,const uint8_t* SendChars,uint16_t len);	//����һ������
void UART_SendString(USART_TypeDef* USARTx,char* s);	//USART�����ַ���
void USART_ReceiveOvertimeProcess(void);	//�ڵδ��ж� SysTick_Handler��ִ�еĴ���

int Get_USART_ready_buf_ok(USART_TypeDef * usart);	//�жϴ����Ƿ�������
void Clean_USART_ready_buf_OK(USART_TypeDef * usart);	//��������Ƿ������ϱ�־
void Clean_USART_ready_buf(USART_TypeDef * usart); //������ڻ�������
#endif

