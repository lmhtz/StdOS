#include "Timer.h"
#include "stm32f10x_rcc.h"

#define TIMS {TIM1,TIM2,TIM3,TIM4,TIM5}


static TIM_TypeDef *const g_Timers[] = TIMS;
Timer **Timer::Timers = NULL;
const byte Timer::TimerCount = ArrayLength(g_Timers);

Timer::Timer(TIM_TypeDef *timer)
{
    assert_param(timer);

    // 初始化静态数组
    if (!Timers)
    {
        Timers = new Timer *[TimerCount];
        #if 0
            ArrayZero2(Timers, TimerCount);
        #endif 
    }

    //TIM_TypeDef* g_Timers[] = TIMS;
    byte idx = 0xFF;
    #if 0
        for (int i = 0; i < ArrayLength(g_Timers); i++)
        {
            if (g_Timers[i] == timer)
            {
                idx = i;
                break;
            }
        }
    #endif 
    assert_param(idx <= ArrayLength(g_Timers));

    Timers[idx] = this;

    _index = idx;
    _port = g_Timers[idx];

    // 默认情况下，预分频到1MHz，然后1000个周期，即是1ms中断一次
    /*Prescaler = Sys.Clock / 1000000;
    Period = 1000;*/
    SetFrequency(10);

    Opened = false;
    #if 0
        _Handler = NULL;
    #endif 
}

Timer::~Timer()
{
    if (Opened)
        Close();
    #if 0
        if (_Handler)
            Register(NULL);
    #endif 
    Timers[_index] = NULL;
}

// 创建指定索引的定时器，如果已有则直接返回，默认0xFF表示随机分配
Timer *Timer::Create(byte index)
{
    // 特殊处理随机分配
    if (index == 0xFF)
    {
        // 初始化静态数组
        if (!Timers)
        {
            Timers = new Timer *[TimerCount];
            #if 0
                ArrayZero2(Timers, TimerCount);
            #endif 
        }

        // 找到第一个可用的位置，没有被使用，并且该位置定时器存在
        byte i = 0;
        for (; i < TimerCount && (Timers[i] || !g_Timers[i]); i++)
            ;

        if (i >= TimerCount)
        {
            debug_printf("Timer::Create 失败！没有空闲定时器可用！\r\n");
            return NULL;
        }

        index = i;
    }

    assert_param(index < TimerCount);

    if (Timers[index])
        return Timers[index];
    else
        return new Timer(g_Timers[index]);
}
void Timer::Open()	// 开始定时器
{
	 #if DEBUG
        // 获取当前频率
        RCC_ClocksTypeDef clock;
        RCC_GetClocksFreq(&clock);

        #if defined(STM32F1) || defined(STM32F4)
            uint clk = clock.PCLK1_Frequency;
            if ((uint)_port &0x00010000)
                clk = clock.PCLK2_Frequency;
            clk <<= 1;
        #elif defined(STM32F0)
            uint clk = clock.PCLK_Frequency << 1;
        #endif 

        uint fre = clk / Prescaler / Period;
        debug_printf("Timer%d::Start Prescaler=%d Period=%d Frequency=%d\r\n", _index + 1, Prescaler, Period, fre);
    #endif 

    // 打开时钟
    ClockCmd(true);

    // 关闭。不再需要，跟上面ClockCmd的效果一样
    //TIM_DeInit(_port);

    // 配置时钟
    TIM_TimeBaseInitTypeDef _timer;
    TIM_TimeBaseStructInit(&_timer);
    _timer.TIM_Period = Period - 1;
    _timer.TIM_Prescaler = Prescaler - 1;
    //_timer.TIM_ClockDivision = 0x0;
    _timer.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(_port, &_timer);

    //        TIM_PrescalerConfig(_port, _timer.TIM_Period,TIM_PSCReloadMode_Immediate);                // 分频数立即加载
    // 打开中断
    //TIM_ITConfig(_port, TIM_IT_Update | TIM_IT_Trigger, ENABLE);
    TIM_ITConfig(_port, TIM_IT_Update, ENABLE);
    //TIM_UpdateRequestConfig(_port, TIM_UpdateSource_Regular);
    TIM_ClearFlag(_port, TIM_FLAG_Update); // 清楚标志位  必须要有！！ 否则 开启中断立马中断给你看
    //        TIM_ClearITPendingBit(_port, TIM_IT_Update);
    // 打开计数
    TIM_Cmd(_port, ENABLE);

    Opened = true;
}
void Timer::Close()	// 停止定时器
{
	if (!Opened)
        return ;

    debug_printf("Timer%d::Stop\r\n", _index + 1);

    // 关闭时钟
    ClockCmd(false);
    TIM_ITConfig(_port, TIM_IT_Update, DISABLE);
    TIM_ClearITPendingBit(_port, TIM_IT_Update); // 仅清除中断标志位 关闭不可靠
    TIM_Cmd(_port, DISABLE);

    Opened = false;
}
void Timer::Config()
{
}
void Timer::OnInit()
{
}
	void Timer::OnOpen()
	{
	}
	void Timer::OnClose()
	{
	}

void Timer::ClockCmd(bool state)
{
    FunctionalState st = state ? ENABLE : DISABLE;
    switch (_index + 1)
    {
        case 1:
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, st);
            break;
        case 2:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, st);
            break;
        case 3:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, st);
            break;
            #if defined(STM32F1) && defined(STM32F4)
            case 4:
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, st);
                break;
            case 5:
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, st);
                break;
            #endif 
        case 6:
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, st);
            break;
            #if defined(STM32F1) && defined(STM32F4)
            case 7:
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, st);
                break;
            case 8:
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, st);
                break;
            #endif 
            #ifdef STM32F4
            case 9:
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, st);
                break;
            case 10:
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, st);
                break;
            case 11:
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, st);
                break;
            case 12:
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, st);
                break;
            case 13:
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, st);
                break;
            case 14:
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, st);
                break;
            #endif 
            #if defined(STM32F0)
            case 14:
                RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, st);
                break;
            case 15:
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, st);
                break;
            case 16:
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16, st);
                break;
            case 17:
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17, st);
                break;
            #endif 
    }
}

// 设置预分频目标，比如1MHz
/*void Timer::SetScaler(uint scaler)
{
assert_param(scaler);

uint ps = Sys.Clock / scaler;
assert_param(ps > 0 && ps <= 0xFFFF);
}*/

// 设置频率，自动计算预分频
void Timer::SetFrequency(uint frequency)
{
    // 获取当前频率
    RCC_ClocksTypeDef clock;
    RCC_GetClocksFreq(&clock);

    #if defined(STM32F1) || defined(STM32F4)
        uint clk = clock.PCLK1_Frequency;
        if ((uint)_port &0x00010000)
            clk = clock.PCLK2_Frequency;
        clk <<= 1;
    #elif defined(STM32F0)
        uint clk = clock.PCLK_Frequency << 1;
    #endif 

    assert_param(frequency > 0 && frequency <= clk);

    uint s = 1;
    uint p = s / frequency;

    uint pre = clk / s; // prescaler

    //while (pre >= 0x10000 || p == 0) { // prescaler 太大
    // 周期刚好为1也不行，配置的时候需要先减去1，就变成了0
    while (pre >= 0x10000 || p <= 1)
    {
        // prescaler 太大
        if (p >= 0x80000000)
            return ;
        s *= 10;
        pre /= 10;
        p = s / frequency;
    }

    if (_index + 1 != 2 && _index + 1 != 5)
    {
        // 16 bit timer
        while (p >= 0x10000)
        {
            // period too large
            if (pre > 0x8000)
                return ;
            pre <<= 1;
            p >>= 1;
        }
    }

    Prescaler = pre;
    Period = p;

    // 如果已启动定时器，则重新配置一下，让新设置生效
    if (Opened)
    {
        TIM_TimeBaseInitTypeDef _timer;
        TIM_TimeBaseStructInit(&_timer);
        _timer.TIM_Period = Period - 1;
        _timer.TIM_Prescaler = Prescaler - 1;
        //_timer.TIM_ClockDivision = 0x0;
        _timer.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(_port, &_timer);
    }
}

#if 0
    void Timer::Register(EventHandler handler, void *param)
    {
        _Handler = handler;
        _Param = param;

        int irqs[] = TIM_IRQns;
        if (handler)
        {
            Interrupt.SetPriority(irqs[_index]);
            Interrupt.Activate(irqs[_index], OnHandler, this);
        }
        else
            Interrupt.Deactivate(irqs[_index]);
    }
#endif 
void Timer::OnHandler(ushort num, void *param)
{
    Timer *timer = (Timer*)param;
    if (timer)
        timer->OnInterrupt();
}

void Timer::OnInterrupt()
{
    // 检查指定的 TIM 中断发生
    if (TIM_GetITStatus(_port, TIM_IT_Update) == RESET)
        return ;
    // 必须清除TIMx的中断待处理位，否则会频繁中断
    TIM_ClearITPendingBit(_port, TIM_IT_Update);
    #if 0
        if (_Handler)
            _Handler(this, _Param);
    #endif 
}
