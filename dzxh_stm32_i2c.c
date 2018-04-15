#include "dzxh_stm32_i2c.h"

#define I2C_Speed              400000		//I2C��������  ���ֵ���ܸ��� 400KHz
#define I2C_SLAVE_ADDRESS    0xff			//����STM32�豸����ĵ�ַ
#define I2C_PageSize           8
/****************************************************************************************/
/*
		//���豸0xA0��0λ��д��I2c_Buf_Write����256�ֽ�
@��: 	I2C_EE_BufferWrite(I2C1,0xA0,I2c_Buf_Write,0,256);

		//���豸0xA1��0λ�ö�ȡI2c_Buf_Read����256�ֽ� 
@��: 	I2C_BufferRead(I2C1,0xA1,I2c_Buf_Read,0,256);

@��: I2C_init(1,0);	//��ʼ��I2C
	����1��ѡ��I2C1��I2C2 ȡֵ��Χ(1,2)
									1	I2C1
									2	I2C2
									
	����2���Ƿ���ӳ�� ȡֵ��Χ��0,1��
						I2C		������ӳ��		SCL		SDA
						
						I2C1	0 ����û��ӳ��	PB6		PB7
								1 ������ӳ��	PB8		PB9
								
						I2C2	0 ����û��ӳ��	PB10	PB11
						
(Ĭ�ϣ�I2C_ModeΪ I2C ģʽ)
(Ĭ�ϣ�I2C_DutyCycle = I2C_DutyCycle_2;//I2C ����ģʽ Tlow / Thigh = 2)
(Ĭ�ϣ�I2C_Ack = I2C_Ack_Enable;//ʹ��Ӧ�� ACK��)
(Ĭ�ϣ�I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//Ӧ�� 7 λ��ַ)

*/
/****************************************************************************************/
/*
 * ��������I2C_init
 * ����  ����ʼ��I2C
 * ����  ��
 *         -I2Cx ѡ��I2C1��I2C2 ȡֵ��Χ(1,2)
 *         -remap_i2c �Ƿ���ӳ�� ȡֵ��Χ��0,1��
 * ���  ����
 * ����  ����
 * ����  ���ⲿ����
 */
void I2C_init(u8 I2Cx,u8 remap_i2c)
{
	uint16_t GPIO_Pin_SCL;
	uint16_t GPIO_Pin_SDA;	
	I2C_TypeDef * I2C;
	GPIO_TypeDef*  GPIOy;
	GPIO_InitTypeDef  GPIO_InitStructure; 
	I2C_InitTypeDef  I2C_InitStructure;

	if(remap_i2c==0)
	{
		switch(I2Cx)
		{
			case 1:
					I2C=I2C1;
					GPIOy=GPIOB;
					GPIO_Pin_SCL=GPIO_Pin_6;
					GPIO_Pin_SDA=GPIO_Pin_7;
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);break;
			case 2:
					I2C=I2C2;
					GPIOy=GPIOB;
					GPIO_Pin_SCL=GPIO_Pin_10;
					GPIO_Pin_SDA=GPIO_Pin_11;
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);break;		
		}
	}
	if(remap_i2c==1)
	{
		switch(I2Cx)
		{
			case 1:
					GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);//I2C���ù���ȫӳ��
					I2C=I2C1;
					GPIOy=GPIOB;
					GPIO_Pin_SCL=GPIO_Pin_8;
					GPIO_Pin_SDA=GPIO_Pin_9;
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);break;		
		}
	}

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_SCL | GPIO_Pin_SDA;/* PB6-I2C1_SCL��PB7-I2C1_SDA*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // ��©���
	GPIO_Init(GPIOy, &GPIO_InitStructure);
	
	/* I2C ���� */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;//���� I2C Ϊ I2C ģʽ
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;//I2C ����ģʽ Tlow / Thigh = 2
	I2C_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS;//����STM32�豸����ĵ�ַ
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//ʹ��Ӧ�� ACK��
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//Ӧ�� 7 λ��ַ
	I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;//�ò�����������ʱ��Ƶ�ʣ����ֵ���ܸ��� 400KHz

	/* I2C ��ʼ�� */
	I2C_Init(I2C, &I2C_InitStructure);
	
	/* ʹ�� I2C */
	I2C_Cmd(I2C, ENABLE);
	/*����1�ֽ�1Ӧ��ģʽ*/
	I2C_AcknowledgeConfig(I2C, ENABLE);   	
}

/*
 * ��������I2C_ByteWrite
 * ����  ��дһ���ֽڵ����豸��
 * ����  ��
 *         -I2C ѡ��I2C1��I2C2
 *         -ADDR ���豸��ַ 
 *         -byte Ҫ���͵��ֽ�
 *         -WriteAddr д����ڲ���ַ 
 * ���  ����
 * ����  ����
 * ����  ���ⲿ����
 */
void I2C_ByteWrite(I2C_TypeDef * I2C,u8 ADDR,u8 byte, u8 WriteAddr)
{
  /* Send STRAT condition */
  I2C_GenerateSTART(I2C, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT));  

  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C, ADDR, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
      
  /* Send the EEPROM's internal address to write to */
  I2C_SendData(I2C, WriteAddr);
  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the byte to be written */
  I2C_SendData(I2C, byte); 
   
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STOP condition */
  I2C_GenerateSTOP(I2C, ENABLE);
}

/*
 * ��������I2C_PageWrite
 * ����  ������д���ݵ����豸��
 * ����  ��
 *         -I2C ѡ��I2C1��I2C2
 *         -ADDR ���豸��ַ
 *         -pBuffer ������ָ��
 *         -WriteAddr д����ڲ���ַ 
 *         -NumByteToWrite Ҫд����豸���ֽ���
 * ���  ����
 * ����  ����
 * ����  ���ⲿ����
 */
void I2C_PageWrite(I2C_TypeDef * I2C,u8 ADDR,u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite)
{
    while(I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY)); 
    
  /* Send START condition */
  I2C_GenerateSTART(I2C, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT)); 
  
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C, ADDR, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));  

  /* Send the EEPROM's internal address to write to */    
  I2C_SendData(I2C, WriteAddr);  

  /* Test on EV8 and clear it */
  while(! I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* While there is data to be written */
  while(NumByteToWrite--)  
  {
    /* Send the current byte */
    I2C_SendData(I2C, *pBuffer); 

    /* Point to the next byte to be written */
    pBuffer++; 
  
    /* Test on EV8 and clear it */
    while (!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  }

  /* Send STOP condition */
  I2C_GenerateSTOP(I2C, ENABLE);
}


/*
 * ��������I2C_EE_BufferRead
 * ����  ���Ӵ��豸������������ 
 * ����  ��
 *         -I2C ѡ��I2C1��I2C2
 *         -ADDR ���豸��ַ
 *         -pBuffer ��ŴӴ��豸��ȡ�����ݵĻ�����ָ�롣
 *         -ReadAddr ��ȡ���ڲ���ַ 
 *         -NumByteToWrite Ҫ�Ӵ��豸��ȡ���ֽ�����
 * ���  ����
 * ����  ����
 * ����  ���ⲿ����
 */
void I2C_BufferRead(I2C_TypeDef * I2C,u8 ADDR,u8* pBuffer, u8 ReadAddr, u16 NumByteToRead)
{  
  //*((u8 *)0x4001080c) |=0x80; 
    while(I2C_GetFlagStatus(I2C, I2C_FLAG_BUSY)); // Added by Najoua 27/08/2008
    
    
  /* Send START condition */
  I2C_GenerateSTART(I2C, ENABLE);
  //*((u8 *)0x4001080c) &=~0x80;
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT));

  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C, ADDR, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
  
  /* Clear EV6 by setting again the PE bit */
  I2C_Cmd(I2C, ENABLE);

  /* Send the EEPROM's internal address to write to */
  I2C_SendData(I2C, ReadAddr);  

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(I2C, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send EEPROM address for read */
  I2C_Send7bitAddress(I2C, ADDR, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
  /* While there is data to be read */
  while(NumByteToRead)  
  {
    if(NumByteToRead == 1)
    {
      /* Disable Acknowledgement */
      I2C_AcknowledgeConfig(I2C, DISABLE);
      
      /* Send STOP Condition */
      I2C_GenerateSTOP(I2C, ENABLE);
    }

    /* Test on EV7 and clear it */
    if(I2C_CheckEvent(I2C, I2C_EVENT_MASTER_BYTE_RECEIVED))  
    {      
      /* Read a byte from the EEPROM */
      *pBuffer = I2C_ReceiveData(I2C);

      /* Point to the next location where the byte read will be saved */
      pBuffer++; 
      
      /* Decrement the read bytes counter */
      NumByteToRead--;        
    }   
  }

  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C, ENABLE);
}


/*
 * ��������I2C_WaitEepromStandbyState
 * ����  ��Wait for EEPROM Standby state
		   �ȴ�EEPROM����״̬
 * ����  ����
 * ���  ����
 * ����  ����
 * ����  �� 
 */
void I2C_WaitEepromStandbyState(I2C_TypeDef * I2C,u8 ADDR)      
{
  vu16 SR1_Tmp = 0;

  do
  {
    /* Send START condition */
    I2C_GenerateSTART(I2C, ENABLE);
    /* Read I2C SR1 register */
    SR1_Tmp = I2C_ReadRegister(I2C, I2C_Register_SR1);
    /* Send EEPROM address for write */
    I2C_Send7bitAddress(I2C, ADDR, I2C_Direction_Transmitter);
  }while(!(I2C_ReadRegister(I2C, I2C_Register_SR1) & 0x0002));
  
  /* Clear AF flag */
  I2C_ClearFlag(I2C, I2C_FLAG_AF);
    /* STOP condition */    
    I2C_GenerateSTOP(I2C, ENABLE); 
}

/*******************************************************************************
* Function Name  : I2C_EE_BufferWrite
* Description    : Writes buffer of data to the I2C EEPROM.
* Input          : - pBuffer : pointer to the buffer  containing the data to be 
*                    written to the EEPROM.
*                  - WriteAddr : EEPROM's internal address to write to.
*                  - NumByteToWrite : number of bytes to write to the EEPROM.
* Output         : None
* Return         : None
*******************************************************************************/
void I2C_EE_BufferWrite(I2C_TypeDef * I2C,u8 ADDR,u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite)
{
	u8 NumOfPage = 0, NumOfSingle = 0, Addr = 0, count = 0;

	Addr = WriteAddr % I2C_PageSize;  //0x00%8=0
	count = I2C_PageSize - Addr;		//8-0=8
	NumOfPage =  NumByteToWrite / I2C_PageSize;	//256/8	=32
	NumOfSingle = NumByteToWrite % I2C_PageSize;	//256%8	=0

	/* If WriteAddr is I2C_PageSize aligned  */
	if(Addr == 0) 
	{
		/* If NumByteToWrite < I2C_PageSize */
		if(NumOfPage == 0) 
		{
			I2C_PageWrite(I2C,ADDR,pBuffer, WriteAddr, NumOfSingle);
			I2C_WaitEepromStandbyState(I2C,ADDR);
		}
		/* If NumByteToWrite > I2C_PageSize */
		else  
		{
			while(NumOfPage--)  //һ��д8������
			{
				I2C_PageWrite(I2C,ADDR,pBuffer, WriteAddr, I2C_PageSize);				
				I2C_WaitEepromStandbyState(I2C,ADDR);
				WriteAddr +=  I2C_PageSize;
				pBuffer += I2C_PageSize;
			}

			if(NumOfSingle!=0)	//��8�������
			{
				I2C_PageWrite(I2C,ADDR,pBuffer, WriteAddr, NumOfSingle);				
				I2C_WaitEepromStandbyState(I2C,ADDR);
			}
		}
	}
	/* If WriteAddr is not I2C_PageSize aligned  */
	else 
	{
	/* If NumByteToWrite < I2C_PageSize */
		if(NumOfPage== 0) 
		{
			I2C_PageWrite(I2C,ADDR,pBuffer, WriteAddr, NumOfSingle);				
			I2C_WaitEepromStandbyState(I2C,ADDR);
		}
		/* If NumByteToWrite > I2C_PageSize */
		else
		{
			NumByteToWrite -= count;
			NumOfPage =  NumByteToWrite / I2C_PageSize;
			NumOfSingle = NumByteToWrite % I2C_PageSize;	

			if(count != 0)
			{  
				I2C_PageWrite(I2C,ADDR,pBuffer, WriteAddr, count);				
				I2C_WaitEepromStandbyState(I2C,ADDR);
				WriteAddr += count;
				pBuffer += count;
			} 

			while(NumOfPage--)
			{
				I2C_PageWrite(I2C,ADDR,pBuffer, WriteAddr, I2C_PageSize);				
				I2C_WaitEepromStandbyState(I2C,ADDR);
				WriteAddr +=  I2C_PageSize;
				pBuffer += I2C_PageSize;  
			}
			if(NumOfSingle != 0)
			{
				I2C_PageWrite(I2C,ADDR,pBuffer, WriteAddr, NumOfSingle);				
				I2C_WaitEepromStandbyState(I2C,ADDR);
			}
		}
	}  
}


/*
  * log:
  *	2018��4��15��
	�޸�IIC��ȡ��д��EEPROM�ֽڲ���ȷ����
	Programmer:����

  *	2016��7��10��
	�½�����
	ʵ�ֻ�����ʼ������
	Programmer:����
	
*/
