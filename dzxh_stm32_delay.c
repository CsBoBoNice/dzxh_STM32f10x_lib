#include "dzxh_stm32_delay.h"

/**********ʹ�÷���***************************************************************/
/*
	delay_us(1024);	//��ʱ1024us
	delay_ms(1024);	//��ʱ1024ms

ע:
����ʱʱ�䲻׼ȷ��delay_us���������ӻ����__NOP();
*/

/*********************************************************************************/

//��ͨ��ʱ����
void delay_us(u32 nTimer)  
{  
	u32 i=0;  
	for(i=0;i<nTimer;i++){  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();  
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();  
		__NOP();__NOP();__NOP();__NOP();__NOP();
//		__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();
//		__NOP();  
	}  
}  
//��ͨ��ʱ����
void delay_ms(u32 nTimer)  
{  
    u32 i=1000*nTimer;  
    delay_us(i);  
} 

/*
  * log:

  *	2018��4��15��
	�޸ĺ�������
	���ļ�ֻ����ͨ��ʱ����
	Programmer:����

  *	2018��4��6��
	�޸ĺ�������
	��������ͨ��ʱ��δ���ʱ
	Programmer:����

  *	2016��7��6��
	�½�����
	ʵ�ֻ�����ʼ������
	ʵ�ֻ�����������չ���
	Programmer:����
	
*/


