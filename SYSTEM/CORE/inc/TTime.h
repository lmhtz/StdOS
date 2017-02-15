#pragma once

#include "Type.h"

class TTime
{
	public:
		TTime();
		UInt64 Ms() const;//系统启动以来的毫秒数
		UInt64 Current() const;//系统启动以来的毫秒
		uint Seconds();//系统时间
		void SetTime(UInt64 seconds);//设置系统当前时间,Unix格式秒数
		void Sleep(uint us);//延时us		
					
		uint TicksToUs(uint ticks) const;
		uint UsToTicks(uint us) const;
	
		UInt64 mCurrent;//系统启动以来的毫秒数	
		UInt64 CurrentTicks;//滴答数。比微妙还短的超高精度时间		
};
extern TTime Time; //系统时间，不建议用户直接使用
