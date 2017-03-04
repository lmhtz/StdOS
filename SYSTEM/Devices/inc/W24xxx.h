#pragma once 
#include "SoftI2C.h"

#define EEPTEST 1
typedef enum
{
    AT24C01 = 127, AT24C02 = 255, AT24C04 = 511, AT24C08 = 1023, AT24C16 = 2047, AT24C32 = 4095, AT24C64 = 8191, AT24C128 = 16383, AT24C256 = 32767, AT24C512 = (32767 *2), AT24C1024 = (32767 *4), AT24C2048 = (32767 *8)
} EW24XXType;


class CW24xxx
{
    public:
        CW24xxx(Pin pinsck, Pin pinsda, EW24XXType devtype, byte devaddr = 0xA0, uint wnms = 5); //写延时时间       
        byte CheckOk();
        #if EEPTEST
            void Test(void);
        #endif 
        byte ReadBytes(byte *pBuffer, ushort bufpos, uint addr, int size);
        byte WriteBytes(byte *pBuffer, ushort bufpos, uint addr, int size);
        byte ReadByte(ushort address);
        byte WriteByte(ushort address, byte da);
		
		OutputPort *pinWP;//保护引脚
    private:
        byte checkDevice();
		ushort jsPageSize(uint type); //计算存储页大小
        byte writePage(byte *buf, ushort bufpos, ushort addr, uint size); //页内写
        byte readPage(byte *buf, ushort bufpos, ushort addr, uint size); //页内读
        byte bufwr(byte *buf, ushort bufpos, ushort addr, uint size, byte wr); //读写集中操作1写 0读
		
		CSoftI2C *pi2c;
        EW24XXType deviceType; //器件类型
        uint pageSize; //存储页大小
        uint writedelaynms; //写延时	    
        byte devAddr; //设备地址        
};
