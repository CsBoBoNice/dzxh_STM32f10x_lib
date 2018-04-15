#include "dzxh_stm32_i2c.h"

#define I2C_Speed              400000		//I2C传输数率  这个值不能高于 400KHz
#define I2C_SLAVE_ADDRESS    0xff			//设置STM32设备本身的地址
#define I2C_PageSize           8
/****************************************************************************************/
/*
		//向设备0xA0的0位置写入I2c_Buf_Write数据256字节
@例: 	I2C_EE_BufferWrite(I2C1,0xA0,I2c_Buf_Write,0,256);

		//向设备0xA1的0位置读取I2c_Buf_Read数据256字节 
@例: 	I2C_BufferRead(I2C1,0xA1,I2c_Buf_Read,0,256);

@例: I2C_init(1,0);	//初始化I2C
	参数1：选择I2C1或I2C2 取值范围(1,2)
									1	I2C1
									2	I2C2
									
	参数2：是否重映射 取值范围（0,1）
						I2C		引脚重映像		SCL		SDA
						
						I2C1	0 引脚没重映射	PB6		PB7
								1 引脚重映射	PB8		PB9
								
						I2C2	0 引脚没重映射	PB10	PB11
						
(默认：I2C_Mode为 I2C 模式)
(默认：I2C_DutyCycle = I2C_DutyCycle_2;//I2C 快速模式 Tlow / Thigh = 2)
(默认：I2C_Ack = I2C_Ack_Enable;//使能应答（ ACK）)
(默认：I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//应答 7 位地址)

*/
/****************************************************************************************/
/*
 * 函数名：I2C_init
 * 描述  ：初始化I2C
 * 输入  ：
 *         -I2Cx 选择I2C1或I2C2 取值范围(1,2)
 *         -remap_i2c 是否重映射 取值范围（0,1）
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
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
					GPIO_PinRemapConfig(GPIO_Remap_I2C1, ENABLE);//I2C复用功能全映射
					I2C=I2C1;
					GPIOy=GPIOB;
					GPIO_Pin_SCL=GPIO_Pin_8;
					GPIO_Pin_SDA=GPIO_Pin_9;
					RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
					RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);break;		
		}
	}

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_SCL | GPIO_Pin_SDA;/* PB6-I2C1_SCL、PB7-I2C1_SDA*/
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;	       // 开漏输出
	GPIO_Init(GPIOy, &GPIO_InitStructure);
	
	/* I2C 配置 */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;//设置 I2C 为 I2C 模式
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;//I2C 快速模式 Tlow / Thigh = 2
	I2C_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS;//设置STM32设备本身的地址
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;//使能应答（ ACK）
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//应答 7 位地址
	I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;//该参数用来设置时钟频率，这个值不能高于 400KHz

	/* I2C 初始化 */
	I2C_Init(I2C, &I2C_InitStructure);
	
	/* 使能 I2C */
	I2C_Cmd(I2C, ENABLE);
	/*允许1字节1应答模式*/
	I2C_AcknowledgeConfig(I2C, ENABLE);   	
}

/*
 * 函数名：I2C_ByteWrite
 * 描述  ：写一个字节到从设备中
 * 输入  ：
 *         -I2C 选择I2C1或I2C2
 *         -ADDR 从设备地址 
 *         -byte 要发送的字节
 *         -WriteAddr 写入的内部地址 
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
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
 * 函数名：I2C_PageWrite
 * 描述  ：连续写数据到从设备中
 * 输入  ：
 *         -I2C 选择I2C1或I2C2
 *         -ADDR 从设备地址
 *         -pBuffer 缓冲区指针
 *         -WriteAddr 写入的内部地址 
 *         -NumByteToWrite 要写入从设备的字节数
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
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
 * 函数名：I2C_EE_BufferRead
 * 描述  ：从从设备中连续读数据 
 * 输入  ：
 *         -I2C 选择I2C1或I2C2
 *         -ADDR 从设备地址
 *         -pBuffer 存放从从设备读取的数据的缓冲区指针。
 *         -ReadAddr 读取的内部地址 
 *         -NumByteToWrite 要从从设备读取的字节数。
 * 输出  ：无
 * 返回  ：无
 * 调用  ：外部调用
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
 * 函数名：I2C_WaitEepromStandbyState
 * 描述  ：Wait for EEPROM Standby state
		   等待EEPROM待机状态
 * 输入  ：无
 * 输出  ：无
 * 返回  ：无
 * 调用  ： 
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
			while(NumOfPage--)  //一次写8个数据
			{
				I2C_PageWrite(I2C,ADDR,pBuffer, WriteAddr, I2C_PageSize);				
				I2C_WaitEepromStandbyState(I2C,ADDR);
				WriteAddr +=  I2C_PageSize;
				pBuffer += I2C_PageSize;
			}

			if(NumOfSingle!=0)	//除8个以外的
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
  *	2018年4月15日
	修复IIC读取与写入EEPROM字节不正确问题
	Programmer:陈述

  *	2016年7月10日
	新建工程
	实现基本初始化功能
	Programmer:陈述
	
*/
