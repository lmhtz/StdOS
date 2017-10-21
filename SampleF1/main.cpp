#include <stdio.h>
#include "SerialPort.h"
#include "Drivers\AT24CXX.h"
#include "Drivers\W25QXXX.h"
#include "Drivers\Button.h"
#include "SString.h"
#include "string.h"
#include "List.h"
#include "Spi.h"
#include "Flash.h"
#include "Drivers\lcd_dr.h"
#include "TInterrupt.h"
#include "Timer.h"
#include "TTime.h"
#include "Drivers\RX8025T.h"


class TTTTime
{
    public:
        uint Seconds; // 全局秒数，系统启动后总秒数。累加
        UInt64 Milliseconds; // 全局毫秒数，系统启动后总毫秒（1000ms整部分）。累加
        uint CurrentTicks; // 当前滴答时钟
        UInt64 Current; // 当前毫秒数
};
TTTTime now123;
//InputPort paa11(PA11,false);
OutputPort paaa1(PA11);
void Test12(void *param)
{
//	int aa=paa11;aa++;
    now123.Seconds = Time.Seconds;
    now123.Milliseconds = Time.Milliseconds;
    now123.Current = Time.Current();
    now123.CurrentTicks = Time.CurrentTicks();
}

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

void LedTask(void *param)
{
    auto leds = (OutputPort*)param;
    *leds = ! * leds;
    //    led2 = key0;
	//paaa1=!paaa1;
	paaa1=0;
}

uint OnUsart1Read(ITransport *transport, Buffer &bs, void *para, void *para2)
{
	transport->Write(bs);
    return 0;
}

uint time6cnt;
void TimerTask(void *param)
{
    static int i = 0;
    printf("\r\n%d: cnt:%d", i++, time6cnt++);
}

SerialPort *sp1;

void InterruptTest();
void ADS1232Test();
void ModbusTest();
void streamtest();
int main(void)
{
    Sys.Init();
    #if DEBUG
        Sys.MessagePort = COM1;
        Sys.ShowInfo();
    #endif 
	

	sp1=SerialPort::GetMessagePort();
    SerialPort::GetMessagePort()->Register(OnUsart1Read);
    
    Sys.AddTask(LedTask, &led1, 0, 500, "LedTask");
    Sys.AddTask(TimerTask, &led1, 0, 1000, "TimerTask");
    Sys.AddTask(Test12, 0, 600, 1000, "Test");
	
	IList::Test();
	ADS1232Test();
	//streamtest();
	//ModbusTest();
	//InterruptTest();
	
	//InterruptTest();
		
    Sys.Start();
}
