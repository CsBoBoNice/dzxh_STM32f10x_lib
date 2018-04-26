#include "dzxh_stm32_nvic.h"

/*//ȡֵ��Χ:
  *   This parameter can be one of the following values:
  *     @arg NVIC_PriorityGroup_0: 0 bits for pre-emption priority
  *                                4 bits for subpriority
  *     @arg NVIC_PriorityGroup_1: 1 bits for pre-emption priority
  *                                3 bits for subpriority
  *     @arg NVIC_PriorityGroup_2: 2 bits for pre-emption priority
  *                                2 bits for subpriority
  *     @arg NVIC_PriorityGroup_3: 3 bits for pre-emption priority
  *                                1 bits for subpriority
  *     @arg NVIC_PriorityGroup_4: 4 bits for pre-emption priority
  *                                0 bits for subpriority
*/
//�������ȼ����飺�������ȼ�����Ӧ���ȼ� (Ĭ�ϣ�4���������ȼ���4����Ӧ���ȼ�)
void NVIC_Configuration(void)
{ 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
}

/*
  * log:

  *	2018��4��6��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/

