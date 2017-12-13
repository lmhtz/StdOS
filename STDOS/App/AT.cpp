#include  "Sys.h"
#include "Device\SerialPort.h"
#include "AT.h"
#include "Buffer.h"
#include "SString.h"
#include "WaitHandle.h"

static float latitude;
static float longitude;

int ParseFail(const char *a1,const Buffer bs)
{
	int ret =0;
	
	if(bs.Length())
	{
		auto v5 = 0;
		if(bs.Length() > 0 && bs[0] == 32)
			v5 = 1;
		if(bs.Length() > v5 && bs[v5] == 13)
			++v5;
		if(bs.Length() > v5 && bs[v5]== 10)
			++v5;
		auto v8 = bs.Sub(v5,1);
		auto v7 = v8.AsString();
		if(v7)
		{
			auto v6 = bs.Length();
			debug_printf("",a1,v6);
			v7.Show(true);
		}
	}
	return ret;
}

AT::AT()
{
	latitude = 0;
	longitude = 0;
}
AT::~AT()
{
	
}
float AT::GetLatitude()
{
	return latitude;
}
float AT::GetLongitude()
{
	return longitude;
}
// 打开与关闭
bool AT::Open()
{	
	this->Port->Register(AT::OnPortReceive);
	this->Port->Open();
	return true;
}
void AT::Close()
{
	
}
String AT::Send(const String& cmd, cstring expect, cstring expect2, uint msTimeout, bool trim)
{	
	cmd.Trim();
	cmd.Show();
	auto p=(SerialPort*)this->Port;
	if(this->Port)
	{
		p->Write(cmd);
		if(!cmd.EndsWith("\r\n"))
			p->Printf("\r\n");		
	}
	
	WaitHandle waitHandle;
	
	waitHandle.WaitOne(msTimeout);
	return "OK";
}
String AT::Send(const String& cmd, uint msTimeout, bool trim)
{
	String pcmd=cmd;
	if((cmd.StartsWith("AT",0)) &&(!cmd.EndsWith("\r\n")))
	{
		pcmd.Concat("\r\n");
	}
	
	return this->Send(pcmd,"OK","ERROR",msTimeout,trim);;
}

// 发送命令，自动检测并加上\r\n，等待响应OK
bool AT::SendCmd(const String& cmd, uint msTimeout)
{	
	debug_printf("\r\nSend CMD: ");
	auto strrcv= this->Send(cmd,msTimeout,false);
	return "OK";
	return strrcv.Contains("OK");
}
// 分析关键字。返回被用掉的字节数
uint AT::ParseReply(const Buffer& bs)
{
	return 0;
}	
// 引发数据到达事件
uint AT::OnReceive(Buffer& bs, void* param)
{
	uint ret=0;
	bs.Show();
	return;
	if(bs.Length())
	{
		auto v20=bs.AsString();
		//v20.Split('a');
		auto v18=v20;
		auto v13=v20;
		auto v9 = 0;
		if(v18.Contains("+UGNSINF: 1"))
		{
			latitude = v13.ToFloat();
			longitude = v13.ToFloat();
		}
		else
		{
			auto v6 = 0;
			while(v6>=0 &&bs.Length()>v6)
			{
				auto v7=v6;
				auto v8 = v20.IndexOf(this->DataKey,v6);
				v6=v8;
				if(v8 < 0 )
					v9 = bs.Length() - v7;
				else
					v9= v8 - v7;
				if(v9 > 0 )
				{
					if(this->_Expect)
					{
						auto v17 = bs.Sub(v7,1);
						this->ParseReply(v17);
					}
					else if(this->Received)
					{
						auto v17=bs.Sub(v7,1);
						//ParaseFail("NoExpect",v17);
					}
					else
					{
						v6 = 0;
					}
				}
			}
		}
	}
	else
	{
		
		ret=0;
	}
	bs.Show();
	return ret;
}
#include "Drivers\Esp8266.h"
extern Esp8266 esp;
uint AT::OnPortReceive(ITransport* sender, Buffer& bs, void* param, void* param2)
{
	return esp.At.OnReceive(bs,param);
	//return this->OnReceive(bs, sender, param);
}
