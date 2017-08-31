#include "WatchDog.h"

#ifdef STM32F0
	#include "stm32f0xx.h"
#elif defined STM32F1
	#include "stm32f10x.h"
#elif defined STM32F4
	#include "stm32f4xx.h"
#endif

int SetWatchDog( unsigned int a2)
{
  int v3; // r0@1
  int v4; // r0@1

//  IWDG_SetPrescaler();
//  v3 = IWDG_SetReload(a2);
//  v4 = IWDG_ReloadCounter(v3);
//  return IWDG_Enable(v4);
}
int OpenWatchDog(void)
{
//  RCC_LSICmd(1);
//  if ( RCC_GetFlagStatus(125) )
//    RCC_ClearFlag();
//  return IWDG_WriteAccessCmd(21845);
}
// ι��
void WatchDog::Feed()
{
    IWDG_ReloadCounter();
}
// ���ÿ��Ź�ι������ʱ�䣬������ʱ�佫����MCU
bool WatchDog::Config(uint ms)
{
    if (ms == 0)
    {
        debug_printf("WatchDog msTimeout %dms must larger than 0ms\r\n", ms);
        return false;
    }
    RCC_LSICmd(ENABLE);
    /* ���ϵͳ�Ƿ��IWDG���ûָ� */
    if (RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
    {
        /* ������ñ�ʶ */
        RCC_ClearFlag();
    }
    /* ��IWDG_PR��IWDG_RLR�Ĵ�����д���� */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    byte pre = IWDG_Prescaler_4;
    int mul = 4;
    // ������12λ 0~0x0FFF����reload = ms/1000 / (1/(LSI/mul)) = ms * LSI / (mul*1000) = ms * 40 / mul
    // ���ǵ�reload����Ŀ��ܣ�ÿ�ַ�Ƶ���ms = reload * mul / 40 ~= 102 * mul
    int i = 0;
    /*
    #define IWDG_Prescaler_4            ((byte)0x00)
    #define IWDG_Prescaler_8            ((byte)0x01)
    #define IWDG_Prescaler_16           ((byte)0x02)
    #define IWDG_Prescaler_32           ((byte)0x03)
    #define IWDG_Prescaler_64           ((byte)0x04)
    #define IWDG_Prescaler_128          ((byte)0x05)
    #define IWDG_Prescaler_256          ((byte)0x06)
     */
    for (i = IWDG_Prescaler_4; i <= IWDG_Prescaler_256; i++)
    {
        pre = i;
        mul = 1 << (i + 2);

        // �ж��Ƿ��ڷ�Χ֮��
        if (ms *40 / mul < 0x0FFF)
            break;
    }
    if (i > IWDG_Prescaler_256)
    {
        debug_printf("WatchDog msTimeout must smaller than %dms\r\n", 0x0FFF *256 / 40);
        return false;
    }
    IWDG_SetPrescaler(pre);
    /*if(ms < (0x0FFF * 32 / 40))
    {
    // IWDG������ʱ��: LSI/32=40KHz/32=1250Hz��ÿ����0.8ms
    IWDG_SetPrescaler(IWDG_Prescaler_32);
    }
    else
    {
    // IWDG������ʱ��: LSI/64=40KHz/64=625Hz��ÿ����0.4ms
    IWDG_SetPrescaler(IWDG_Prescaler_64);

    // ֱ�ӳ���2�����治���ظ�����
    ms >>= 2;
    }*/

    /* ���ü���������ֵΪ��ʱʱ��
    Counter Reload Value = ms / 1000 / IWDG������ʱ������
    = ms / 1000 / (1/(LSI/mul))
    = ms * LSI / (mul * 1000)
    = ms * 40k / (mul * 1000)
    = ms * 40 / mul
     */
    IWDG_SetReload(ms *40 / mul);

    /* ���� IWDG ������ */
    IWDG_ReloadCounter();

    /* �� IWDG (LSI����Ӳ����) */
    IWDG_Enable();

    Timeout = ms;

    return true;
}
// ���Ź��޷��رգ�ֻ������һ�����ֵ
void WatchDog::ConfigMax()
{
    /* ��IWDG_PR��IWDG_RLR�Ĵ�����д���� */
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);

    // �������Ź��޷��ر�
    IWDG_SetPrescaler(IWDG_Prescaler_256);
    IWDG_SetReload(0x0FFF); 
    IWDG_ReloadCounter();
}