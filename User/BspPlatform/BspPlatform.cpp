#include "BspPlatform.h"
#if defined STM32F0
#elif defined STM32F1
#include "stm32f10x.h"
#elif defined STM32F4
#endif
#include "Sys.h"
#include "Core\Queue.h"
#include "Port.h"
#include "Platform\stm32.h"
#include "Device\DeviceConfigHelper.h"

void TimeUpdate();
void BspPlatformInit()
{	
	DeviceConfigHelper::TimeTickInit();//系统用定时器初始化
	DeviceConfigHelper::PTim2Update = TimeUpdate;
}
int DeviceConfigHelper::CurrentTick()
{
#if defined STM32F0

#elif defined STM32F1
	return (TIM2->CNT) >> 1;
#elif defined STM32F4

#endif
}
uint32_t DeviceConfigHelper::CurrentTicks1()
{
#if defined STM32F0

#elif defined STM32F1
	return SysTick->LOAD - SysTick->VAL;
#elif defined STM32F4

#endif
}


