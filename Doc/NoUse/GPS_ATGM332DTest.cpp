#include "Drivers\GPS_ATGM332D.h"
#include "Sys.h"
#include "Device\SerialPort.h"

//#define _GPS_ATGM332D_TEST_H
#ifdef _GPS_ATGM332D_TEST_H
uint32_t OnUsart2Read(ITransport *transport, Buffer &bs, void *para, void *para2)
{
		bs.Show(true);
	//gps1216.Analysis((uint8_t*)bs.GetBuffer());//�����ַ���
	//gps1216.Show();				//��ʾ��Ϣ	
	return 0;
}

SerialPort *sp2;
uint8_t com2rx[500], com2tx[500];
void GPS_ATGM332DTest()
{
	sp2 = new SerialPort(COM2);
	sp2->Rx.SetBuf(com2rx, ArrayLength(com2rx));
	sp2->Tx.SetBuf(com2tx, ArrayLength(com2tx));
	sp2->Register(OnUsart2Read);
	sp2->SetBaudRate(9600);
	sp2->Open();
}

#endif // _GPS_ATGM332DTest
