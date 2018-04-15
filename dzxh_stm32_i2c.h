#ifndef  _DZXH_STM32_I2C_H_
#define  _DZXH_STM32_I2C_H_

#include "stm32f10x.h"

void I2C_init(u8 I2Cx,u8 remap_i2c);
void I2C_ByteWrite(I2C_TypeDef * I2C,u8 ADDR,u8 byte, u8 WriteAddr);
void I2C_PageWrite(I2C_TypeDef * I2C,u8 ADDR,u8* pBuffer, u8 WriteAddr, u8 NumByteToWrite);
void I2C_EE_BufferWrite(I2C_TypeDef * I2C,u8 ADDR,u8* pBuffer, u8 WriteAddr, u16 NumByteToWrite);
void I2C_BufferRead(I2C_TypeDef * I2C,u8 ADDR,u8* pBuffer, u8 ReadAddr, u16 NumByteToRead);
void I2C_WaitEepromStandbyState(I2C_TypeDef * I2C,u8 ADDR);

#endif
