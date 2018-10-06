#include "Configuration.h"
#include "Port.h"
#include "Platform\stm32.h"

//�ж�

Func DeviceConfigCenter::PExit0 = 0;
Func DeviceConfigCenter::PExit1 = 0;
Func DeviceConfigCenter::PExit2 = 0;
Func DeviceConfigCenter::PExit3 = 0;
Func DeviceConfigCenter::PExit4 = 0;
Func DeviceConfigCenter::PExit5 = 0;
Func DeviceConfigCenter::PExit6 = 0;
Func DeviceConfigCenter::PExit7 = 0;
Func DeviceConfigCenter::PExit8 = 0;
Func DeviceConfigCenter::PExit9 = 0;
Func DeviceConfigCenter::PExit10 = 0;
Func DeviceConfigCenter::PExit11 = 0;
Func DeviceConfigCenter::PExit12 = 0;
Func DeviceConfigCenter::PExit13 = 0;
Func DeviceConfigCenter::PExit14 = 0;
Func DeviceConfigCenter::PExit15 = 0;

//����
OutputPort *DeviceConfigCenter::pCOM1Rx485 = 0;
OutputPort *DeviceConfigCenter::pCOM2Rx485 = 0;
OutputPort *DeviceConfigCenter::pCOM3Rx485 = 0;
OutputPort *DeviceConfigCenter::pCOM4Rx485 = 0;
OutputPort *DeviceConfigCenter::pCOM5Rx485 = 0;

Func DeviceConfigCenter::PRcvCOM1 = 0;
Func DeviceConfigCenter::PRcvCOM2 = 0;
Func DeviceConfigCenter::PRcvCOM3 = 0;
Func DeviceConfigCenter::PRcvCOM4 = 0;
Func DeviceConfigCenter::PRcvCOM5 = 0;

int DeviceConfigCenter::RcvLastTimeCOM1 = 0;//����1����������ʱ��
int DeviceConfigCenter::RcvLastTimeCOM2 = 0;//����2����������ʱ��
int DeviceConfigCenter::RcvLastTimeCOM3 = 0;//����3����������ʱ��
int DeviceConfigCenter::RcvLastTimeCOM4 = 0;//����4����������ʱ��
int DeviceConfigCenter::RcvLastTimeCOM5 = 0;//����5����������ʱ��

int DeviceConfigCenter::RcvCom1PackInterval = 1;//����1��������֡ʱ����
int DeviceConfigCenter::RcvCom2PackInterval = 1;//����2��������֡ʱ����
int DeviceConfigCenter::RcvCom3PackInterval = 1;//����3��������֡ʱ����
int DeviceConfigCenter::RcvCom4PackInterval = 1;//����4��������֡ʱ����
int DeviceConfigCenter::RcvCom5PackInterval = 1;//����5��������֡ʱ����

int DeviceConfigCenter::BUFLEN_TX1 = 0;	//����1���ͻ���������
int DeviceConfigCenter::BUFLEN_RX1 = 0;	//����1���ջ���������
int DeviceConfigCenter::BUFLEN_TX2 = 0;	//����2���ͻ���������
int DeviceConfigCenter::BUFLEN_RX2 = 0;	//����2���ջ���������
int DeviceConfigCenter::BUFLEN_TX3 = 0;	//����3���ͻ���������
int DeviceConfigCenter::BUFLEN_RX3 = 0;	//����3���ջ���������
int DeviceConfigCenter::BUFLEN_TX4 = 0;	//����4���ͻ���������
int DeviceConfigCenter::BUFLEN_RX4 = 0;	//����4���ջ���������
int DeviceConfigCenter::BUFLEN_TX5 = 0;	//����5���ͻ���������
int DeviceConfigCenter::BUFLEN_RX5 = 0;	//����5���ջ���������

int DeviceConfigCenter::FLAG_TX1EN = 1;	//����1���Է���
int DeviceConfigCenter::FLAG_TX2EN = 1;	//����2���Է���
int DeviceConfigCenter::FLAG_TX3EN = 1;	//����3���Է���
int DeviceConfigCenter::FLAG_TX4EN = 1;	//����4���Է���
int DeviceConfigCenter::FLAG_TX5EN = 1;	//����5���Է���

//��ʱ��
Func DeviceConfigCenter::PTim2Update = 0;
Func DeviceConfigCenter::PTim3Update = 0;
Func DeviceConfigCenter::PTim4Update = 0;
Func DeviceConfigCenter::PTim5Update = 0;
Func DeviceConfigCenter::PTim6Update = 0;
Func DeviceConfigCenter::PTim7Update = 0;
Func DeviceConfigCenter::PTim8Update = 0;


//�ж��ߴ򿪡��ر�
void DeviceConfigCenter::SetEXIT(int pinIndex, bool enable, Trigger trigger)
{
#if defined STM32F0

#elif defined STM32F1
	/* ����EXTI�ж��� */
	EXTI_InitTypeDef ext;
	EXTI_StructInit(&ext);
	ext.EXTI_Line = EXTI_Line0 << (pinIndex & 0X0F);
	ext.EXTI_Mode = EXTI_Mode_Interrupt;
	switch (trigger)
	{
	case Rising: ext.EXTI_Trigger = EXTI_Trigger_Rising; // �����ش���
		break;
	case Falling: ext.EXTI_Trigger = EXTI_Trigger_Falling; // �½��ش���
		break;
	case Both:
	default:
		ext.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // �������½��ش���
		break;
	}
	ext.EXTI_LineCmd = enable ? ENABLE : DISABLE;
	EXTI_Init(&ext);
#elif defined STM32F4

#endif
}
#if defined STM32F0

#elif defined STM32F1

static const int PORT_IRQns[] =
{
	EXTI0_IRQn, EXTI1_IRQn, EXTI2_IRQn, EXTI3_IRQn, EXTI4_IRQn,  // 5��������
	EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn, EXTI9_5_IRQn,  // EXTI9_5
	EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn, EXTI15_10_IRQn  // EXTI15_10
};
#elif defined STM32F4

#endif


void DeviceConfigCenter::InputPort_OpenEXTI(Pin pin, Trigger trigger)
{
#if defined STM32F0

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

#endif
}

#ifdef __cplusplus
extern "C" {
#endif	
#if defined USECOM1TXD
	static char com1tx[256];
	Queue	Txx1;
#endif
#if defined USECOM1RXD
	static char com1rx[256];
	Queue	Rxx1;
#endif
#if defined USECOM2TXD
	static char com2tx[256];
	Queue	Txx2;
#endif
#if defined USECOM2RXD
	static char com2rx[256];
	Queue	Rxx2;
#endif
#if defined USECOM3TXD
	static char com3tx[256];
	Queue	Txx3;
#endif
#if defined USECOM3RXD
	static char com3rx[256];
	Queue	Rxx3;
#endif
#if defined USECOM4TXD
	static char com4tx[256];
	Queue	Txx4;
#endif
#if defined USECOM4RXD
	static char com4rx[256];
	Queue	Rxx4;
#endif
#if defined USECOM5TXD
	static char com5tx[256];
	Queue	Txx5;
#endif
#if defined USECOM5RXD
	static char com5rx[256];
	Queue	Rxx5;
#endif

#ifdef __cplusplus
}
#endif
void DeviceConfigCenter::ConfigCom(COM com, int baudRate)
{
	switch (com)
	{
	case COM1:
		configCOM1(baudRate);
		break;
	case COM2:
		configCOM2(baudRate);
		break;
	case COM3:
		configCOM3(baudRate);
		break;
	case COM4:
		configCOM4(baudRate);
		break;
	case COM5:
		configCOM5(baudRate);
		break;
	case COM6:
		break;
	case COM7:
		break;
	case COM8:
		break;
	case COM_NONE:
		break;
	default:
		break;
	}
}
//�ı䲨����
void DeviceConfigCenter::ComChgBaudRate(COM com, int baudRate)
{
	switch (com)
	{
	case COM1:
		Com1ChgBaudRate(baudRate);
		break;
	case COM2:
		Com2ChgBaudRate(baudRate);
		break;
	case COM3:
		Com3ChgBaudRate(baudRate);
		break;
	case COM4:
		Com4ChgBaudRate(baudRate);
		break;
	case COM5:
		Com5ChgBaudRate(baudRate);
		break;
	case COM6:
		break;
	case COM7:
		break;
	case COM8:
		break;
	case COM_NONE:
		break;
	default:
		break;
	}
}
//��������
void DeviceConfigCenter::comSend(COM com, void* buf, int len)
{
	switch (com)
	{
	case COM1:
		com1send(buf, len);
		break;
	case COM2:
		com2send(buf, len);
		break;
	case COM3:
		com3send(buf, len);
		break;
	case COM4:
		com4send(buf, len);
		break;
	case COM5:
		com5send(buf, len);
		break;
	case COM6:
		break;
	case COM7:
		break;
	case COM8:
		break;
	case COM_NONE:
		break;
	default:
		break;
	}
}
#if defined COM1TXDMAFLAG
void USART1_SendDMA(uint8_t* buf, int len)
{
	DMA_InitTypeDef DMA_InitStruct;
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA1_Channel4, DISABLE);

	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)buf;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_BufferSize = len;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel4, &DMA_InitStruct);

	DMA_Cmd(DMA1_Channel4, ENABLE);
	DeviceConfigCenter::FLAG_TX1EN = 0;	//����1�����Է���
}
#endif
#if defined COM2TXDMAFLAG
void USART2_SendDMA(uint8_t* buf, int len)
{
	DMA_InitTypeDef DMA_InitStruct;
	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA1_Channel7, DISABLE);

	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&USART2->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)buf;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_BufferSize = len;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel7, &DMA_InitStruct);

	DMA_Cmd(DMA1_Channel7, ENABLE);
	DeviceConfigCenter::FLAG_TX2EN = 0;	//����2�����Է���
}
#endif
#if defined COM3TXDMAFLAG
void USART3_SendDMA(uint8_t* buf, int len)
{
	DMA_InitTypeDef DMA_InitStruct;
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA1_Channel2, DISABLE);

	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&USART3->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)buf;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_BufferSize = len;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2, &DMA_InitStruct);

	DMA_Cmd(DMA1_Channel2, ENABLE);
	DeviceConfigCenter::FLAG_TX3EN = 0;	//����3�����Է���
}
#endif
#if defined COM4TXDMAFLAG
void USART4_SendDMA(uint8_t* buf, int len)
{
	DMA_InitTypeDef DMA_InitStruct;
	//DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);

	//DMA_Cmd(DMA1_Channel2, DISABLE);

	//DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&UART4->DR);
	//DMA_InitStruct.DMA_MemoryBaseAddr = (u32)buf;
	//DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	//DMA_InitStruct.DMA_BufferSize = len;
	//DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	//DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	//DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	//DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	//DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	//DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
	//DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	//DMA_Init(DMA1_Channel2, &DMA_InitStruct);

	//DMA_Cmd(DMA1_Channel2, ENABLE);
	DeviceConfigCenter::FLAG_TX4EN = 0;	//����4�����Է���
}
#endif
#if defined COM5TXDMAFLAG
void USART5_SendDMA(uint8_t* buf, int len)
{
	DMA_InitTypeDef DMA_InitStruct;
	/*DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);

	DMA_Cmd(DMA1_Channel2, DISABLE);

	DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&UART5->DR);
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)buf;
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_InitStruct.DMA_BufferSize = len;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStruct.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel2, &DMA_InitStruct);

	DMA_Cmd(DMA1_Channel2, ENABLE);*/
	DeviceConfigCenter::FLAG_TX5EN = 0;	//����5�����Է���
}
#endif
#if defined COM1TXDMAFLAG
uint8_t com1bufff[300];
#endif
#if defined COM2TXDMAFLAG
uint8_t com2bufff[300];
#endif
#if defined COM3TXDMAFLAG
uint8_t com3bufff[300];
#endif
#if defined COM4TXDMAFLAG
uint8_t com4bufff[300];
#endif
#if defined COM5TXDMAFLAG
uint8_t com5bufff[300];
#endif
void OS_ComSendChk(void *param);
void DeviceConfigCenter::com1send(void* buf, int len)
{
#if defined USECOM1TXD
	if (pCOM1Rx485)
	{
		*pCOM1Rx485 = 1;
	}

#if defined COM1TXDMAFLAG			
	Txx1.Write(bs);
#elif defined COM1SENDINTFLAG
	while (len > Txx1.RemainLength());//�ȴ����ͻ������������㹻����
	//�жϷ���
	Sys.GlobalDisable();
	Txx1.Write(buf,len);
	Sys.GlobalEnable();
	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
#else	
	for (int i = 0; i < len; i++)
	{
		/* ����һ���ֽ����ݵ�USART */
		USART_SendData(USART1, ((uint8_t*)buf)[i]);

		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	}
	if (pCOM1Rx485)
	{
		Sys.Delay(100);
		*pCOM1Rx485 = 0;
	}
#endif
#endif
}
void DeviceConfigCenter::com2send(void* buf, int len)
{
#if defined USECOM2TXD
	if (pCOM2Rx485)
	{
		*pCOM2Rx485 = 1;
	}

#if defined COM2TXDMAFLAG			
	Txx2.Write(bs);
#elif defined COM2SENDINTFLAG
	while (len > Txx2.RemainLength());//�ȴ����ͻ������������㹻����
											  //�жϷ���
	Sys.GlobalDisable();
	Txx2.Write(buf,len);
	Sys.GlobalEnable();
	USART_ITConfig(USART2, USART_IT_TXE, ENABLE);
#else	
	for (int i = 0; i < bs.Length(); i++)
	{
		/* ����һ���ֽ����ݵ�USART */
		USART_SendData(USART2, bs[i]);

		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	}
	if (pCOM2Rx485)
	{
		Sys.Delay(100);
		*pCOM2Rx485 = 0;
	}
#endif
#endif
}
void DeviceConfigCenter::com3send(void* buf, int len)
{
#if defined USECOM3TXD
	if (pCOM3Rx485)
	{
		*pCOM3Rx485 = 1;
	}

#if defined COM3TXDMAFLAG			
	Txx3.Write(bs.GetBuffer(),bs.Length());
#elif defined COM3SENDINTFLAG
	while (bs.Length() > Txx3.RemainLength());//�ȴ����ͻ������������㹻����
											  //�жϷ���
	Sys.GlobalDisable();
	Txx3.Write(bs.GetBuffer(),bs.Length());
	Sys.GlobalEnable();
	USART_ITConfig(USART3, USART_IT_TXE, ENABLE);
#else	
	for (int i = 0; i < len; i++)
	{
		/* ����һ���ֽ����ݵ�USART */
		USART_SendData(USART3, ((char*)buf)[i]);

		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
	}
	if (pCOM3Rx485)
	{
		Sys.Delay(100);
		*pCOM3Rx485 = 0;
	}
#endif
#endif
}
void DeviceConfigCenter::com4send(void* buf, int len)
{
#if defined USECOM4TXD
	if (pCOM4Rx485)
	{
		*pCOM4Rx485 = 1;
	}

#if defined COM4TXDMAFLAG			
	Txx4.Write(bs);
#elif defined COM4SENDINTFLAG
	while (len > Txx4.RemainLength());//�ȴ����ͻ������������㹻����
											  //�жϷ���
	Sys.GlobalDisable();
	Txx4.Write(buf,len);
	Sys.GlobalEnable();
	USART_ITConfig(UART4, USART_IT_TXE, ENABLE);
#else	
	for (int i = 0; i < bs.Length(); i++)
	{
		/* ����һ���ֽ����ݵ�USART */
		USART_SendData(UART4, bs[i]);

		/* �ȴ�������� */
		while (USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);
	}
	if (pCOM4Rx485)
	{
		Sys.Delay(100);
		*pCOM4Rx485 = 0;
	}
#endif
#endif
}
void DeviceConfigCenter::com5send(void* buf, int len)
{
#if defined USECOM5TXD
	if (pCOM5Rx485)
	{
		*pCOM5Rx485 = 1;
	}

#if defined COM5TXDMAFLAG			
	Txx5.Write(bs.GetBuffer(),bs.Length());
#elif defined COM5SENDINTFLAG
	while (len > Txx5.RemainLength());//�ȴ����ͻ������������㹻����
											  //�жϷ���
	Sys.GlobalDisable();
	Txx5.Write(buf,len);
	Sys.GlobalEnable();
	USART_ITConfig(UART5, USART_IT_TXE, ENABLE);
#else	
	for (int i = 0; i < bs.Length(); i++)
	{
		/* ����һ���ֽ����ݵ�USART */
		USART_SendData(UART5, ��char* buf)[i]);

		/* �ȴ�������� */
		while (USART_GetFlagStatus(UART5, USART_FLAG_TXE) == RESET);
	}
	if (pCOM5Rx485)
	{
		Sys.Delay(100);
		*pCOM5Rx485 = 0;
	}
#endif
#endif
}

void DeviceConfigCenter::configCOM1(int baudRate)
{
#if defined USECOM1
	Port*		Ports[2];	// Tx/Rx
	Pin			Pins[2];	// Tx/Rx

#if defined USECOM1RXD
	DeviceConfigCenter::BUFLEN_RX1 = ArrayLength(com1rx);
	Rxx1.SetBuf(com1rx, ArrayLength(com1rx));
#endif
#if defined USECOM1TXD
	DeviceConfigCenter::BUFLEN_TX1 = ArrayLength(com1tx);
	Txx1.SetBuf(com1tx, ArrayLength(com1tx));
#endif
	SerialPort_GetPins(&Pins[0], &Pins[1], COM1);
	Ports[0] = new AlternatePort();
	Ports[1] = new InputPort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#if defined STM32F0
#elif defined STM32F1	

	USART_InitTypeDef USART_InitStructure;

	/* config USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	/* USART1 mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);

	/*	�����ж����ȼ� */
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	/* ʹ�ܴ���1�����ж� */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // ���ڽ����ж�����

#if defined COM1TXDMAFLAG
	//DMA����
	/*����DMAʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);  //����DMA������ɺ�����ж�

	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

	NVIC_InitTypeDef NVIC_InitStruct;

	DMA_ITConfig(DMA1_Channel5, DMA_IT_TC, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	//ENABLE DMA TX ISR
	DMA_ITConfig(DMA1_Channel4, DMA_IT_TC, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
#endif // COM1TXDMAFLAG
#if defined COM1RXDMAFLAG
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//���������ж�
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);   //ʹ�ܴ���1 DMA����

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	DMA_InitTypeDef DMA_InitStructureRcv;
	DMA_DeInit(DMA1_Channel5);   //��DMA��ͨ��5�Ĵ�������Ϊȱʡֵ  ����1��Ӧ����DMAͨ��5
	DMA_InitStructureRcv.DMA_PeripheralBaseAddr = (u32)&USART1->DR;  //DMA����ADC����ַ
	DMA_InitStructureRcv.DMA_MemoryBaseAddr = (u32)com1rx;  //DMA�ڴ����ַ
	DMA_InitStructureRcv.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�򣬴������ȡ���͵��ڴ�
	DMA_InitStructureRcv.DMA_BufferSize = DeviceConfigCenter::BUFLEN_RX1;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructureRcv.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructureRcv.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructureRcv.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ���Ϊ8λ
	DMA_InitStructureRcv.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ���Ϊ8λ
	DMA_InitStructureRcv.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructureRcv.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructureRcv.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel5, &DMA_InitStructureRcv);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���

	DMA_Cmd(DMA1_Channel5, ENABLE);  //��ʽ����DMA����
#endif

#if defined COM1RCVIDLEINTFLAG
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif

	USART_Cmd(USART1, ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//ʹ��USART1ʱ��
															  //����1��Ӧ���Ÿ���ӳ��
	//USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������1

	USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 

	//USART_ClearFlag(USART1, USART_FLAG_TC);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//��������ж�
												  //Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
#if defined COM1RCVIDLEINTFLAG
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1); //GPIO����ΪUSART
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1); //GPIO����ΪUSART

	SerialPort_GetPins(&Pins[0], &Pins[1], COM1);
	Ports[0] = new AlternatePort();
	Ports[1] = new AlternatePort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#endif	
#endif
}
void DeviceConfigCenter::configCOM2(int baudRate)
{
#if defined USECOM2
	Port*		Ports[2];	// Tx/Rx
	Pin			Pins[2];	// Tx/Rx
#if defined USECOM2RXD
	DeviceConfigCenter::BUFLEN_RX2 = ArrayLength(com2rx);
	Rxx2.SetBuf(com2rx, ArrayLength(com2rx));
#endif
#if defined USECOM2TXD
	DeviceConfigCenter::BUFLEN_TX2 = ArrayLength(com2tx);
	Txx2.SetBuf(com2tx, ArrayLength(com2tx));
#endif
	SerialPort_GetPins(&Pins[0], &Pins[1], COM2);
	Ports[0] = new AlternatePort();
	Ports[1] = new InputPort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#if defined STM32F0
#elif defined STM32F1

	USART_InitTypeDef USART_InitStructure;

	/* config USART2 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

	/* USART2 mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);

	/*	�����ж����ȼ� */
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

#if defined COM2TXDMAFLAG
	//DMA����
	/*����DMAʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);  //����DMA������ɺ�����ж�

	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE);

	NVIC_InitTypeDef NVIC_InitStruct;

	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	//ENABLE DMA TX ISR
	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
#endif // COM1TXDMAFLAG

	/* ʹ�ܴ���2�����ж� */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); // ���ڽ����ж�����
#if defined COM2RXDMAFLAG
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//���������ж�
	USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);   //ʹ�ܴ��� DMA����

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	DMA_InitTypeDef DMA_InitStructureRcv;
	DMA_DeInit(DMA1_Channel6);   //��DMA��ͨ��5�Ĵ�������Ϊȱʡֵ  ����1��Ӧ����DMAͨ��5
	DMA_InitStructureRcv.DMA_PeripheralBaseAddr = (u32)&USART2->DR;  //DMA����ADC����ַ
	DMA_InitStructureRcv.DMA_MemoryBaseAddr = (u32)com2rx;  //DMA�ڴ����ַ
	DMA_InitStructureRcv.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�򣬴������ȡ���͵��ڴ�
	DMA_InitStructureRcv.DMA_BufferSize = DeviceConfigCenter::BUFLEN_RX2;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructureRcv.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructureRcv.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructureRcv.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ���Ϊ8λ
	DMA_InitStructureRcv.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ���Ϊ8λ
	DMA_InitStructureRcv.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructureRcv.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructureRcv.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel6, &DMA_InitStructureRcv);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���

	DMA_Cmd(DMA1_Channel6, ENABLE);  //��ʽ����DMA����
#endif
#if defined COM2RCVIDLEINTFLAG
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif
	USART_Cmd(USART2, ENABLE);
	USART_ClearFlag(USART2, USART_FLAG_TC);
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//ʹ��USART1ʱ��
														  //����1��Ӧ���Ÿ���ӳ��
														  //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������1

	USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 

	//USART_ClearFlag(USART2, USART_FLAG_TC);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�
												  //Usart NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//�����ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
#if defined COM2RCVIDLEINTFLAG
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIO����ΪUSART
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIO����ΪUSART

	SerialPort_GetPins(&Pins[0], &Pins[1], COM1);
	Ports[0] = new AlternatePort();
	Ports[1] = new AlternatePort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#endif	
#endif
}

void DeviceConfigCenter::configCOM3(int baudRate)
{
#if defined USECOM3
	Port*		Ports[2];	// Tx/Rx
	Pin			Pins[2];	// Tx/Rx
#if defined USECOM3RXD
	DeviceConfigCenter::BUFLEN_RX3 = ArrayLength(com3rx);
	Rxx3.SetBuf(com3rx, ArrayLength(com3rx));
#endif
#if defined USECOM3TXD
	DeviceConfigCenter::BUFLEN_TX3 = ArrayLength(com3tx);
	Txx3.SetBuf(com3tx, ArrayLength(com3tx));
#endif
	SerialPort_GetPins(&Pins[0], &Pins[1], COM3);
	Ports[0] = new AlternatePort();
	Ports[1] = new InputPort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#if defined STM32F0

#elif defined STM32F1

	USART_InitTypeDef USART_InitStructure;

	/* config USART3 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	/* USART3 mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure);

	/*	�����ж����ȼ� */
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#if defined COM3TXDMAFLAG
	//DMA����
	/*����DMAʱ��*/
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);  //����DMA������ɺ�����ж�

	USART_DMACmd(USART3, USART_DMAReq_Tx, ENABLE);

	NVIC_InitTypeDef NVIC_InitStruct;

	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel5_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

	//ENABLE DMA TX ISR
	DMA_ITConfig(DMA1_Channel2, DMA_IT_TC, ENABLE);
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
#endif // COM1TXDMAFLAG
	/* ʹ�ܴ���3�����ж� */
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); // ���ڽ����ж�����
#if defined COM3RXDMAFLAG
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//���������ж�
	USART_DMACmd(USART3, USART_DMAReq_Rx, ENABLE);   //ʹ�ܴ���1 DMA����

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	DMA_InitTypeDef DMA_InitStructureRcv;
	DMA_DeInit(DMA1_Channel3);   //��DMA��ͨ��5�Ĵ�������Ϊȱʡֵ  ���ڶ�Ӧ����DMAͨ��
	DMA_InitStructureRcv.DMA_PeripheralBaseAddr = (u32)&USART3->DR;  //DMA����ADC����ַ
	DMA_InitStructureRcv.DMA_MemoryBaseAddr = (u32)com3rx;  //DMA�ڴ����ַ
	DMA_InitStructureRcv.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�򣬴������ȡ���͵��ڴ�
	DMA_InitStructureRcv.DMA_BufferSize = DeviceConfigCenter::BUFLEN_RX3;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructureRcv.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructureRcv.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructureRcv.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ���Ϊ8λ
	DMA_InitStructureRcv.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ���Ϊ8λ
	DMA_InitStructureRcv.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
	DMA_InitStructureRcv.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructureRcv.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel3, &DMA_InitStructureRcv);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���

	DMA_Cmd(DMA1_Channel3, ENABLE);  //��ʽ����DMA����
#endif
#if defined COM3RCVIDLEINTFLAG
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif
	USART_Cmd(USART3, ENABLE);
	USART_ClearFlag(USART3, USART_FLAG_TC);
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);//ʹ��USARTʱ��
														  //����1��Ӧ���Ÿ���ӳ��
														  //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������1

	USART_Cmd(USART3, ENABLE);  //ʹ�ܴ��� 

	//USART_ClearFlag(USART1, USART_FLAG_TC);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�
												  //Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
#if defined COM3RCVIDLEINTFLAG
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3); //GPIO����ΪUSART
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3); //GPIO����ΪUSART

	SerialPort_GetPins(&Pins[0], &Pins[1], COM1);
	Ports[0] = new AlternatePort();
	Ports[1] = new AlternatePort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#endif
#endif
}
void DeviceConfigCenter::configCOM4(int baudRate)
{
#if defined USECOM4
	Port*		Ports[2];	// Tx/Rx
	Pin			Pins[2];	// Tx/Rx
#if defined USECOM4RXD
	DeviceConfigCenter::BUFLEN_RX4 = ArrayLength(com4rx);
	Rxx4.SetBuf(com4rx, ArrayLength(com4rx));
#endif
#if defined USECOM4TXD
	DeviceConfigCenter::BUFLEN_TX4 = ArrayLength(com4tx);
	Txx4.SetBuf(com4tx, ArrayLength(com4tx));
#endif
#if defined STM32F0

#elif defined STM32F1 && defined STM32F10X_HD

	USART_InitTypeDef USART_InitStructure;

	/* config USART4 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	/* USART4 mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(UART4, &USART_InitStructure);

	/*	�����ж����ȼ� */
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* ʹ�ܴ���4�����ж� */
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE); // ���ڽ����ж�����
#if COM4RCVIDLEINTFLAG
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif

	USART_Cmd(UART4, ENABLE);
	USART_ClearFlag(UART4, USART_FLAG_TC);

	SerialPort_GetPins(&Pins[0], &Pins[1], COM4);
	Ports[0] = new AlternatePort();
	Ports[1] = new InputPort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);//ʹ��USARTʱ��
														  //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(UART4, &USART_InitStructure); //��ʼ������

	USART_Cmd(UART4, ENABLE);  //ʹ�ܴ���4 

	//USART_ClearFlag(USART4, USART_FLAG_TC);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//��������ж�
												  //Usart4 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
#if COM1RCVIDLEINTFLAG
	USART_ITConfig(UART4, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_UART4); //GPIO����ΪUSART
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_UART4); //GPIO����ΪUSART

	SerialPort_GetPins(&Pins[0], &Pins[1], COM1);
	Ports[0] = new AlternatePort();
	Ports[1] = new AlternatePort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#endif

#endif
}
void DeviceConfigCenter::configCOM5(int baudRate)
{
#if defined USECOM5
	Port*		Ports[2];	// Tx/Rx
	Pin			Pins[2];	// Tx/Rx
#if defined USECOM5RXD
	DeviceConfigCenter::BUFLEN_RX5 = ArrayLength(com5rx);
	Rxx5.SetBuf(com5rx, ArrayLength(com5rx));
#endif
#if defined USECOM5TXD
	DeviceConfigCenter::BUFLEN_TX5 = ArrayLength(com5tx);
	Txx5.SetBuf(com5tx, ArrayLength(com5tx));
#endif
#if defined STM32F0

#elif defined STM32F1 && defined STM32F10X_HD

	USART_InitTypeDef USART_InitStructure;

	/* config USART5 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

	/* USART5 mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(UART5, &USART_InitStructure);

	/*	�����ж����ȼ� */
	NVIC_InitTypeDef NVIC_InitStructure;
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	/* ʹ�ܴ���5�����ж� */
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE); // ���ڽ����ж�����
#if COM5RCVIDLEINTFLAG
	USART_ITConfig(UART5, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif

	USART_Cmd(UART5, ENABLE);
	USART_ClearFlag(UART5, USART_FLAG_TC);

	SerialPort_GetPins(&Pins[0], &Pins[1], COM5);
	Ports[0] = new AlternatePort();
	Ports[1] = new InputPort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();

#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD, ENABLE); //ʹ��GPIOʱ��
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);//ʹ��USARTʱ��
														  //USART5 ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(UART5, &USART_InitStructure); //��ʼ������

	USART_Cmd(UART5, ENABLE);  //ʹ�ܴ��� 

	//USART_ClearFlag(USART5, USART_FLAG_TC);

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//��������ж�
												  //Usart1 NVIC ����
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;//����1�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
#if COM1RCVIDLEINTFLAG
	USART_ITConfig(UART5, USART_IT_IDLE, ENABLE); //ʹ�ܴ������߿����ж� 
#endif

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5); //GPIO����ΪUSART
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5); //GPIO����ΪUSART

	SerialPort_GetPins(&Pins[0], &Pins[1], COM1);
	Ports[0] = new AlternatePort();
	Ports[1] = new AlternatePort();
	Ports[0]->Set(Pins[0]);
	Ports[1]->Set(Pins[1]);
	Ports[0]->Open();
	Ports[1]->Open();
#endif
#endif
}
void DeviceConfigCenter::Com1ChgBaudRate(int baudRate)
{
#if defined USECOM1
#if defined STM32F0

#elif defined STM32F1
	USART_InitTypeDef USART_InitStructure;

	/* USART mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART1, &USART_InitStructure);
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART1, &USART_InitStructure); //��ʼ������
#endif
#endif
}
void DeviceConfigCenter::Com2ChgBaudRate(int baudRate)
{
#if defined USECOM2
#if defined STM32F0

#elif defined STM32F1
	USART_InitTypeDef USART_InitStructure;

	/* USART mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART2, &USART_InitStructure);
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART2, &USART_InitStructure); //��ʼ������
#endif
#endif
}
void DeviceConfigCenter::Com3ChgBaudRate(int baudRate)
{
#if defined USECOM3
#if defined STM32F0

#elif defined STM32F1
	USART_InitTypeDef USART_InitStructure;

	/* USART mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(USART3, &USART_InitStructure);
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(USART3, &USART_InitStructure); //��ʼ������
#endif
#endif
}
void DeviceConfigCenter::Com4ChgBaudRate(int baudRate)
{
#if defined USECOM4
#if defined STM32F0

#elif defined STM32F1
	USART_InitTypeDef USART_InitStructure;

	/* USART mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(UART4, &USART_InitStructure);
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(UART4, &USART_InitStructure); //��ʼ������
#endif
#endif
}
void DeviceConfigCenter::Com5ChgBaudRate(int baudRate)
{
#if defined USECOM5
#if defined STM32F0

#elif defined STM32F1
	USART_InitTypeDef USART_InitStructure;

	/* USART mode config */
	USART_InitStructure.USART_BaudRate = baudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	USART_Init(UART5, &USART_InitStructure);
#elif defined STM32F4
	USART_InitTypeDef USART_InitStructure;

	//USART ��ʼ������
	USART_InitStructure.USART_BaudRate = baudRate;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
	USART_Init(UART5, &USART_InitStructure); //��ʼ������
#endif
#endif
}
void DeviceConfigCenter::SerialPort_GetPins(Pin *txPin, Pin *rxPin, COM index, bool Remap)
{
	*rxPin = *txPin = P0;

	const Pin g_Uart_Pins[] = UART_PINS;
	const Pin g_Uart_Pins_Map[] = UART_PINS_FULLREMAP;
	const Pin *p = g_Uart_Pins;
	if (Remap)
	{
		p = g_Uart_Pins_Map;
	}
	int n = index << 2;
	*txPin = p[n];
	*rxPin = p[n + 1];
}

void DeviceConfigCenter::TimeTickInit()//ϵͳ�ö�ʱ����ʼ��
{
#if defined STM32F0
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//ʹ��TIM2ʱ��

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//����һ��TIM_InitTypeDef���͵Ľṹ��
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//���жϱ�־���Ա��´��жϵ���ʹ��

	TIM_TimeBaseStructure.TIM_Period = 1000;//1���ӻ�2000������
	TIM_TimeBaseStructure.TIM_Prescaler = 35999; //36000��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//��ʼ����ʱ��
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//ʹ������ж�

	TIM_Cmd(TIM2, ENABLE);//��ʱ��ʹ��

	NVIC_InitTypeDef   NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#elif defined STM32F1
#if 1
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
	TIM_TimeBaseStructure.TIM_Period = 2000 - 1;
	/* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
	/* ʱ��Ԥ��Ƶ��Ϊ72 */
	TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1;

	/* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_DeInit(TIM2);
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update); // �����־λ  ����Ҫ�У��� ���� �����ж������жϸ��㿴
	TIM_Cmd(TIM2, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE); /*�ȹرյȴ�ʹ��*/
	NVIC_InitTypeDef nvic;

	nvic.NVIC_IRQChannelCmd = ENABLE;
	nvic.NVIC_IRQChannel = TIM2_IRQn;

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;

	NVIC_Init(&nvic);
	NVIC_SetPriority(TIM2_IRQn, 3);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	NVIC_SetPriority(TIM2_IRQn, 0);
#else
	Timer2Config(1000);
#endif
	NVIC_SetPriority(SysTick_IRQn, 0);
#elif defined STM32F4
	Timer2Config(10000);
#endif
}

//��ʱ������
void DeviceConfigCenter::TimerConfig(TIMER tim, int interval, int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
	switch (tim)
	{
	case Timer0:
		break;
	case Timer1:
		Timer1Config(interval);
		break;
	case Timer2:
		Timer2Config(interval);
		break;
	case Timer3:
		Timer3Config(interval);
		break;
	case Timer4:
		Timer4Config(interval);
		break;
	case Timer5:
		Timer5Config(interval);
		break;
	case Timer6:
		Timer6Config(interval);
		break;
	case Timer7:
		Timer7Config(interval);
		break;
	case Timer8:
		Timer8Config(interval);
		break;
	case Timer9:
		break;
	case Timer10:
		break;
	case Timer11:
		break;
	case Timer12:
		break;
	case Timer13:
		break;
	case Timer14:
		break;
	case Timer15:
		break;
	case Timer16:
		break;
	case Timer17:
		break;
	case Timer18:
		break;
	default:
		break;
	}
}
//��ʱ������
void DeviceConfigCenter::Timer0Config(int interval)
{
#if defined STM32F0

#elif defined STM32F1

#elif defined STM32F4

#endif
}
//��ʱ������
void DeviceConfigCenter::Timer1Config(int interval)
{
#if defined STM32F0

#elif defined STM32F1

#elif defined STM32F4

#endif
}
//��ʱ������
void DeviceConfigCenter::Timer2Config(int interval)
{
#if defined STM32F0
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;//����һ��TIM_InitTypeDef���͵Ľṹ��
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);//���жϱ�־���Ա��´��жϵ���ʹ��

	TIM_TimeBaseStructure.TIM_Period = interval;//1���ӻ�2000������
	TIM_TimeBaseStructure.TIM_Prescaler = 35999; //36000��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //TIM_CKD_DIV1
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//��ʼ����ʱ��
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//ʹ������ж�

	TIM_Cmd(TIM2, ENABLE);//��ʱ��ʹ��
#elif defined STM32F1
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIMx_CLK,x,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// �Զ���װ�ؼĴ����ܵ�ֵ(����ֵ)
	TIM_TimeBaseStructure.TIM_Period = 1000;

	// �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
	// ʱ��Ԥ��Ƶ��Ϊ71����������������ʱ��CK_CNT = CK_INT / (71+1)=1M
	TIM_TimeBaseStructure.TIM_Prescaler = 71;

	// ��ʼ����ʱ��TIMx, x
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	// ����������жϱ�־λ
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);

	// �����������ж�
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	// ʹ�ܼ�����
	TIM_Cmd(TIM2, ENABLE);

	// ��ʱ�ر�TIMx,x��ʱ�ӣ��ȴ�ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, DISABLE);

	/* ������ʱ�� TIMx,x ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
#elif defined STM32F4
	//arr���Զ���װֵ��
	//psc��ʱ��Ԥ��Ƶ��
	//��ʱ�����ʱ����㷽�� : Tout = ((arr + 1)*(psc + 1)) / Ft us.
	//Ft=��ʱ������Ƶ��,��λ:Mhz
	u16 arr = interval - 1;
	u16 psc = 8400 - 1;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);  ///ʹ��TIMʱ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);//��ʼ��TIM

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); //������ʱ�������ж�
	TIM_Cmd(TIM2, ENABLE); //ʹ�ܶ�ʱ��

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}
//��ʱ������
void DeviceConfigCenter::Timer3Config(int interval)
{
#if defined STM32F0

#elif defined STM32F1
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIMx_CLK,x,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	// �Զ���װ�ؼĴ����ܵ�ֵ(����ֵ)
	TIM_TimeBaseStructure.TIM_Period = 1000;

	// �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
	// ʱ��Ԥ��Ƶ��Ϊ71����������������ʱ��CK_CNT = CK_INT / (71+1)=1M
	TIM_TimeBaseStructure.TIM_Prescaler = 71;

	// ��ʼ����ʱ��TIMx, x
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	// ����������жϱ�־λ
	TIM_ClearFlag(TIM3, TIM_FLAG_Update);

	// �����������ж�
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

	// ʹ�ܼ�����
	TIM_Cmd(TIM3, ENABLE);

	// ��ʱ�ر�TIMx,x��ʱ�ӣ��ȴ�ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);

	/* ������ʱ�� TIMx,x ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
#elif defined STM32F4
	//arr���Զ���װֵ��
	//psc��ʱ��Ԥ��Ƶ��
	//��ʱ�����ʱ����㷽�� : Tout = ((arr + 1)*(psc + 1)) / Ft us.
	//Ft=��ʱ������Ƶ��,��λ:Mhz
	u16 arr = interval - 1;
	u16 psc = 8400 - 1;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  ///ʹ��TIMʱ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);//��ʼ��TIM

	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE); //������ʱ�������ж�
	TIM_Cmd(TIM3, ENABLE); //ʹ�ܶ�ʱ��

	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; //��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}
//��ʱ������
void DeviceConfigCenter::Timer4Config(int interval)
{
#if defined STM32F0

#elif defined STM32F1
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIMx_CLK,x,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	// �Զ���װ�ؼĴ����ܵ�ֵ(����ֵ)
	TIM_TimeBaseStructure.TIM_Period = 1000;

	// �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
	// ʱ��Ԥ��Ƶ��Ϊ71����������������ʱ��CK_CNT = CK_INT / (71+1)=1M
	TIM_TimeBaseStructure.TIM_Prescaler = 71;

	// ��ʼ����ʱ��TIMx, x
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	// ����������жϱ�־λ
	TIM_ClearFlag(TIM4, TIM_FLAG_Update);

	// �����������ж�
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

	// ʹ�ܼ�����
	TIM_Cmd(TIM4, ENABLE);

	// ��ʱ�ر�TIMx,x��ʱ�ӣ��ȴ�ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, DISABLE);

	/* ������ʱ�� TIMx,x ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
#elif defined STM32F4
	//arr���Զ���װֵ��
	//psc��ʱ��Ԥ��Ƶ��
	//��ʱ�����ʱ����㷽�� : Tout = ((arr + 1)*(psc + 1)) / Ft us.
	//Ft=��ʱ������Ƶ��,��λ:Mhz
	u16 arr = interval - 1;
	u16 psc = 8400 - 1;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);  ///ʹ��TIMʱ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);//��ʼ��TIM

	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE); //������ʱ�������ж�
	TIM_Cmd(TIM4, ENABLE); //ʹ�ܶ�ʱ��

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; //��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}
//��ʱ������
void DeviceConfigCenter::Timer5Config(int interval)
{
#if defined STM32F0

#elif defined STM32F1
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIMx_CLK,x,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	// �Զ���װ�ؼĴ����ܵ�ֵ(����ֵ)
	TIM_TimeBaseStructure.TIM_Period = 1000;

	// �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
	// ʱ��Ԥ��Ƶ��Ϊ71����������������ʱ��CK_CNT = CK_INT / (71+1)=1M
	TIM_TimeBaseStructure.TIM_Prescaler = 71;

	// ��ʼ����ʱ��TIMx, x
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);

	// ����������жϱ�־λ
	TIM_ClearFlag(TIM5, TIM_FLAG_Update);

	// �����������ж�
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	// ʹ�ܼ�����
	TIM_Cmd(TIM5, ENABLE);

	// ��ʱ�ر�TIMx,x��ʱ�ӣ��ȴ�ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, DISABLE);

	/* ������ʱ�� TIMx,x ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
#elif defined STM32F4
	//arr���Զ���װֵ��
	//psc��ʱ��Ԥ��Ƶ��
	//��ʱ�����ʱ����㷽�� : Tout = ((arr + 1)*(psc + 1)) / Ft us.
	//Ft=��ʱ������Ƶ��,��λ:Mhz
	u16 arr = interval - 1;
	u16 psc = 8400 - 1;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);  ///ʹ��TIMʱ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);//��ʼ��TIM

	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE); //������ʱ�������ж�
	TIM_Cmd(TIM5, ENABLE); //ʹ�ܶ�ʱ��

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn; //��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}
//��ʱ������
void DeviceConfigCenter::Timer6Config(int interval)
{
#if defined STM32F0

#elif defined STM32F1
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIMx_CLK,x,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

	// �Զ���װ�ؼĴ����ܵ�ֵ(����ֵ)
	TIM_TimeBaseStructure.TIM_Period = 1000;

	// �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
	// ʱ��Ԥ��Ƶ��Ϊ71����������������ʱ��CK_CNT = CK_INT / (71+1)=1M
	TIM_TimeBaseStructure.TIM_Prescaler = 71;

	// ��ʼ����ʱ��TIMx, x
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

	// ����������жϱ�־λ
	TIM_ClearFlag(TIM6, TIM_FLAG_Update);

	// �����������ж�
	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

	// ʹ�ܼ�����
	TIM_Cmd(TIM6, ENABLE);

	// ��ʱ�ر�TIMx,x��ʱ�ӣ��ȴ�ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, DISABLE);

	/* ������ʱ�� TIMx,x ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
#elif defined STM32F4
	//arr���Զ���װֵ��
	//psc��ʱ��Ԥ��Ƶ��
	//��ʱ�����ʱ����㷽�� : Tout = ((arr + 1)*(psc + 1)) / Ft us.
	//Ft=��ʱ������Ƶ��,��λ:Mhz
	u16 arr = interval - 1;
	u16 psc = 8400 - 1;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);  ///ʹ��TIMʱ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);//��ʼ��TIM

	TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE); //������ʱ�������ж�
	TIM_Cmd(TIM6, ENABLE); //ʹ�ܶ�ʱ��

	//NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn; //��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}
//��ʱ������
void DeviceConfigCenter::Timer7Config(int interval)
{
#if defined STM32F0

#elif defined STM32F1
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	// ����TIMx_CLK,x,���ڲ�ʱ��CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	// �Զ���װ�ؼĴ����ܵ�ֵ(����ֵ)
	TIM_TimeBaseStructure.TIM_Period = 1000;

	// �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж�
	// ʱ��Ԥ��Ƶ��Ϊ71����������������ʱ��CK_CNT = CK_INT / (71+1)=1M
	TIM_TimeBaseStructure.TIM_Prescaler = 71;

	// ��ʼ����ʱ��TIMx, x
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);

	// ����������жϱ�־λ
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);

	// �����������ж�
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);

	// ʹ�ܼ�����
	TIM_Cmd(TIM7, ENABLE);

	// ��ʱ�ر�TIMx,x��ʱ�ӣ��ȴ�ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, DISABLE);

	/* ������ʱ�� TIMx,x ���¿�ʱ�ӣ���ʼ��ʱ */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
#elif defined STM32F4
	//arr���Զ���װֵ��
	//psc��ʱ��Ԥ��Ƶ��
	//��ʱ�����ʱ����㷽�� : Tout = ((arr + 1)*(psc + 1)) / Ft us.
	//Ft=��ʱ������Ƶ��,��λ:Mhz
	u16 arr = interval - 1;
	u16 psc = 8400 - 1;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);  ///ʹ��TIMʱ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);//��ʼ��TIM

	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); //������ʱ�������ж�
	TIM_Cmd(TIM7, ENABLE); //ʹ�ܶ�ʱ��

	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn; //��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}
//��ʱ������
void DeviceConfigCenter::Timer8Config(int interval)
{
#if defined STM32F0

#elif defined STM32F1

#elif defined STM32F4
	//arr���Զ���װֵ��
	//psc��ʱ��Ԥ��Ƶ��
	//��ʱ�����ʱ����㷽�� : Tout = ((arr + 1)*(psc + 1)) / Ft us.
	//Ft=��ʱ������Ƶ��,��λ:Mhz
	u16 arr = interval - 1;
	u16 psc = 8400 - 1;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM8, ENABLE);  ///ʹ��TIMʱ��

	TIM_TimeBaseInitStructure.TIM_Period = arr; 	//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler = psc;  //��ʱ����Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;

	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);//��ʼ��TIM

	TIM_ITConfig(TIM8, TIM_IT_Update, ENABLE); //������ʱ�������ж�
	TIM_Cmd(TIM8, ENABLE); //ʹ�ܶ�ʱ��

	//NVIC_InitStructure.NVIC_IRQChannel = TIM8_IRQn; //��ʱ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01; //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03; //�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}
void DeviceConfigCenter::TimerConfigNvic(TIMER tim, int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
	switch (tim)
	{
	case Timer0:
		Timer0ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer1:
		Timer1ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer2:
		Timer2ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer3:
		Timer3ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer4:
		Timer4ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer5:
		Timer5ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer6:
		Timer6ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer7:
		Timer7ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer8:
		Timer8ConfigNvic(NVIC_PriorityGroup, NVIC_IRQChannelPreemptionPriority, NVIC_IRQChannelSubPriorit);
		break;
	case Timer9:
		break;
	case Timer10:
		break;
	case Timer11:
		break;
	case Timer12:
		break;
	case Timer13:
		break;
	case Timer14:
		break;
	case Timer15:
		break;
	case Timer16:
		break;
	case Timer17:
		break;
	case Timer18:
		break;
	default:
		break;
	}
}
void DeviceConfigCenter::Timer0ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0

#elif defined STM32F1

#elif defined STM32F4

#endif
}
void DeviceConfigCenter::Timer1ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0

#elif defined STM32F1

#elif defined STM32F4

#endif
}
void DeviceConfigCenter::Timer2ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0
	NVIC_InitTypeDef   NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#elif defined STM32F1
	NVIC_InitTypeDef NVIC_InitStructure;
	// �����ж���Ϊ0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;

	// ���������ȼ�Ϊ 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;

	// ������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriorit;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#elif defined STM32F4

#endif
}
void DeviceConfigCenter::Timer3ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0

#elif defined STM32F1
	NVIC_InitTypeDef NVIC_InitStructure;
	// �����ж���Ϊ0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;

	// ���������ȼ�Ϊ 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;

	// ������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriorit;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#elif defined STM32F4

#endif
}
void DeviceConfigCenter::Timer4ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0

#elif defined STM32F1
	NVIC_InitTypeDef NVIC_InitStructure;
	// �����ж���Ϊ0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;

	// ���������ȼ�Ϊ 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;

	// ������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriorit;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#elif defined STM32F4

#endif
}
void DeviceConfigCenter::Timer5ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0

#elif defined STM32F1
#ifdef STM32F10X_HD
	NVIC_InitTypeDef NVIC_InitStructure;
	// �����ж���Ϊ0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;

	// ���������ȼ�Ϊ 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;

	// ������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriorit;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
#elif defined STM32F4

#endif
}
void DeviceConfigCenter::Timer6ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0

#elif defined STM32F1
#ifdef STM32F10X_HD
	NVIC_InitTypeDef NVIC_InitStructure;
	// �����ж���Ϊ0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;

	// ���������ȼ�Ϊ 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;

	// ������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriorit;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
#elif defined STM32F4

#endif
}
void DeviceConfigCenter::Timer7ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0

#elif defined STM32F1
#ifdef STM32F10X_HD
	NVIC_InitTypeDef NVIC_InitStructure;
	// �����ж���Ϊ0
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM7_IRQn;

	// ���������ȼ�Ϊ 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = NVIC_IRQChannelPreemptionPriority;

	// ������ռ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = NVIC_IRQChannelSubPriorit;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
#elif defined STM32F4

#endif
}
void DeviceConfigCenter::Timer8ConfigNvic(int NVIC_PriorityGroup, int NVIC_IRQChannelPreemptionPriority, int NVIC_IRQChannelSubPriorit)
{
#if defined STM32F0

#elif defined STM32F1

#elif defined STM32F4

#endif
}

//ϵͳ
void OS_ComSendChk(void *param)
{
	//��鴮���Ƿ���Է���
#if defined COM1TXDMAFLAG
	if (USART_GetFlagStatus(USART1, USART_FLAG_TXE) != RESET)
	{
		int len = Txx1.Length();
		if (len == 0)
			return;
		for (int i = 0; i < len; i++)
		{
			com1bufff[i] = Txx1.Dequeue();
		}
		Txx1.Clear();
		USART1_SendDMA((uint8_t*)com1bufff, len);
	}
#endif

#if defined COM2TXDMAFLAG
	if (USART_GetFlagStatus(USART2, USART_FLAG_TXE) != RESET)
	{
		int len = Txx2.Length();
		if (len == 0)
			return;
		for (int i = 0; i < len; i++)
		{
			com2bufff[i] = Txx2.Dequeue();
		}
		Txx2.Clear();
		USART2_SendDMA((uint8_t*)com2bufff, len);
	}
#endif

#if defined COM3TXDMAFLAG
	if (USART_GetFlagStatus(USART3, USART_FLAG_TXE) != RESET)
	{
		int len = Txx3.Length();
		if (len == 0)
			return;
		for (int i = 0; i < len; i++)
		{
			com3bufff[i] = Txx3.Dequeue();
		}
		Txx3.Clear();
		USART3_SendDMA((uint8_t*)com3bufff, len);
	}
#endif

#if defined COM4TXDMAFLAG
	if (USART_GetFlagStatus(USART2, USART_FLAG_TXE) != RESET)
	{
		int len = Txx4.Length();
		if (len == 0)
			return;
		for (int i = 0; i < len; i++)
		{
			com4bufff[i] = Txx4.Dequeue();
		}
		Txx4.Clear();
		//UART4_SendDMA((uint8_t*)com4bufff, len);
	}
#endif

#if defined COM5TXDMAFLAG
	if (USART_GetFlagStatus(UART5, USART_FLAG_TXE) != RESET)
	{
		int len = Txx5.Length();
		if (len == 0)
			return;
		for (int i = 0; i < len; i++)
		{
			com5bufff[i] = Txx5.Dequeue();
		}
		Txx5.Clear();
		//UART5_SendDMA((uint8_t*)com5bufff, len);
	}
#endif
}
//���ڽ����ж�
void OS_ComRcvChk(void *param)
{
	int ms = Sys.Ms();
#if (defined USECOM1RXD)&&(! defined COM1RCVIDLEINTFLAG)
	if ((ms - DeviceConfigCenter::RcvLastTimeCOM1 > DeviceConfigCenter::RcvCom1PackInterval) && (Rxx1.Length() > 0))
	{
		if (DeviceConfigCenter::PRcvCOM1)
		{
			(*DeviceConfigCenter::PRcvCOM1)();
		}
	}
#endif
#if (defined USECOM2RXD)&&(! defined COM2RCVIDLEINTFLAG)
	if ((ms - DeviceConfigCenter::RcvLastTimeCOM2 > DeviceConfigCenter::RcvCom2PackInterval) && (Rxx2.Length() > 0))
	{
		if (DeviceConfigCenter::PRcvCOM2)
		{
			(*DeviceConfigCenter::PRcvCOM2)();
		}
	}
#endif
#if (defined USECOM3RXD)&&(! defined COM3RCVIDLEINTFLAG)
	if ((ms - DeviceConfigCenter::RcvLastTimeCOM3 > DeviceConfigCenter::RcvCom3PackInterval) && (Rxx3.Length() > 0))
	{
		if (DeviceConfigCenter::PRcvCOM3)
		{
			(*DeviceConfigCenter::PRcvCOM3)();
		}
	}
#endif
#if (defined USECOM4RXD)&&(! defined COM4RCVIDLEINTFLAG)
	if ((ms - DeviceConfigCenter::RcvLastTimeCOM4 > DeviceConfigCenter::RcvCom4PackInterval) && (Rxx4.Length() > 0))
	{
		if (DeviceConfigCenter::PRcvCOM4)
		{
			(*DeviceConfigCenter::PRcvCOM4)();
		}
	}
#endif
#if (defined USECOM5RXD)&&(! defined COM5RCVIDLEINTFLAG)
	if ((ms - DeviceConfigCenter::RcvLastTimeCOM5 > DeviceConfigCenter::RcvCom5PackInterval) && (Rxx5.Length() > 0))
	{
		if (DeviceConfigCenter::PRcvCOM5)
		{
			(*DeviceConfigCenter::PRcvCOM5)();
		}
	}
#endif
}