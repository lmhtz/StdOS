#include "I2C.h"

#ifdef STM32F0
	#include "stm32f0xx.h"
#elif defined STM32F1
	#include "stm32f10x.h"
#elif defined STM32F4
	#include "stm32f4xx.h"
#endif

bool HardI2C::SendAddress(int addr, bool tx)
{
	return false;
}
void HardI2C::Ack(bool ack)
{
	
}
void HardI2C::Stop()
{
}
void HardI2C::Start()
{
}
void HardI2C::OnInit()
{
}
void HardI2C::OnOpen()
{
}
void HardI2C::OnClose()
{
}
// �ȴ�Ack��Ĭ��0��ʾ����ȫ��Retry
bool HardI2C::WaitAck(int retry)
{
}
byte HardI2C::ReadByte()
{
	return 0;
}
void HardI2C::WriteByte(byte dat)
{
}