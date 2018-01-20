#include "SerialPort.h"
#include "Drivers\AT24CXX.h"
#include "Drivers\W25QXXX.h"
#include "SString.h"
#include "string.h"
#include "List.h"
#include "Spi.h"
#include "Flash.h"
#include "App\lcd_dr.h"
#include "TInterrupt.h"
#include "Timer.h"
#include "TTime.h"
#include "Drivers\RX8025T.h"

//InputPort paa11(PA11,false);
OutputPort paaa1(PA11);

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
    paaa1 = 0;
}
uint time6cnt;
uint OnUsart1Read(ITransport *transport, Buffer &bs, void *para, void *para2)
{
	time6cnt++;
    //transport->Write(bs);
	bs.Show(true);
    return 0;
}

uint OnUsart3Read(ITransport *transport, Buffer &bs, void *para, void *para2)
{
	time6cnt++;
    //transport->Write(bs);
	bs.Show(true);
    return 0;
}

//SerialPort *sp2;
//SerialPort *sp3;
void OCM240128Test();
void PCF8563Test();
int main(void)
{
    Sys.Init();
    #if DEBUG
        Sys.MessagePort = COM3;
        Sys.ShowInfo();
    #endif 	

    SerialPort::GetMessagePort()->Register(OnUsart1Read);
		
//	sp3=new SerialPort(COM3);
//	sp3->Register(OnUsart3Read);
//	sp3->Open();
	
    //Sys.AddTask(LedTask, &led1, 0, 500, "LedTask");
		OCM240128Test();
		PCF8563Test();
    Sys.Start();
}
