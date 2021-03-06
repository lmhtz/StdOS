#ifndef __Pwm_H__
#define __Pwm_H__

#include "Timer.h"

class AlternatePort;

// 脉冲宽度调制
class Pwm : public Timer
{
public:
	uint16_t	Pulse[4];	// 每个通道的占空比
	bool	Polarity	= true;	// 极性。默认true高电平
	bool	IdleState	= true;	// 空闲状态。
    //uint32_t	Remap;		// 重映射。0不映射，其它为实际映射数字
	AlternatePort*	Ports[4];
	uint8_t	Enabled[4];	// 每个通道是否启用

	Pwm(TIMER index);		// index 定时器编号
	virtual ~Pwm();

	virtual void Open();
	virtual void Close();
	virtual void Config();

	void Flush();	// 刷新输出

	void SetPulse(int idx, uint16_t pulse);
	// 设置占空比，0~255
	void SetDuty(int idx, uint8_t duty);
	uint8_t GetDuty(int idx);
};

// PWM输出数据
class PwmData : public Pwm
{
public:
	// 连续调整占空比
	uint16_t* Pulses;		// 宽度数组
	uint8_t	PulseCount;	// 宽度个数
	uint8_t	Channel;	// 需要连续调整的通道。仅支持连续调整1个通道。默认0表示第一个通道
	uint8_t	PulseIndex;	// 索引。使用数组中哪一个位置的数据
	bool	Repeated;	// 是否重复

	PwmData(TIMER index);

	virtual void Config();

protected:
	virtual void OnInterrupt();
};

#endif
