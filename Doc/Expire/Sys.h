#ifndef _Sys_H_
#define _Sys_H_

#include <stddef.h>
#include "Core\Type.h"
#include "Core\DateTime.h"
#include "Core\List.h"
#include "Core\Delegate.h"

/* 引脚定义 */
#include "Platform\Pin.h"

extern "C"
{
#ifdef DEBUG
	#define debug_printf StdPrintf	
#else
	#define debug_printf(format, ...)
#endif
}

#ifdef DEBUG
#define assert(expr, msg) ((expr) ? (void)0 : assert_failed2(msg, (const char*)__FILE__, __LINE__))

#else

#define assert(expr, msg) ((void)0)

#endif

//class SystemConfig;

// 系统类
class TSys
{
public:
    uint32_t	Clock;  	// 系统时钟
    uint32_t	CystalClock;// 晶振时钟
	uint32_t	HeapSize;	// 堆大小
	uint32_t	StackSize;	// 栈大小

	uint8_t	ID[12];		// 芯片ID。
    uint16_t	FlashSize;	// 芯片Flash容量。
    //uint16_t	RAMSize;	// 芯片RAM容量

	//const SystemConfig*	Config;	// 系统设置

    TSys();

	void Init();     	// 初始化系统
	void ShowInfo() const;
	
	uint64_t	Ms() const;		// 系统启动后的毫秒数
	uint32_t	Seconds() const;	// 系统绝对当前时间，秒

    void Sleep(int ms) const; // 毫秒级延迟
    void Delay(int us) const; // 微秒级延迟
	
	// 延迟异步重启
	void Reboot(int msDelay = 0) const;
	// 打开全局中断
	void GlobalEnable();
	// 关闭全局中断
	void GlobalDisable();
		
private:
	void Reset() const;
	void OnInit();
	void OnShowInfo() const;

public:
	// 创建任务，返回任务编号。dueTime首次调度时间ms，period调度间隔ms，-1表示仅处理一次
	uint32_t AddTask(Action func, void* param, int dueTime = 0, int period = 0, cstring name = nullptr) const;
	template<typename T>
	uint32_t AddTask(void(T::*func)(), T* target, int dueTime = 0, int period = 0, cstring name = nullptr)
	{
		return AddTask(*(Action*)&func, target, dueTime, period, name);
	}
	void RemoveTask(uint32_t& taskid) const;
	// 设置任务的开关状态，同时运行指定任务最近一次调度的时间，0表示马上调度
	bool SetTask(uint32_t taskid, bool enable, int msNextTime = -1) const;
	// 改变任务周期
	bool SetTaskPeriod(uint32_t taskid, int period) const;

	bool Started;
	void Start();	// 开始系统大循环
};

extern TSys Sys;		// 创建一个全局的Sys对象  会在main函数之前执行构造函数（！！！！！）

// 系统设置
//class SystemConfig
//{
//public:
//	// 操作系统
//	uint32_t	Ver;		// 系统版本。Version格式
//	char	Name[16];	// 系统名称
//
//	// 硬件
//	uint32_t	HardVer;	// 硬件版本
//
//	// 应用软件
//	uint16_t	Code;		// 产品种类
//	uint32_t	AppVer;		// 产品版本
//	char	Company[16];// 公司
//	char	Product[16];// 产品批次
//
//	char	DevID[16];	// 设备编码
//	char	Server[32];	// 服务器。重置后先尝试厂商前端，再尝试原服务器
//	char	Token[32];	// 访问服务器的令牌
//
//	uint32_t	Expire;		// 有效期。1970以来的秒数。
//	
//	uint16_t	Checksum;	// 校验
//};

#define STDOS_VERSION "0.5.2018.1030" //版本号

#endif //_Sys_H_

/*

v0.1.2018.0820  使用C++11实现，实现F1 F4 F1的GPIO和串口、IIC、SPI、中断管理
v0.2.2018.		串口发送、接收采用DMA方式实现。
v0.3.2018       更换串口实现方式
v0.4.2018.1024  启动过程优化，启动时关闭全局中断，启动完成开启，防止启动异常
v0.5.2018.1030  系统统计信息精简，去除不必要内容
*/
