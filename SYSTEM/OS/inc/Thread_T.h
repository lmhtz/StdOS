#pragma once
#include "Type.h"
class CThread
{
	public:
		CThread();
		~CThread();
	public:
		uint TickCur;//当前计数值	
		uint intervalms;//回调间隔
		bool canRun;//可以执行
		uint delaycnt;//延时时间		
	public:
		void (*callback)(void);//回调函数
		void checkRun();//判断是否运行
		void SetPara(void (*callback)(void),uint intervalms,uint delaycntms=0);//设置参数
};
