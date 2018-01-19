#include "Drivers\OCM240128.h"
#include "Sys.h"

#define _OCM240128TEST
#ifdef  _OCM240128TEST

OCM240128 ocm;
void OCM240128Test()
{
	ocm.SetPin(PA6,PA7,PA5,PA1,PA0,PA8,PA9,PA11,PA4);
	ocm.LCD_DataPort_Out();
	ocm.LCD_CMDPort_Out();
	ocm.LCD_Init();		 //Һ����ʼ��
	ocm.LCD_Clr();		 //	����
	ocm.LCD_TEST();
}

#endif //  _OCM240128TEST

const byte  hanzi_16x16[][32]={
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x01,0x00,0x01,0x00,0x7F,0xFC,0x01,0x00,0x3F,0xF8,0x01,0x00,0xFF,0xFE,0x00,0x00,
0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x50,0x10,0x20,

/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x01,0x00,0x02,0x00,0x1F,0xF0,0x10,0x10,0x12,0x10,0x11,0x50,0x10,0x20,0x10,0x00,
0x1F,0xFC,0x02,0x04,0x22,0x24,0x22,0x24,0x3F,0xE4,0x00,0x04,0x00,0x28,0x00,0x10,
};
const byte  GB3212[][32]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x41,0x04,0x43,0x04,0x85,0x02,0x81,0x02,0x81,0x02,
0x81,0x02,0x81,0x02,0x41,0x04,0x41,0x04,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x43,0x84,0x44,0x44,0x80,0x42,0x80,0x42,0x80,0x82,
0x81,0x02,0x82,0x02,0x44,0x04,0x47,0xC4,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x47,0xC4,0x40,0x44,0x80,0x82,0x81,0x02,0x83,0x02,
0x80,0x82,0x80,0x42,0x44,0x44,0x43,0x84,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x41,0x04,0x42,0x04,0x82,0x02,0x84,0x82,0x84,0x82,
0x88,0x82,0x8F,0xE2,0x40,0x84,0x40,0x84,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x47,0xC4,0x44,0x04,0x84,0x02,0x87,0x82,0x80,0x42,
0x80,0x42,0x80,0x42,0x48,0x84,0x47,0x04,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x41,0x04,0x42,0x04,0x82,0x02,0x84,0x02,0x85,0x82,
0x86,0x42,0x84,0x42,0x44,0x44,0x43,0x84,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x47,0xC4,0x40,0x44,0x80,0x82,0x80,0x82,0x81,0x02,
0x81,0x02,0x81,0x02,0x41,0x04,0x41,0x04,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,

/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x43,0x84,0x44,0x44,0x84,0x42,0x84,0x42,0x83,0x82,
0x84,0x42,0x84,0x42,0x44,0x44,0x43,0x84,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x43,0x84,0x44,0x44,0x84,0x42,0x84,0x42,0x83,0xC2,
0x80,0x42,0x80,0x82,0x41,0x04,0x42,0x04,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x49,0xC4,0x5A,0x24,0xAA,0x22,0x8A,0x22,0x8A,0x22,
0x8A,0x22,0x8A,0x22,0x4A,0x24,0x49,0xC4,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x00,0x00,0x0E,0xFC,0xEA,0x08,0xAA,0x08,0xAA,0xE8,0xAA,0xA8,0xAC,0xA8,0xAA,0xA8,
0xAA,0xA8,0xAA,0xA8,0xEA,0xE8,0xAA,0xA8,0x0C,0x08,0x08,0x08,0x08,0x28,0x08,0x10,
};
const byte  shuzi_16x16[][32]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x41,0x04,0x43,0x04,0x85,0x02,0x81,0x02,0x81,0x02,
0x81,0x02,0x81,0x02,0x41,0x04,0x41,0x04,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
/*--  ??:  ?  --*/
/*--  ??12;  ??????????:?x?=16x16   --*/
0x07,0xC0,0x18,0x30,0x20,0x08,0x43,0x84,0x44,0x44,0x80,0x42,0x80,0x42,0x80,0x82,
0x81,0x02,0x82,0x02,0x44,0x04,0x47,0xC4,0x20,0x08,0x18,0x30,0x07,0xC0,0x00,0x00,
};
