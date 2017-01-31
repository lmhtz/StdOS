#include <stdio.h>
#include "Type.h"
#include "stm32f10x.h"
#include "SerialPortOld.h"
#include "W24xxx.h"
#include "W25qxx.h"
#include "multi_button.h"
#include "InputPortOld.h"
#include "Sys.h"
#include "WatchDog.h"
#include "Port.h"
#include "Buffer.h"
#include "CString.h"
#include "string.h"
#include "DateTime.h"
#include "TimeCost.h"
#include "List.h"

void ledflash();
OutputPort led1(PB0, true);
OutputPort led2(PF7, true);
OutputPort led3(PF8, true);
//按键 PC13 PA0

InputPortOld exti(PC13); //PA1 PB3

WatchDog dog(3000);
void feeddog()
{
    dog.Feed();
}

void OnKeyPress(Pin pin, bool onoff)
{
    //led1.Write(onoff);
    led2 = !led2;
    printf("中断引脚：%d 值%d \n", pin, onoff);
}

static uint OnUsartRead(ITransport *transport, Buffer &bs, void *para)
{
    SerialPortOld *sp = (SerialPortOld*)para;
    debug_printf("%s 收到：[%d]", sp->Name, bs.Length());
    bs.Show(true);
    sp->SendBuffer(bs.GetBuffer());

    return 0;
}

SerialPortOld sp1(COM1);
SerialPortOld sp2(COM2);
SerialPortOld sp3(COM3);
/*
KEY PA0 
 */
//系统初始化
void ComTimers();
void assert_failed(uint8_t* file, uint32_t line);

void ledflash()
{
    //	led1=!led1;
    //	led2=!led2;
    led3 = !led3;
}

byte USART_RX_BUF[100]; //接收缓冲,最大USART_REC_LEN个字节.
extern uint com1timeidle; //串口1空闲时间
extern CFIFORing com1buf; //串口1接收缓冲区

extern uint com2timeidle; //串口2空闲时间
extern CFIFORing com2buf; //串口2接收缓冲区

extern uint com3timeidle; //串口3空闲时间
extern CFIFORing com3buf; //串口3接收缓冲区
//串口接收通信定时器
void ComTimers()
{
    com1timeidle++;
    com2timeidle++;
    com3timeidle++;

    if (com1timeidle > 3)
    {
        com1timeidle = 0;
        ushort len = com1buf.GetLength();
        if (len >= 1)
        {
            com1buf.Pop(USART_RX_BUF, 0, len);
            sp1.OnUsartReceive(USART_RX_BUF, len);
        }
        com1buf.Reset();
    }

    if (com2timeidle > 3)
    {
        com2timeidle = 0;
        ushort len = com2buf.GetLength();
        if (len >= 1)
        {
            com2buf.Pop(USART_RX_BUF, 0, len);
            sp2.OnUsartReceive(USART_RX_BUF, len);
        }
        com2buf.Reset();
    }

    if (com3timeidle > 3)
    {
        com3timeidle = 0;
        ushort len = com3buf.GetLength();
        if (len >= 1)
        {
            com3buf.Pop(USART_RX_BUF, 0, len);
            sp3.OnUsartReceive(USART_RX_BUF, len);
        }
        com3buf.Reset();
    }
}
//显示系统时间
void ShowSysTime()
{
	printf("%d-%d\n",Sys.Ms(),Time.Ms());
}

int main(void)
{
     Sys.MessagePort = COM1;
    Sys.Init();
    Sys.ShowInfo();
    sp1.Register(OnUsartRead, &sp1);
    sp2.Register(OnUsartRead, &sp2);
    sp3.Register(OnUsartRead, &sp3);
    sp1.Open();
    sp2.Open();
    sp3.Open();

	TimeCost tc; 
    exti.InitOld();
    exti.On();
    exti.RegisterOld(OnKeyPress);
	tc.Show();
	List<float> floatList;

for(int i=1;i<7;i++)
{
floatList.Add(* new float(i+0.6));
}
floatList.PrintList();
float b=3.6;
float *pa=floatList.Find(b);
if(pa)
{
	floatList.Remove(*pa);
}
floatList.PrintList();

    Sys.AddTask(ComTimers, 0, 1, 1, "串口数据接收定时器"); //1毫秒周期循环
    Sys.AddTask(feeddog, 0, 0, 10, "看门狗"); //看门狗-喂狗
    Sys.AddTask(ledflash, 0, 5, 50, "状态指示灯");
	Sys.AddTask(ShowSysTime, 0, 5, 1000, "系统时间显示");
    	
	Sys.Start();
}
