/*
*********************************************************************************************************
*
*	模块名称 : 汉字点阵字库。有效显示区 高16x宽15, 最右一列留白
*	文件名称 : hz16.c
*	版    本 : V1.0
*	说    明 : 只包含本程序用到汉字字库
*	修改记录 :
*		版本号  日期       作者    说明
*		v1.0    2011-09-08 armfly  ST固件库V3.5.0版本。
*
*	Copyright (C), 2010-2011, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "fonts.h"

/*
	FLASH中内嵌小字库，只包括本程序用到的汉字点阵
	每行点阵数据，头2字节是汉子的内码，后面32字节是16点阵汉子的字模数据。
*/

#ifdef USE_SMALL_FONT

unsigned char const g_Hz16[] = {
0xA3,0xAC, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,// ， //
           0x0C,0x00,0x1E,0x00,0x1E,0x00,0x0C,0x00,0x04,0x00,0x08,0x00,0x10,0x00,0x00,0x00,

0xB2,0xBB, 0x00,0x04,0xFF,0xFE,0x00,0x80,0x00,0x80,0x01,0x00,0x01,0x00,0x03,0x40,0x05,0x20,// 不 //
           0x09,0x18,0x11,0x0C,0x21,0x04,0x41,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,

0xB4,0xA5, 0x20,0x20,0x20,0x20,0x3C,0x20,0x48,0x24,0x51,0xFE,0xFD,0x24,0x55,0x24,0x55,0x24,// 触 //
           0x7D,0x24,0x55,0x24,0x55,0xFC,0x7D,0x20,0x54,0x28,0x54,0x3C,0x55,0xE2,0x8C,0x82,

0xB5,0xE3, 0x02,0x00,0x02,0x00,0x02,0x08,0x03,0xFC,0x02,0x00,0x02,0x10,0x3F,0xF8,0x20,0x10,// 点 //
           0x20,0x10,0x20,0x10,0x3F,0xF0,0x00,0x00,0x29,0x10,0x24,0xC8,0x44,0x44,0x80,0x04,

0xB5,0xE7, 0x02,0x00,0x02,0x00,0x02,0x10,0x7F,0xF8,0x42,0x10,0x42,0x10,0x7F,0xF0,0x42,0x10,// 电 //
           0x42,0x10,0x7F,0xF0,0x42,0x10,0x02,0x00,0x02,0x04,0x02,0x04,0x01,0xFC,0x00,0x00,

0xB6,0xAF, 0x00,0x40,0x08,0x40,0x7C,0x40,0x00,0x44,0x05,0xFE,0xFE,0x44,0x10,0x44,0x10,0x44,// 动 //
           0x20,0x44,0x24,0x44,0x42,0x84,0xFE,0x84,0x41,0x04,0x01,0x04,0x02,0x28,0x04,0x10,

0xB7,0xB5, 0x00,0x08,0x40,0x1C,0x33,0xE0,0x12,0x00,0x02,0x00,0x02,0xF8,0xF2,0x08,0x12,0x90,// 返 //
           0x12,0x50,0x12,0x20,0x12,0x50,0x14,0x8C,0x15,0x04,0x28,0x00,0x44,0x06,0x03,0xFC,

0xBB,0xD8, 0x00,0x00,0x00,0x04,0x7F,0xFE,0x40,0x04,0x40,0x44,0x47,0xE4,0x44,0x44,0x44,0x44,// 回 //
           0x44,0x44,0x44,0x44,0x47,0xC4,0x44,0x44,0x40,0x04,0x7F,0xFC,0x40,0x04,0x00,0x00,

0xBD,0xAB, 0x10,0x80,0x10,0x80,0x11,0xF8,0x91,0x08,0x73,0x10,0x34,0xA0,0x10,0x40,0x10,0x94,// 将 //
           0x1F,0xFE,0x30,0x10,0x52,0x10,0xD1,0x90,0x10,0x90,0x10,0x10,0x10,0x50,0x10,0x20,

0xBD,0xE7, 0x00,0x10,0x1F,0xF8,0x11,0x10,0x11,0x10,0x1F,0xF0,0x11,0x10,0x11,0x10,0x1F,0xF0,// 界 //
           0x02,0x80,0x04,0x60,0x0C,0x50,0x34,0x4E,0xC4,0x44,0x04,0x40,0x08,0x40,0x10,0x40,

0xC3,0xE6, 0x00,0x04,0xFF,0xFE,0x02,0x00,0x04,0x04,0x7F,0xFE,0x44,0x44,0x44,0x44,0x47,0xC4,// 面 //
           0x44,0x44,0x44,0x44,0x44,0x44,0x47,0xC4,0x44,0x44,0x44,0x44,0x7F,0xFC,0x40,0x04,

0xC3,0xEB, 0x04,0x20,0x0E,0x20,0x78,0x20,0x08,0x20,0x08,0xA8,0xFE,0xA6,0x08,0xA2,0x1D,0x20,// 秒 //
           0x1A,0x24,0x28,0x24,0x28,0x28,0x48,0x10,0x88,0x20,0x08,0x40,0x08,0x80,0x0B,0x00,

0xC3,0xFE, 0x11,0x10,0x11,0x14,0x1F,0xFE,0x11,0x10,0xFD,0x18,0x13,0xFC,0x16,0x08,0x1B,0xF8,// 摸 //
           0x32,0x08,0xD3,0xF8,0x10,0x40,0x1F,0xFE,0x10,0x40,0x10,0xA0,0x51,0x1C,0x26,0x08,

0xC4,0xDA, 0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x04,0x7F,0xFE,0x41,0x04,0x41,0x04,0x42,0x04,// 内 //
           0x42,0x84,0x44,0x64,0x48,0x34,0x50,0x14,0x40,0x04,0x40,0x04,0x40,0x14,0x40,0x08,

0xC6,0xC1, 0x00,0x08,0x3F,0xFC,0x20,0x08,0x20,0x08,0x3F,0xF8,0x22,0x20,0x21,0x48,0x2F,0xFC,// 屏 //
           0x22,0x20,0x22,0x24,0x3F,0xFE,0x22,0x20,0x22,0x20,0x42,0x20,0x84,0x20,0x08,0x20,

0xC8,0xDD, 0x02,0x00,0x01,0x00,0x7F,0xFE,0x40,0x02,0x84,0x44,0x09,0x30,0x12,0x90,0x04,0x40,// 容 //
           0x08,0x20,0x10,0x10,0x2F,0xEE,0xC8,0x24,0x08,0x20,0x08,0x20,0x0F,0xE0,0x08,0x20,

0xCA,0xAE, 0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x04,0xFF,0xFE,0x01,0x00,// 十 //
           0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,

0xCB,0xC4, 0x00,0x00,0x00,0x04,0x7F,0xFE,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,0x44,// 四 //
           0x44,0x44,0x44,0x3C,0x48,0x04,0x50,0x04,0x40,0x04,0x7F,0xFC,0x40,0x04,0x00,0x00,

0xCE,0xDE, 0x00,0x20,0x3F,0xF0,0x02,0x00,0x02,0x00,0x02,0x00,0x02,0x08,0x7F,0xFC,0x02,0x80,// 无 //
           0x02,0x80,0x04,0x80,0x04,0x80,0x08,0x80,0x08,0x82,0x10,0x82,0x20,0x7E,0x40,0x00,

0xD0,0xA3, 0x10,0x40,0x10,0x20,0x10,0x04,0x13,0xFE,0xFC,0x00,0x10,0x88,0x31,0x06,0x3A,0x8A,// 校 //
           0x54,0x88,0x50,0x50,0x90,0x50,0x10,0x20,0x10,0x50,0x10,0x88,0x13,0x0E,0x1C,0x04,

0xD0,0xE8, 0x1F,0xF0,0x01,0x00,0x7F,0xFE,0x51,0x12,0x8D,0x64,0x11,0x10,0x01,0x04,0xFF,0xFE,// 需 //
           0x02,0x00,0x04,0x08,0x3F,0xFC,0x24,0x88,0x24,0x88,0x24,0x88,0x24,0xA8,0x20,0x10,

0xD2,0xAA, 0x00,0x08,0x7F,0xFC,0x04,0x40,0x3F,0xF8,0x24,0x48,0x24,0x48,0x3F,0xF8,0x02,0x00,// 要 //
           0x02,0x04,0xFF,0xFE,0x04,0x20,0x08,0x20,0x06,0x40,0x01,0x80,0x06,0x60,0x38,0x10,

0xD6,0xF7, 0x02,0x00,0x01,0x00,0x01,0x08,0x7F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x10,// 主 //
           0x3F,0xF8,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x04,0xFF,0xFE,0x00,0x00,

0xD7,0xBC, 0x01,0x40,0x41,0x20,0x31,0x24,0x13,0xFE,0x02,0x20,0x16,0x28,0x1B,0xFC,0x12,0x20,// 准 //
           0x22,0x28,0xE3,0xFC,0x22,0x20,0x22,0x20,0x22,0x24,0x23,0xFE,0x22,0x00,0x02,0x00,

0xD7,0xD4, 0x01,0x00,0x02,0x00,0x04,0x10,0x1F,0xF8,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,// 自 //
           0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,0x10,0x10,0x10,0x10,0x1F,0xF0,0x10,0x10,

0xD7,0xE8, 0x00,0x00,0x7C,0x08,0x45,0xFC,0x49,0x08,0x49,0x08,0x51,0x08,0x49,0xF8,0x49,0x08,// 阻 //
           0x45,0x08,0x45,0x08,0x45,0xF8,0x69,0x08,0x51,0x08,0x41,0x08,0x47,0xFE,0x40,0x00,

/* 最后一行必须用0xFF,0xFF结束，这是字库数组结束标志 */
0xFF,0xFF

};

#else
	unsigned char const g_Hz16[] = {0xFF, 0xFF};
#endif

