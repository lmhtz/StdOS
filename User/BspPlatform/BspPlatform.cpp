#include "BspPlatform.h"
#if defined STM32F0
#elif defined STM32F1
#include "stm32f10x.h"
#elif defined STM32F4
#endif
#include "Sys.h"
#include "Core\Queue.h"
#include "Port.h"
#include "Platform\stm32.h"
#include "Device\DeviceConfigHelper.h"

#ifdef STM32F0


extern "C"
{

}
#elif defined STM32F1

//中断线打开、关闭
void SetEXIT(int pinIndex, bool enable, Trigger trigger = Both)
{
#if defined STM32F0
	/* 配置EXTI中断线 */
	EXTI_InitTypeDef ext;
	EXTI_StructInit(&ext);
	ext.EXTI_Line = EXTI_Line0 << (pinIndex & 0X0F);
	ext.EXTI_Mode = EXTI_Mode_Interrupt;
	switch (trigger)
	{
	case InputPort::Rising:
		ext.EXTI_Trigger = EXTI_Trigger_Rising; // 上升沿触发
		break;
	case InputPort::Falling:
		ext.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
		break;
	case InputPort::Both:
	default:
		ext.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 上升沿下降沿触发
		break;
	}
	ext.EXTI_LineCmd = enable ? ENABLE : DISABLE;
	EXTI_Init(&ext);
#elif defined STM32F1
	/* 配置EXTI中断线 */
	EXTI_InitTypeDef ext;
	EXTI_StructInit(&ext);
	ext.EXTI_Line = EXTI_Line0 << (pinIndex & 0X0F);
	ext.EXTI_Mode = EXTI_Mode_Interrupt;
	switch (trigger)
	{
	case Rising: ext.EXTI_Trigger = EXTI_Trigger_Rising; // 上升沿触发
		break;
	case Falling: ext.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
		break;
	case Both:
	default:
		ext.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 上升沿下降沿触发
		break;
	}
	ext.EXTI_LineCmd = enable ? ENABLE : DISABLE;
	EXTI_Init(&ext);
#elif defined STM32F4
	/* 配置EXTI中断线 */
	EXTI_InitTypeDef ext;
	EXTI_StructInit(&ext);
	ext.EXTI_Line = EXTI_Line0 << (pinIndex & 0X0F);
	ext.EXTI_Mode = EXTI_Mode_Interrupt;
	switch (trigger)
	{
	case InputPort::Rising:
		ext.EXTI_Trigger = EXTI_Trigger_Rising; // 上升沿触发
		break;
	case InputPort::Falling:
		ext.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
		break;
	case InputPort::Both:
	default:
		ext.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 上升沿下降沿触发
		break;
	}
	ext.EXTI_LineCmd = enable ? ENABLE : DISABLE;
	EXTI_Init(&ext);
#endif
}
static const int PORT_IRQns[] =
{
	#if defined STM32F0
	EXTI0_1_IRQn, EXTI0_1_IRQn,  // 基础
	EXTI2_3_IRQn, EXTI2_3_IRQn,  // 基础
	EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn,
	EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn, EXTI4_15_IRQn  // EXTI15_10
	#elif defined STM32F1
	EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn, EXTI4_IRQn,  // 5个基础的
	EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn,  // EXTI9_5
	EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn  // EXTI15_10
	#elif defined STM32F4
	EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn, EXTI4_IRQn,  // 5个基础的
	EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn,  // EXTI9_5
	EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn  // EXTI15_10
	#endif
};
void InputPort_OpenEXTI(Pin pin, Trigger trigger = Both)
{
#if defined STM32F0
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA + pin >> 4, pin & 0x0f);

	SetEXIT(pin, true, trigger);
	Interrupt.SetPriority(PORT_IRQns[pin & 0x0f], 1u);
	//Interrupt.Activate(PORT_IRQns[v3],(void (__cdecl *)(unsigned __int16, void *))EXTI_IRQHandler,v1);
#elif defined STM32F1
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA + pin >> 4, pin & 0x0f);
	SetEXIT(pin, true, trigger);
	NVIC_InitTypeDef nvic;

	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannel = PORT_IRQns[pin & 0x0f];

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;

	NVIC_Init(&nvic);
	NVIC_SetPriority((IRQn_Type)PORT_IRQns[pin & 0x0f], 1);
#elif defined STM32F4
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA + pin >> 4, pin & 0x0f);

	SetEXIT(pin, true, trigger);
	Interrupt.SetPriority(PORT_IRQns[pin & 0x0f], 1u);
	//Interrupt.Activate(PORT_IRQns[v3],(void (__cdecl *)(unsigned __int16, void *))EXTI_IRQHandler,v1);
#endif
}

void BspPlatformInit()
{	
	DeviceConfigHelper::TimeTickInit();//系统用定时器初始化
}
void TimeUpdate();
extern "C"
{
	void SysTick_Handler(void)
	{

	}

	void USART1_IRQHandler(void)
	{
#if USECOM1
		volatile uint8_t ch;
		if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
			ch = USART_ReceiveData(USART1);
			Rxx1.Enqueue(ch);
		}
		if (USART_GetITStatus(USART1, USART_IT_IDLE) == SET)
			//数据帧接收完毕
		{
			ch = USART_ReceiveData(USART1); //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)
		}
		/* 处理发送缓冲区空中断 */
		if (USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
		{
			if (Txx1.Empty())
			{
				/* 发送缓冲区的数据已取完时， 禁止发送缓冲区空中断 （注意：此时最后1个数据还未真正发送完毕）*/
				USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
				/* 使能数据发送完毕中断 */
				USART_ITConfig(USART1, USART_IT_TC, ENABLE);
			}
			else
			{
				/* 从发送FIFO取1个字节写入串口发送数据寄存器 */
				USART_SendData(USART1, Txx1.Dequeue());
			}

		}
		/* 数据bit位全部发送完毕的中断 */
		else if (USART_GetITStatus(USART1, USART_IT_TC) != RESET)
		{
			if (Txx1.Empty())
			{
				/* 如果发送FIFO的数据全部发送完毕，禁止数据发送完毕中断 */
				USART_ITConfig(USART1, USART_IT_TC, DISABLE);

				/* 回调函数, 一般用来处理RS485通信，将RS485芯片设置为接收模式，避免抢占总线 */
				Txx1.Clear();
				if (DeviceConfigHelper::pCOM1Rx485)
				{
					*DeviceConfigHelper::pCOM1Rx485 = 0;
				}
			}
			else
			{
				/* 正常情况下，不会进入此分支 */
				/* 如果发送FIFO的数据还未完毕，则从发送FIFO取1个数据写入发送数据寄存器 */
				USART_SendData(USART1, Txx1.Dequeue());
			}
		}
#endif
	}
	void USART2_IRQHandler(void)
	{
#if USECOM2
		volatile uint8_t ch;
		if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
		{
			ch = USART_ReceiveData(USART2);
			Rxx2.Enqueue(ch);
		}
		if (USART_GetITStatus(USART2, USART_IT_IDLE) == SET)
			//数据帧接收完毕
		{
			ch = USART_ReceiveData(USART2); //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)    
			//com2test();
		}
		/* 处理发送缓冲区空中断 */
		if (USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
		{
			if (Txx2.Empty())
			{
				/* 发送缓冲区的数据已取完时， 禁止发送缓冲区空中断 （注意：此时最后1个数据还未真正发送完毕）*/
				USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
				/* 使能数据发送完毕中断 */
				USART_ITConfig(USART2, USART_IT_TC, ENABLE);
			}
			else
			{
				/* 从发送FIFO取1个字节写入串口发送数据寄存器 */
				USART_SendData(USART2, Txx2.Dequeue());
			}

		}
		/* 数据bit位全部发送完毕的中断 */
		else if (USART_GetITStatus(USART2, USART_IT_TC) != RESET)
		{
			if (Txx2.Empty())
			{
				/* 如果发送FIFO的数据全部发送完毕，禁止数据发送完毕中断 */
				USART_ITConfig(USART2, USART_IT_TC, DISABLE);

				/* 回调函数, 一般用来处理RS485通信，将RS485芯片设置为接收模式，避免抢占总线 */
				Txx2.Clear();
				if (DeviceConfigHelper::pCOM2Rx485)
				{
					*DeviceConfigHelper::pCOM2Rx485 = 0;
				}
			}
			else
			{
				/* 正常情况下，不会进入此分支 */
				/* 如果发送FIFO的数据还未完毕，则从发送FIFO取1个数据写入发送数据寄存器 */
				USART_SendData(USART2, Txx2.Dequeue());
			}
		}
#endif
	}
	void USART3_IRQHandler(void)
	{
#if USECOM3
		volatile uint8_t ch;
		if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
		{
			ch = USART_ReceiveData(USART3);
			Rxx3.Enqueue(ch);
		}
		if (USART_GetITStatus(USART3, USART_IT_IDLE) == SET)
			//数据帧接收完毕
		{
			ch = USART_ReceiveData(USART3); //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR) 
		}
		/* 处理发送缓冲区空中断 */
		if (USART_GetITStatus(USART3, USART_IT_TXE) != RESET)
		{
			if (Txx3.Empty())
			{
				/* 发送缓冲区的数据已取完时， 禁止发送缓冲区空中断 （注意：此时最后1个数据还未真正发送完毕）*/
				USART_ITConfig(USART3, USART_IT_TXE, DISABLE);
				/* 使能数据发送完毕中断 */
				USART_ITConfig(USART3, USART_IT_TC, ENABLE);
			}
			else
			{
				/* 从发送FIFO取1个字节写入串口发送数据寄存器 */
				USART_SendData(USART3, Txx3.Dequeue());
			}

		}
		/* 数据bit位全部发送完毕的中断 */
		else if (USART_GetITStatus(USART3, USART_IT_TC) != RESET)
		{
			if (Txx3.Empty())
			{
				/* 如果发送FIFO的数据全部发送完毕，禁止数据发送完毕中断 */
				USART_ITConfig(USART3, USART_IT_TC, DISABLE);

				/* 回调函数, 一般用来处理RS485通信，将RS485芯片设置为接收模式，避免抢占总线 */
				Txx3.Clear();
				if (DeviceConfigHelper::pCOM3Rx485)
				{
					*DeviceConfigHelper::pCOM3Rx485 = 0;
				}
			}
			else
			{
				/* 正常情况下，不会进入此分支 */
				/* 如果发送FIFO的数据还未完毕，则从发送FIFO取1个数据写入发送数据寄存器 */
				USART_SendData(USART3, Txx3.Dequeue());
			}
		}
#endif
	}
	void UART4_IRQHandler(void)
	{
#if USECOM4
		volatile uint8_t ch;
		if (USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)
		{
			ch = USART_ReceiveData(UART4);
			Rxx3.Enqueue(ch);
		}
		if (USART_GetITStatus(UART4, USART_IT_IDLE) == SET)
			//数据帧接收完毕
		{
			ch = USART_ReceiveData(UART4); //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR) 
		}
		/* 处理发送缓冲区空中断 */
		if (USART_GetITStatus(UART4, USART_IT_TXE) != RESET)
		{
			if (Txx4.Empty())
			{
				/* 发送缓冲区的数据已取完时， 禁止发送缓冲区空中断 （注意：此时最后1个数据还未真正发送完毕）*/
				USART_ITConfig(UART4, USART_IT_TXE, DISABLE);
				/* 使能数据发送完毕中断 */
				USART_ITConfig(UART4, USART_IT_TC, ENABLE);
			}
			else
			{
				/* 从发送FIFO取1个字节写入串口发送数据寄存器 */
				USART_SendData(UART4, Txx4.Dequeue());
			}

		}
		/* 数据bit位全部发送完毕的中断 */
		else if (USART_GetITStatus(UART4, USART_IT_TC) != RESET)
		{
			if (Txx4.Empty())
			{
				/* 如果发送FIFO的数据全部发送完毕，禁止数据发送完毕中断 */
				USART_ITConfig(UART4, USART_IT_TC, DISABLE);

				/* 回调函数, 一般用来处理RS485通信，将RS485芯片设置为接收模式，避免抢占总线 */
				Txx4.Clear();
				if (DeviceConfigHelper::pCOM4Rx485)
				{
					*DeviceConfigHelper::pCOM4Rx485 = 0;
				}
			}
			else
			{
				/* 正常情况下，不会进入此分支 */
				/* 如果发送FIFO的数据还未完毕，则从发送FIFO取1个数据写入发送数据寄存器 */
				USART_SendData(UART4, Txx4.Dequeue());
			}
		}
#endif
	}
	void UART5_IRQHandler(void)
	{
#if USECOM5
		volatile uint8_t ch;
		if (USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)
		{
			ch = USART_ReceiveData(UART5);
			Rxx5.Enqueue(ch);
		}
		if (USART_GetITStatus(UART5, USART_IT_IDLE) == SET)
			//数据帧接收完毕
		{
			ch = USART_ReceiveData(UART5); //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)  
		}
		/* 处理发送缓冲区空中断 */
		if (USART_GetITStatus(UART5, USART_IT_TXE) != RESET)
		{
			if (Txx5.Empty())
			{
				/* 发送缓冲区的数据已取完时， 禁止发送缓冲区空中断 （注意：此时最后1个数据还未真正发送完毕）*/
				USART_ITConfig(UART5, USART_IT_TXE, DISABLE);
				/* 使能数据发送完毕中断 */
				USART_ITConfig(UART5, USART_IT_TC, ENABLE);
			}
			else
			{
				/* 从发送FIFO取1个字节写入串口发送数据寄存器 */
				USART_SendData(UART5, Txx3.Dequeue());
			}

		}
		/* 数据bit位全部发送完毕的中断 */
		else if (USART_GetITStatus(UART5, USART_IT_TC) != RESET)
		{
			if (Txx5.Empty())
			{
				/* 如果发送FIFO的数据全部发送完毕，禁止数据发送完毕中断 */
				USART_ITConfig(UART5, USART_IT_TC, DISABLE);

				/* 回调函数, 一般用来处理RS485通信，将RS485芯片设置为接收模式，避免抢占总线 */
				Txx5.Clear();
				if (DeviceConfigHelper::pCOM5Rx485)
				{
					*DeviceConfigHelper::pCOM5Rx485 = 0;
				}
			}
			else
			{
				/* 正常情况下，不会进入此分支 */
				/* 如果发送FIFO的数据还未完毕，则从发送FIFO取1个数据写入发送数据寄存器 */
				USART_SendData(UART5, Txx5.Dequeue());
			}
		}
#endif
	}

	void TIM2_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
		{

			TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
			TimeUpdate();
		}
	}
	void TIM3_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
		{

			TIM_ClearITPendingBit(TIM3, TIM_FLAG_Update);
		}
	}
	void TIM4_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
		{

			TIM_ClearITPendingBit(TIM4, TIM_FLAG_Update);
		}
	}
	void TIM5_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM5, TIM_FLAG_Update);
		}
	}

	void TIM6_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM6, TIM_FLAG_Update);
		}
	}

	void TIM7_IRQHandler(void)
	{
		if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)
		{
			TIM_ClearITPendingBit(TIM7, TIM_FLAG_Update);
		}
	}
	void EXTI0_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line0) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line0);
		}
	}
	void EXTI1_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line1) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line1);
		}
	}

	void EXTI2_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line2) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line2);
		}
	}
	void EXTI3_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line3) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line3);
		}
	}
	void EXTI4_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line4) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line4);
		}
	}

	void EXTI9_5_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line5) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line5);
		}
		if (EXTI_GetITStatus(EXTI_Line6) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line6);
		}
		if (EXTI_GetITStatus(EXTI_Line7) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line7);
		}
		if (EXTI_GetITStatus(EXTI_Line8) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line8);
		}
		if (EXTI_GetITStatus(EXTI_Line9) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line9);
		}
	}
	void EXTI15_10_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line10) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line10);
		}
		if (EXTI_GetITStatus(EXTI_Line11) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line11);
		}
		if (EXTI_GetITStatus(EXTI_Line12) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line12);
		}
		if (EXTI_GetITStatus(EXTI_Line13) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line13);
		}
		if (EXTI_GetITStatus(EXTI_Line14) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line14);
		}
		if (EXTI_GetITStatus(EXTI_Line15) != RESET)
		{
			EXTI_ClearITPendingBit(EXTI_Line15);
		}
	}
}

#elif defined STM32F4


extern "C"
{

}
#endif
