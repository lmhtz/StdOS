#pragma once

#include "stm32f10x.h"
#include "Spi.h"


#define macSPI_APBxClock_FUN                        RCC_APB2PeriphClockCmd
#define macSPI_CLK                                  RCC_APB2Periph_SPI1

class W25QXXX
{
    public:
		W25QXXX(Spi * spi);
	
		Spi * pSpi;
		OutputPort *pcs;//Ƭѡ��
	
        void Init(void);
        void SectorErase(uint SectorAddr);
        void BulkErase(void);
        void PageWrite(byte *pBuffer, uint WriteAddr, ushort NumByteToWrite);
        void BufferWrite(byte *pBuffer, uint WriteAddr, ushort NumByteToWrite);
        void BufferRead(byte *pBuffer, uint ReadAddr, ushort NumByteToRead);
        uint ReadID(void);
        uint ReadDeviceID(void);
        void StartReadSequence(uint ReadAddr);
        void PowerDown(void);
        void WAKEUP(void);
                    
        void WriteEnable(void);
        void WaitForWriteEnd(void);
};
