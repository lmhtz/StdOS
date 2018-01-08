#include "I2C.h"

I2C::I2C()
{
	
}
I2C::~I2C()
{
	
}
// 打开设备
bool I2C::Open()
{
	return true;
}
// 关闭设备
void I2C::Close()
{
	
}
// 新会话向指定地址写入
bool I2C::Write(int addr, const Buffer &bs)
{
    return false;
}

bool I2C::Write(int addr, byte data)
{
    return false;
}

// 新会话从指定地址读取
uint I2C::Read(int addr, Buffer &bs)
{
    return 0;
}

byte I2C::Read(int addr)
{
    return 0;
}

ushort I2C::Read2(int addr)
{
    return 0;
}

uint I2C::Read4(int addr)
{
    return 0;
}

bool I2C::SendAddress(int addr, bool tx)
{
    return false;
}

bool I2C::SendSubAddr(int addr)
{
    return false;
}

////////////////////////////////////////////////////////////////
////////////////////I2CScope/////////////////////////////////////
////////////////////////////////////////////////////////////////











////////////////////////////////////////////////////////////////
////////////////////HardI2C/////////////////////////////////////
////////////////////////////////////////////////////////////////







////////////////////////////////////////////////////////////////
////////////////////SoftI2C/////////////////////////////////////
////////////////////////////////////////////////////////////////

// 使用端口和最大速度初始化，因为需要分频，实际速度小于等于该速度
SoftI2C::SoftI2C(uint speedHz)
{
	this->_delay=4;
	this->SCL.OpenDrain = true;
    this->SDA.OpenDrain = true;
	this->SCL.Invert = false;
	this->SDA.Invert = false;    
}
SoftI2C::~SoftI2C(){}

void SoftI2C::SetPin(Pin scl, Pin sda)
{
	this->SCL.Set(scl);
    this->SDA.Set(sda);
	
	this->SCL.Open();
	this->SDA.Open();

    this->SCL = 0;
    this->SDA = 1;
    this->SCL = 1;
}

void SoftI2C::GetPin(Pin *scl, Pin *sda)
{

}

void SoftI2C::Start()
{
    /* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
    this->SDA = 1;
    this->SCL = 1;
    this->Delay();
    this->SDA = 0;
    this->Delay();
    this->SCL = 0;
    this->Delay();
}

void SoftI2C::Stop()
{
    /* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
    this->SDA = 0;
    this->SCL = 1;
    this->Delay();
    this->SDA = 1;
}

void SoftI2C::WriteByte(byte dat)
{
    byte i;

    /* 先发送字节的高位bit7 */
    for (i = 0; i < 8; i++)
    {
        if (dat &0x80)
        {
            this->SDA = 1;
        }
        else
        {
            this->SDA = 0;
        }
        this->Delay();
        this->SCL = 1;
        this->Delay();
        this->SCL = 0;
        if (i == 7)
        {
            this->SDA = 1; // 释放总线
        }
        dat <<= 1; /* 左移一个bit */
        this->Delay();
    }
}

byte SoftI2C::ReadByte()
{
    byte i;
    byte value;

    /* 读到第1个bit为数据的bit7 */
    value = 0;
    for (i = 0; i < 8; i++)
    {
        value <<= 1;
        this->SCL = 1;
        this->Delay();
        if (this->SDA.ReadInput())
        {
            value++;
        }
        this->SCL = 0;
        this->Delay();
    }
    return value;
}

void SoftI2C::Ack(bool ack)
{
    if (ack)
    {
        this->SDA = 0; /* CPU驱动SDA = 0 */
        this->Delay();
        this->SCL = 1; /* CPU产生1个时钟 */
        this->Delay();
        this->SCL = 0;
        this->Delay();
        this->SDA = 1;
        /*CPU释放SDA总线 */
    }
    else
    {
        this->SDA = 1; /* CPU驱动SDA = 1 */
        this->Delay();
        this->SCL = 1; /* CPU产生1个时钟 */
        this->Delay();
        this->SCL = 0;
        this->Delay();
    }
}

//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
bool SoftI2C::WaitAck(int retry)
{
    byte re;

    this->SDA = 1; /* CPU释放SDA总线 */
    this->Delay();
    this->SCL = 1; /* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
    this->Delay();

    if (this->SDA.ReadInput())
    /* CPU读取SDA口线状态 */
    {
        re = 1;
    }
    else
    {
        re = 0;
    }
    this->SCL = 0;
    this->Delay();
    return re;
}

void SoftI2C::OnOpen(){}
void SoftI2C::OnClose(){}


void SoftI2C::Delay()
{

    #if 0
        //Sys.Delay(us);
        /*
        因为有系统代码，导致Delay不是很准，经常大于1us
        右移23位时：
        48M = 5;
        72M = 8;
        108M= 12;
        120m= 14;
         */
        // 72M = 4
        int t = Sys.Clock >> 21;
        while (t-- > 0)
            ;
    #endif 
    byte i;

    /*　
    下面的时间是通过安富莱AX-Pro逻辑分析仪测试得到的。
    CPU主频72MHz时，在内部Flash运行, MDK工程不优化
    循环次数为10时，SCL频率 = 205KHz 
    循环次数为7时，SCL频率 = 347KHz， SCL高电平时间1.5us，SCL低电平时间2.87us 
    循环次数为5时，SCL频率 = 421KHz， SCL高电平时间1.25us，SCL低电平时间2.375us 

    IAR工程编译效率高，不能设置为7
     */
    for (i = 0; i < 10; i++)
        ;
}
