#pragma once 
#include "BasePort.h"

// 看门狗
class CWatchDog
{
    public:
        CWatchDog(uint ms = 3000);
        ~CWatchDog();
    public:
        byte Init();
        void Feed(); // 喂狗
    private:
        uint timeout; // 当前超时时间
};
