#include "Led.h"

CLed::CLed(PinPort pin, ushort period1, ushort onTime1):BasePort(pin)
{    
    this->SetModeOut_PP();
    this->period = period1;
    this->onTime = onTime1;
}

byte CLed::Init(void)
{
    return 0;
}

void CLed::On(void)
{
    this->Reset();
}

void CLed::Off(void)
{
    this->Set();	
}
