#include "Port.h"
#include "stm32f10x.h"

GPIO_TypeDef *IndexToGroup(byte index);

void Port_OnOpen(Pin pin)
{
    int pinindex;
    int portname;

    if (pin == PA15 || pin == PB3 || pin == PB4)
    {
        if (pin == P0)
            pinindex = 48;
        else
            pinindex = pin &0xF;

        if (pin == P0)
            portname = 95;
        else
            portname = pin>>4 + 'A';
        SmartOS_printf("Close JTAG Pin P%c%d \r\n", portname, pinindex);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA << (pin >> 4), ENABLE);
        GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
    }
}

void OpenPeriphClock(Pin pin)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA << (pin >> 4),ENABLE);
}

bool Port::Open()
{
    if (this->Opened == false)
    {
        if (_Pin != P0)
        {
            // 打开时钟
            int gi = _Pin >> 4;
                RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA << gi, ENABLE);
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
int EXTI_IRQHandler(int a1, void *a2)
{
	return 0;
}
void OutputPort::OpenPin(void *param)
{
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
void AnalogInPort::OpenPin(void* param)
{
	
}
void AlternatePort::OpenPin(void *param)
{
    GPIO_InitTypeDef *gpio = (GPIO_InitTypeDef*)param;
        gpio->GPIO_Mode = this->OpenDrain ? GPIO_Mode_AF_OD : GPIO_Mode_AF_PP;
    int i = 0;
    i++;
}
void Port::RemapConfig(uint param, bool sta)
{
	
}
void InputPort::OpenPin(void* param)
{
}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////以下为添加///////////////////////////////////////
// 获取组和针脚
#define _GROUP(PIN) ((GPIO_TypeDef *) (GPIOA_BASE + (((PIN) & (ushort)0xF0) << 6)))
#define _RCC_APB2(PIN) (RCC_APB2Periph_GPIOA << (PIN >> 4))

   
GPIO_TypeDef *IndexToGroup(byte index)
{
    return ((GPIO_TypeDef*)(GPIOA_BASE + (index << 10)));
}

byte GroupToIndex(GPIO_TypeDef *group)
{
    return (byte)(((int)group - GPIOA_BASE) >> 10);
}

void OutputPort::Write(Pin pin, bool value)
{
    if (value)
    {
        GPIO_SetBits(_GROUP(pin), _PORT(pin));
    }
    else
    {
        GPIO_ResetBits(_GROUP(pin), _PORT(pin));
    }
}
void AnalogInPort::OnOpen(void *param)
{
    Port::OnOpen(param);
    GPIO_InitTypeDef *gpio = (GPIO_InitTypeDef*)param;
        gpio->GPIO_Mode = GPIO_Mode_AIN; //
}
void InputPort::OnOpen(void *param)
{
    Port::OnOpen(param);
    GPIO_InitTypeDef *gpio = (GPIO_InitTypeDef*)param;
        if (Floating)
            gpio->GPIO_Mode = GPIO_Mode_IN_FLOATING;
        else if (Pull == UP)
            gpio->GPIO_Mode = GPIO_Mode_IPU;
        else if (Pull == DOWN)
            gpio->GPIO_Mode = GPIO_Mode_IPD;
        // 这里很不确定，需要根据实际进行调整     
}
void GPIO_ISR(int num);
//所有中断线处理
void EXTI_IRQHandler(ushort num, void *param)
{
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
