#include "TInterrupt.h"
#include "SerialPort.h"
#include "Task.h"

SerialPort::SerialPort()
{
    Init();
}

SerialPort::SerialPort(COM index, int baudRate)
{
    this->Set(index,baudRate);    
}

void SerialPort::Set(COM index, int baudRate)
{
    this->Index = index;
    this->_baudRate = baudRate;
	
    // 根据系统时钟自动计算默认波特率
    if (this->_baudRate <= 0)
    {
        //		int clock = Sys.Clock;
        //		if(clock > 72)
        //			_baudRate = 2048000;
        //		else if (clock > 36)
        //			_baudRate = 1024000;
        //		else
        this->_baudRate = 256000;
    }
    if (this->_baudRate <= 9600)
        this->ByteTime = 1000 / (this->_baudRate / 10) + 1;
    else
        this->ByteTime = 1;
}
void SerialPort::Set(uint8_t dataBits, uint8_t parity, uint8_t stopBits)
{
	this->_dataBits=dataBits;
	this->_parity=parity;
	this->_stopBits=stopBits;
}

// 刷出某个端口中的数据
bool SerialPort::Flush(int times)
{
  this->Set485(true);
  while ( (!this->Txx.Empty()) && times > 0 )
  {
    times = this->SendData(this->Txx.Dequeue(), times);
  }
  this->Set485(false);
  return times > 0;
}
void SerialPort::SetBaudRate(int baudRate)
{	
	this->_baudRate=baudRate;
}

SerialPort *printf_sp;
bool isInFPutc;//正在串口输出
static char com1rx[1024],com1tx[1024];
uint32_t OnUsart1Read123(ITransport *transport, Buffer &bs, void *para, void *para2)
{
	//临时借调用
	return 0;
}
SerialPort *SerialPort::GetMessagePort()
{
	if (printf_sp && Sys.MessagePort != printf_sp->Index)
	{
		if ( printf_sp )
			printf_sp->Close();
		printf_sp=nullptr;
	}
	if ( !printf_sp )
	{
		if(Sys.MessagePort==COM_NONE)		
			return nullptr;
		if ( isInFPutc )
			return nullptr;
		isInFPutc = true;
		
		printf_sp=new SerialPort((COM)Sys.MessagePort);
		printf_sp->Txx.SetBuf(com1tx,ArrayLength(com1tx));
		printf_sp->Rxx.SetBuf(com1rx,ArrayLength(com1rx));
		printf_sp->Register(OnUsart1Read123);
		printf_sp->Open();
		
		isInFPutc=false;
	}
	
    return printf_sp;
}

// 向某个端口写入数据。如果size为0，则把data当作字符串，一直发送直到遇到\0为止
bool SerialPort::OnWrite(const Buffer& bs)
{
	bool ret;
	
	if(bs.Length())
	{	
		TInterrupt::GlobalDisable();
		this->Txx.Write(bs);
		TInterrupt::GlobalEnable();
		this->Set485(true);
		this->OnWrite2();
		//this->Set485(false);//添加
		ret=true;
	}
	else
	{
		ret=false;
	}
	
    return ret;
}

void SerialPort::Set485(bool flag)
{
    if (this->RS485)
    {       
        this->RS485->Write(flag);
    }
}

void SerialPort::ReceiveTask()
{
	char buf[512];
	Buffer bs(buf,ArrayLength(buf));
	this->Rxx.Read(bs);
	this->OnReceive(bs,this); 
	((Task*)(this->_task))->Set(false,0);
}

static char *itoa(int value, char *string, int radix)
{
    int i, d;
    int flag = 0;
    char *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *=  - 1;

    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d *i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;
}
#include <stdarg.h>
//模拟printf
void SerialPort::Printf(char *Data, ...)
{
	const char *s;
    int d;
    char buf[16];

    char bufSend[200];
    int bufSendPos;
    //int bufSendMax = ArrayLength(bufSend);

    bufSendPos = 0;

    va_list ap;
    va_start(ap, Data);

    while (*Data != 0)
    // 判断是否到达字符串结束符
    {
        if (*Data == 0x5c)
        //'\'
        {
            switch (*++Data)
            {
                case 'r':
                    //回车符
                    bufSend[bufSendPos++] = 0X0D;
                    Data++;
                    break;

                case 'n':
                    //换行符
                    bufSend[bufSendPos++] = 0X0A;
                    Data++;
                    break;

                default:
                    Data++;
                    break;
            }
        }

        else if (*Data == '%')
        {
            //
            switch (*++Data)
            {
                case 's':
                    //字符串
                    s = va_arg(ap, const char*);
                    for (;  *s; s++)
                    {
                        bufSend[bufSendPos++] =  *s;
                    }
                    Data++;
                    break;
                case 'd':
                    //十进制
                    d = va_arg(ap, int);
                    itoa(d, buf, 10);
                    for (s = buf;  *s; s++)
                    {
                        bufSend[bufSendPos++] =  *s;
                    }
                    Data++;
                    break;
                default:
                    Data++;
                    break;
            }
        }
        else
            bufSend[bufSendPos++] =  *Data++;
    }
	Buffer bs(bufSend,bufSendPos);
	this->Write(bs);
}

void SerialPort::OnRxHandler()
{
	((Task*)(this->_task))->Set(true, 0);
}

void SerialPort::Init()
{
	this->Index = COM_NONE;
	RS485 = NULL;
	Error = 0;

	Remap = 0;
}
