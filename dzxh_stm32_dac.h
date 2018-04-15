#ifndef  _DZXH_STM32_DAC_H_
#define  _DZXH_STM32_DAC_H_

#include "stm32f10x.h"

void Dac_Init(u8 DACx);

void Dac_Set_Vol(u8 DACx,u16 vol);

#endif

