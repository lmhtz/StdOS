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

uint OnUsart1Read(ITransport *transport, Buffer &bs, void *para, void *para2)
{
    //transport->Write(bs);
	bs.Show(true);
    return 0;
}

uint OnUsart3Read(ITransport *transport, Buffer &bs, void *para, void *para2)
{	
    /*transport->Write(bs);
	bs.Show(true);*/
	debug_printf("hehe\r\n");
    return 0;
}

SerialPort *sp3;
byte com3rx[500],com3tx[500];

int main(void)
{
	Sys.Init();
#if DEBUG
	Sys.MessagePort = COM1;
	Sys.ShowInfo();
#endif 	

	SerialPort::GetMessagePort()->Register(OnUsart1Read);

	sp3 = new SerialPort(COM3);
	sp3->Rx.SetBuf(com3rx, ArrayLength(com3rx));
	sp3->Tx.SetBuf(com3tx, ArrayLength(com3tx));
	sp3->Register(OnUsart3Read);
	sp3->SetBaudRate(38400);
	sp3->Open();

	Sys.AddTask(LedTask, &led1, 0, 500, "LedTask");
	Sys.Start();
}
