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
        CW24xxx(PinPort pinsck, PinPort pinsda, EW24XXType devtype, byte devaddr = 0xA0, uint32_t wnms = 5); //写延时时间
        ~CW24xxx();
        byte CheckOk();
    public:
        #if EEPTEST
            void Test(void);
        #endif 
        byte ReadBytes(byte *_pReadBuf, uint16_t bufpos, uint16_t _usAddress, uint32_t _usSize);
        byte WriteBytes(byte *_pWriteBuf, uint16_t bufpos, uint16_t _usAddress, uint32_t _usSize);
        byte ReadByte(uint16_t address);
        byte WriteByte(uint16_t address, byte da);
    private:
        byte checkDevice();
        EW24XXType deviceType; //器件类型
        byte devAddr; //设备地址
        uint32_t pageSize; //存储页大小
        CSoftI2C *pi2c;
        uint32_t writedelaynms; //写延时	
    private:
        uint16_t jsPageSize(uint32_t type); //计算存储页大小
        byte writePage(byte *buf, uint16_t bufpos, uint16_t addr, uint32_t len); //页内写
        byte readPage(byte *buf, uint16_t bufpos, uint16_t addr, uint32_t len); //页内读
        byte bufwr(byte *buf, uint16_t bufpos, uint16_t addr, uint32_t len, byte wr); //读写集中操作1写 0读
};
