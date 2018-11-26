#include "OnChip\Port.h"
#include "OnChip/USART.h"
#include "Sys.h"
#include "Buffer.h"

char *AppVersion = "0.1.2018.1115"; //版本号

#ifdef STM32F0
OutputPort led1(PC6, true);
OutputPort led2(PC7, true);
OutputPort led3(PC8, true);
OutputPort led4(PC9, true);

OutputPort ledss[] =
{
	led1, led2, led3, led4
};
#elif defined STM32F1
#if 1
OutputPort led1(PB0, false);
OutputPort led2(PF7, false);
OutputPort led3(PF8, false);
#else 
OutputPort led1(PD0, false);
OutputPort led2(PD1, false);
OutputPort led3(PD2, false);
OutputPort ledLCD(PD12, false);
#endif 
#elif defined STM32F4
#if 1
//正点原子开发板F4
OutputPort led1(PF9, false);
OutputPort led2(PF10, false);
#else 
//安福莱开发板F4-V5
OutputPort led1(PI10, false);
OutputPort led2(PF7, false);
OutputPort led3(PC2, false);
OutputPort led4(PC2, false);
#endif 
#endif

void LedTask(void *param)
{
#ifdef STM32F0
	static uint8_t flag = 1;
	auto leds = (OutputPort*)param;

	flag <<= 1;
	flag &= 0x0f;
	if (flag == 0)
	{
		flag = 1;
	}

	led1 = !led1;
	led2 = !led2;
	led3 = !led3;
	led4 = !led4;
#elif defined STM32F1
	auto leds = (OutputPort*)param;
	*leds = !* leds;
	//    led2 = key0;
#elif defined STM32F4
	OutputPort *leds = (OutputPort*)param;
	*leds = !* leds;
	//led2 = !led2;
	//    led3 = !led3;
	//    led4 = !led4;
	//led2 = keyup;
#endif 
}

USART usart111(USART1, 115200);

void Com1test()
{
	uint8_t buf[20];
	int len = 0;
	len = usart111.RxSize();
	if (usart111.GetBytes(buf, len))
	{
		Buffer(buf, len).Show(true);
	}
	else
	{
		debug_printf("com1 idle error\n");
	}
}

void EspDemoLinkTestInit();
void BspInit()
{
	led1 = 1;
	led2 = 1;
	Sys.AddTask(LedTask, &led1, 0, 500, "LedTask");

	EspDemoLinkTestInit();
	usart111.OnReceive = Com1test;
}
