#include <stdio.h>
#include "stm32f10x.h"
#include "Port.h"
#include "TInterrupt.h"

void SetEXIT(int pinIndex, bool enable);

#define GPIO_Mode_IN GPIO_Mode_IN_FLOATING
#define GPIO_Mode_AF GPIO_Mode_AF_OD
#define GPIO_OType_OD GPIO_Mode_Out_OD
#define GPIO_OType_PP GPIO_Mode_Out_PP
#define GPIO_Mode_OUT GPIO_Mode_Out_OD


// 获取组和针脚
#define _GROUP(PIN) ((GPIO_TypeDef *) (GPIOA_BASE + (((PIN) & (ushort)0xF0) << 6)))
#define _RCC_APB2(PIN) (RCC_APB2Periph_GPIOA << (PIN >> 4))


#if defined(STM32F1) || defined(STM32F4)
    static const int PORT_IRQns[] = 
    {
        EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn, EXTI4_IRQn,  // 5个基础的
        EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn,  // EXTI9_5
        EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn  // EXTI15_10
    };
#elif defined(STM32F0)
    static const int PORT_IRQns[] = 
    {
        EXTI0_1_IRQn, EXTI0_1_IRQn,  // 基础
        EXTI2_3_IRQn, EXTI2_3_IRQn,  // 基础
        EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn,
            EXTI4_15_IRQn  // EXTI15_10
    };
#endif 
GPIO_TypeDef *IndexToGroup(byte index)
{
    return ((GPIO_TypeDef*)(GPIOA_BASE + (index << 10)));
}

byte GroupToIndex(GPIO_TypeDef *group)
{
    return (byte)(((int)group - GPIOA_BASE) >> 10);
}

/*
端口基本功能
 */
Port::Port()
{
    this->_Pin = P0;
    this->State = NULL;
    //this->PinBit = 0;
}

#ifndef TINY	
    Port::~Port()
    {
        #if defined(STM32F1)
            // 恢复为初始化状态
            //            ushort bits = PinBit;
            //            int config = InitState &0xFFFFFFFF;
            //            for (int i = 0; i < 16 && bits; i++, bits >>= 1)
            //            {
            //                if (i == 7)
            //                    config = InitState >> 32;
            //                if (bits &1)
            //                {
            //                    uint shift = (i &7) << 2; // 每引脚4位
            //                    uint mask = 0xF << shift; // 屏蔽掉其它位

            //                    GPIO_TypeDef *port = (GPIO_TypeDef *)this->State;
            //                    if (i &0x08)
            //                    {
            //                        // bit 8 - 15
            //                        port->CRH = port->CRH &~mask | (config &mask);
            //                    }
            //                    else
            //                    {
            //                        // bit 0-7
            //                        port->CRL = port->CRL &~mask | (config &mask);
            //                    }
            //                }
            //            }
        #endif 
    }
#endif 

/*
单一引脚初始化
 */
Port &Port::Set(Pin pin)
{
    //assert_param(pin != P0);

    this->_Pin = pin;
    //    if (_Pin != P0)
    //    {
    //        this->State = IndexToGroup(pin >> 4);
    //        //        PinBit = 1 << (pin &0x0F);
    //    }
    //    else
    //    {
    //        this->State = NULL;
    //        //        PinBit = 0;
    //    }

    #if defined(STM32F1)
        // 整组引脚的初始状态，析构时有选择恢复
        //        if (_Pin != P0)
        //            InitState = ((UInt64)((GPIO_TypeDef *)this->State)->CRH << 32) + ((GPIO_TypeDef *)this->State)->CRL;
    #endif 


    this->Open();
    return  *this;
}

bool Port::Empty()const
{
    return _Pin == P0;
}

bool Port::Open()
{
    if (this->Opened == false)
    {
        if (_Pin != P0)
        {
            // 打开时钟
            int gi = _Pin >> 4;
            #ifdef STM32F0
                RCC_AHBPeriphClockCmd(RCC_AHBENR_GPIOAEN << gi, ENABLE);
            #elif defined(STM32F1)
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA << gi, ENABLE);
            #elif defined(STM32F4)
                RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA << gi, ENABLE);
            #endif 

            #ifdef STM32F1
                // PA15/PB3/PB4 需要关闭JTAG
                switch (_Pin)
                {
                    case PA15:
                    case PB3:
                    case PB4:
                        {
                            debug_printf("Close JTAG for P%c%d\r\n", _PIN_NAME(_Pin));

                            // PA15是jtag接口中的一员 想要使用 必须开启remap
                            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
                            GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
                            break;
                        }
                }
            #endif 
			 GPIO_InitTypeDef gpio;
            // 特别要慎重，有些结构体成员可能因为没有初始化而酿成大错
            GPIO_StructInit(&gpio);
			gpio.GPIO_Pin = 1 << (this->_Pin &0x0F);	
			this->OnOpen(&gpio);            

            GPIO_Init(IndexToGroup(this->_Pin >> 4), &gpio);
        }

        this->Opened = true;
    }
    return true;
}

void Port::Close()
{
    this->OnClose();
    this->Opened = false;
}

void Port::Clear(){}
bool Port::Read()const
{
    return false;
}

void Port::OnOpen(void *param)
{
    GPIO_InitTypeDef *gpio = (GPIO_InitTypeDef*)param;    
    gpio->GPIO_Speed = GPIO_Speed_50MHz;
}

void Port::OnClose(){}


//#define GPIO_Mode_IN GPIO_Mode_IN_FLOATING
//#define GPIO_Mode_AF GPIO_Mode_AF_OD
//#define GPIO_OType_OD GPIO_Mode_Out_OD
//#define GPIO_OType_PP GPIO_Mode_Out_PP
//#define GPIO_Mode_OUT GPIO_Mode_Out_OD

OutputPort::OutputPort()
{   
}

OutputPort::OutputPort(Pin pin)
{    
    Set(pin);
}

OutputPort::OutputPort(Pin pin, byte invert, bool openDrain, byte speed)
{    
	this->Invert=invert;
	this->OpenDrain=openDrain;	
    Set(pin);
}

//void OutputPort::OnConfig(GPIO_InitTypeDef &gpio)
//{
#if 0
    #ifndef STM32F4
        assert_param(Speed == 2 || Speed == 10 || Speed == 50);
    #else 
        assert_param(Speed == 2 || Speed == 25 || Speed == 50 || Speed == 100);
    #endif 

    //    Port::OnConfig(gpio);

    switch (Speed)
    {
        case 2:
            gpio.GPIO_Speed = GPIO_Speed_2MHz;
            break;
            #ifndef STM32F4
            case 10:
                gpio.GPIO_Speed = GPIO_Speed_10MHz;
                break;
            #else 
            case 25:
                gpio.GPIO_Speed = GPIO_Speed_25MHz;
                break;
            case 100:
                gpio.GPIO_Speed = GPIO_Speed_100MHz;
                break;
            #endif 
        case 50:
            gpio.GPIO_Speed = GPIO_Speed_50MHz;
            break;
    }

    #ifdef STM32F1
        gpio.GPIO_Mode = OpenDrain ? GPIO_Mode_Out_OD : GPIO_Mode_Out_PP;
    #else 
        gpio.GPIO_Mode = GPIO_Mode_OUT;
        gpio.GPIO_OType = OpenDrain ? GPIO_OType_OD : GPIO_OType_PP;
    #endif 

    // 配置之前，需要根据倒置情况来设定初始状态，也就是在打开端口之前必须明确端口高低状态
    ushort dat = GPIO_ReadOutputData(((GPIO_TypeDef*)this->State));
    //    if (!Invert)
    //        dat &= ~PinBit;
    //    else
    //        dat |= PinBit;
    GPIO_Write(((GPIO_TypeDef*)this->State), dat);
#endif 
//}

/*
整组读取
 */
//ushort OutputPort::ReadGroup()
//{
//    return GPIO_ReadOutputData(((GPIO_TypeDef *)this->State));
//}

bool OutputPort::Read()const
{
    // 转为bool时会转为0/1
    //    bool rs = GPIO_ReadOutputData(((GPIO_TypeDef *)this->State)) &PinBit;
    bool rs = GPIO_ReadOutputData(((GPIO_TypeDef*)this->State));
    return rs ^ Invert;
}

bool OutputPort::ReadInput()const
{
    //    bool rs = GPIO_ReadInputData(((GPIO_TypeDef *)this->State)) &PinBit;
    bool rs = GPIO_ReadInputData(((GPIO_TypeDef*)this->State));
    return rs ^ Invert;
}

//bool OutputPort::Read(Pin pin)
//{
//    GPIO_TypeDef *group = _GROUP(pin);
//    return (group->IDR >> (pin &0xF)) &1;
//}

void OutputPort::Write(bool value)const
{
    if (this->Invert)
    {
        if (value)
        {
            GPIO_ResetBits(_GROUP(this->_Pin), _PORT(this->_Pin));
        }
        else
        {
            GPIO_SetBits(_GROUP(this->_Pin), _PORT(this->_Pin));
        }
    }
    else
    {
        if (value)
        {
            GPIO_SetBits(_GROUP(this->_Pin), _PORT(this->_Pin));
        }
        else
        {
            GPIO_ResetBits(_GROUP(this->_Pin), _PORT(this->_Pin));
        }
    }
}

//OutputPort::operator bool()
//{
//    return Read();
//}

//void OutputPort::WriteGroup(ushort value)
//{
//    GPIO_Write(((GPIO_TypeDef *)this->State), value);
//}

void OutputPort::Up(int ms)const
{
    Write(true);
    Sys.Sleep(ms);
    Write(false);
}

void OutputPort::Down(int ms)const
{
    Write(false);
    Sys.Sleep(ms);
    Write(true);
}

void OutputPort::Blink(int times, int ms)const
{
    bool flag = true;
    for (int i = 0; i < times; i++)
    {
        Write(flag);
        flag = !flag;
        Sys.Sleep(ms);
    }
    Write(false);
}

void OutputPort::OnOpen(void *param)
{
	Port::OnOpen(param);
    GPIO_InitTypeDef *gpio = (GPIO_InitTypeDef*)param;
    if (this->OpenDrain)
    {
        gpio->GPIO_Mode = GPIO_Mode_Out_OD;
    }
    else
    {
        gpio->GPIO_Mode = GPIO_Mode_Out_PP;
    } 
}

void OutputPort::OpenPin(void *param){}
/*
设置端口状态
 */
void OutputPort::Write(Pin pin, bool value)
{
    if (value)
        GPIO_SetBits(_GROUP(pin), _PORT(pin));
    else
        GPIO_ResetBits(_GROUP(pin), _PORT(pin));
}

#if 0
    void OutputPort::Init(bool invert, bool openDrain, uint speed)
    {
        OpenDrain = openDrain;
        Speed = speed;
        Invert = invert;
    }
#endif 
AlternatePort::AlternatePort(): OutputPort()
{
    //    Init(false, false);
}

AlternatePort::AlternatePort(Pin pin): OutputPort(pin){

}

AlternatePort::AlternatePort(Pin pin, byte invert, bool openDrain, byte speed)
{
    //    Init(invert, openDrain, speed);
    Set(pin);
}

void AlternatePort::OpenPin(void *param)
{
	GPIO_InitTypeDef *gpio = (GPIO_InitTypeDef*)param;
	#ifdef STM32F1
            gpio->GPIO_Mode = this->OpenDrain ? GPIO_Mode_AF_OD : GPIO_Mode_AF_PP;
        #else 
            gpio->GPIO_Mode = GPIO_Mode_AF;
            gpio->GPIO_OType = OpenDrain ? GPIO_OType_OD : GPIO_OType_PP;
        #endif 
}
#if 0
    void AnalogInPort::OnConfig(GPIO_InitTypeDef &gpio)
    {
        //    Port::OnConfig(gpio);

        #ifdef STM32F1
            gpio.GPIO_Mode = GPIO_Mode_AIN; //
        #else 
            gpio.GPIO_Mode = GPIO_Mode_AN;
            //gpio.GPIO_OType = !Floating ? GPIO_OType_OD : GPIO_OType_PP;
        #endif 
    }
#endif 

InputPort::InputPort(Pin pin, bool floating, PuPd pupd)
{
    //    Init(floating, pupd);
    Set(pin);
}

InputPort::InputPort(){

}

void InputPort::OnOpen(void *param)
{
	Port::OnOpen(param);
GPIO_InitTypeDef *gpio = (GPIO_InitTypeDef*)param;
	#ifdef STM32F1
            if (Floating)
                gpio->GPIO_Mode = GPIO_Mode_IN_FLOATING;
            else if (Pull == UP)
                gpio->GPIO_Mode = GPIO_Mode_IPU;
            else if (Pull == DOWN)
                gpio->GPIO_Mode = GPIO_Mode_IPD;
            // 这里很不确定，需要根据实际进行调整
        #else 
            gpio->GPIO_Mode = GPIO_Mode_IN;
            gpio->GPIO_OType = !Floating ? GPIO_OType_OD : GPIO_OType_PP;
        #endif 
}
void InputPort::OnClose(){

}
#if 0
    void InputPort::Init(bool floating, PuPd pupd)
    {
        Pull = pupd;
        Floating = floating;

        _Registed = false;
        //ShakeTime = 20;
        // 有些应用的输入口需要极高的灵敏度，这个时候不需要抖动检测
        ShakeTime = 0;
        Invert = false;
    }
#endif 

/* 中断状态结构体 */
/* 一共16条中断线，意味着同一条线每一组只能有一个引脚使用中断 */
typedef struct TIntState
{
    Pin Pin;
    InputPort inputport;
    InputPort::IOReadHandler Handler; // 委托事件
    void *Param; // 事件参数，一般用来作为事件挂载者的对象，然后借助静态方法调用成员方法	
    bool OldValue;

    uint ShakeTime; // 抖动时间	
    int Used; // 被使用次数。对于前5行中断来说，这个只会是1，对于后面的中断线来说，可能多个
} IntState;

// 16条中断线
static IntState InterruptState[16];
static bool hasInitState = false;

InputPort::~InputPort()
{
    // 取消所有中断
    //    if (_Registed)
    {
        //       Register(NULL);
    }
}

#if 0
    ushort InputPort::ReadGroup() // 整组读取
    {
        return GPIO_ReadInputData(((GPIO_TypeDef*)this->State));
    }
#endif 
// 读取本组所有引脚，任意脚为true则返回true，主要为单一引脚服务
bool InputPort::Read()const
{
    // 转为bool时会转为0/1
    //    bool rs = GPIO_ReadInputData(((GPIO_TypeDef *)this->State)) &PinBit;
    bool rs = GPIO_ReadInputData(((GPIO_TypeDef*)this->State));
    return rs ^ Invert;
}

#if 0
    bool InputPort::Read(Pin pin)
    {
        GPIO_TypeDef *group = _GROUP(pin);
        return (group->IDR >> (pin &0xF)) &1;
    }
#endif 
#if 0
    // 注册回调  及中断使能
    void InputPort::Register(IOReadHandler handler, void *param)
    {
        //    if (!PinBit)
        //        return ;

        // 检查并初始化中断线数组
        if (!hasInitState)
        {
            for (int i = 0; i < 16; i++)
            {
                IntState *state1 = &InterruptState[i];
                state1->Pin = P0;
                state1->Handler = NULL;
                state1->Used = 0;
            }
            hasInitState = true;
        }

        byte gi = _Pin >> 4;
        gi = gi;
        //    ushort n = PinBit;
        ushort n = 0;
        for (int i = 0; i < 16 && n != 0; i++)
        {
            // 如果设置了这一位，则注册事件
            if (n &0x01)
            {
                // 注册中断事件
                if (handler)
                {
                    IntState *state2 = &InterruptState[i];
                    state2->ShakeTime = ShakeTime;
                    RegisterInput(gi, i, handler, param);
                }
                else
                {
                    UnRegisterInput(i);
                }
            }
            n >>= 1;
        }

        //    _Registed = handler != NULL;
    }
#endif 
void GPIO_ISR(int num) // 0 <= num <= 15
{
    if (!hasInitState)
    {
        return ;
    }
    IntState *state3 = InterruptState + num;
    if (!state3)
    {
        return ;
    }
    #if 0
        uint bit = 1 << num;
    #endif 
    bool value;
    //    value = InputPort::Read(state3->Pin);
    //byte line = EXTI_Line0 << num;
    // 如果未指定委托，则不处理
    if (!state3->Handler)
    {
        return ;
    }
    #if 0
        // 默认20us抖动时间
        uint shakeTime = state->ShakeTime;
    #endif 
    #if 0
        do
        {
            EXTI->PR = bit; // 重置挂起位
            value = InputPort::Read(state->Pin); // 获取引脚状态
            if (shakeTime > 0)
            {
                // 值必须有变动才触发
                if (value == state->OldValue)
                {
                    return ;
                }
                Time.Sleep(shakeTime); // 避免抖动
            }
        }
        while (EXTI->PR &bit); // 如果再次挂起则重复
    #endif 
    //EXTI_ClearITPendingBit(line);
    #if 0
        // 值必须有变动才触发
        if (shakeTime > 0 && value == state->OldValue)
            return ;
        state->OldValue = value;
    #endif 
    if (state3->Handler)
    {
        // 新值value为true，说明是上升，第二个参数是down，所以取非
        state3->Handler(&(state3->inputport), value, state3->Param);
    }
}

//所有中断线处理
void EXTI_IRQHandler(ushort num, void *param)
{
    #if defined(STM32F1) || defined(STM32F4)
        // EXTI0 - EXTI4
        if (num <= EXTI4_IRQn)
        {
            GPIO_ISR(num - EXTI0_IRQn);
        }
        else if (num == EXTI9_5_IRQn)
        {
            // EXTI5 - EXTI9
            uint pending = EXTI->PR &EXTI->IMR &0x03E0; // pending bits 5..9
            int num = 5;
            pending >>= 5;
            do
            {
                if (pending &1)
                {
                    GPIO_ISR(num);
                }
                num++;
                pending >>= 1;
            }
            while (pending);
        }
        else if (num == EXTI15_10_IRQn)
        {
            // EXTI10 - EXTI15
            uint pending = EXTI->PR &EXTI->IMR &0xFC00; // pending bits 10..15
            int num = 10;
            pending >>= 10;
            do
            {
                if (pending &1)
                {
                    GPIO_ISR(num);
                }
                num++;
                pending >>= 1;
            }
            while (pending);
        }
    #elif defined(STM32F0)
        switch (num)
        {
            case EXTI0_1_IRQn:
                {
                    uint pending = EXTI->PR &EXTI->IMR &0x0003; // pending bits 0..1
                    int num = 0;
                    pending >>= 0;
                    do
                    {
                        if (pending &1)
                            GPIO_ISR(num);
                        num++;
                        pending >>= 1;
                    }
                    while (pending);
                    break;
                }
            case EXTI2_3_IRQn:
                {
                    uint pending = EXTI->PR &EXTI->IMR &0x000c; // pending bits 3..2
                    int num = 2;
                    pending >>= 2;
                    do
                    {
                        if (pending &1)
                            GPIO_ISR(num);
                        num++;
                        pending >>= 1;
                    }
                    while (pending);
                }
            case EXTI4_15_IRQn:
                {
                    uint pending = EXTI->PR &EXTI->IMR &0xFFF0; // pending bits 4..15
                    int num = 4;
                    pending >>= 4;
                    do
                    {
                        if (pending &1)
                            GPIO_ISR(num);
                        num++;
                        pending >>= 1;
                    }
                    while (pending);
                }
        }
    #endif 
}

//中断线打开、关闭
void SetEXIT(int pinIndex, bool enable)
{
    /* 配置EXTI中断线 */
    EXTI_InitTypeDef ext;
    EXTI_StructInit(&ext);
    ext.EXTI_Line = EXTI_Line0 << pinIndex;
    ext.EXTI_Mode = EXTI_Mode_Interrupt;
    ext.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 上升沿下降沿触发
    ext.EXTI_LineCmd = enable ? ENABLE : DISABLE;
    EXTI_Init(&ext);
}

#if 0
    // 申请引脚中断托管
    void InputPort::RegisterInput(int groupIndex, int pinIndex, IOReadHandler handler, void *param)
    {
        IntState *state4 = &InterruptState[pinIndex];
        Pin pin = (Pin)((groupIndex << 4) + pinIndex);
        // 检查是否已经注册到别的引脚上
        if (state4->Pin != pin && state4->Pin != P0)
        {
            return ;
        }
        state4->Pin = pin;
        state4->Handler = handler;
        state4->Param = param;
        //    state4->OldValue = Read(pin); // 预先保存当前状态值，后面跳变时触发中断

        // 打开时钟，选择端口作为端口EXTI时钟线
        #if defined(STM32F0) || defined(STM32F4)
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
            SYSCFG_EXTILineConfig(groupIndex, pinIndex);
        #elif defined(STM32F1)
            RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
            GPIO_EXTILineConfig(groupIndex, pinIndex);
        #endif 

        SetEXIT(pinIndex, true);
        // 打开并设置EXTI中断为低优先级
        Interrupt.SetPriority(PORT_IRQns[pinIndex], 1);
        state4->Used++;
        if (state4->Used == 1)
        {
            Interrupt.Activate(PORT_IRQns[pinIndex], EXTI_IRQHandler, this);
        }
    }
#endif 
#if 0
    void InputPort::UnRegisterInput(int pinIndex)
    {
        IntState *state5 = &InterruptState[pinIndex];
        // 取消注册
        state5->Pin = P0;
        state5->Handler = 0;

        SetEXIT(pinIndex, false);

        state5->Used--;
        if (state5->Used == 0)
        {
            Interrupt.Deactivate(PORT_IRQns[pinIndex]);
        }
    }
#endif
