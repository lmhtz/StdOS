#ifndef _STDLILNK_H
#define _STDLILNK_H


#include "stm32f10x.h"
#include "FIFOBuffer.h"
#include "DataFrame.h"
#include "USART.h"

class StdLink
{
public:
	DataFrame txFrame;
	DataFrame rxFrame;
	FIFOBuffer<uint8_t, USART_RX_BUFFER_SIZE>  mRxBuf;  //USART Rx Buffer
	USART &com;
public:
	StdLink(USART &uart);
	bool CheckFrame();
	bool Send();
private:
	bool CheckFrame(DataFrame &df);
private:
	bool Get(uint8_t & da);
	bool Gets(uint8_t * pData, uint16_t num);

};

#endif // !_STDLILNK_H
