#include "Queue.h"

byte buf[512];
Queue::Queue():_s(buf,512)
{	
	return ;
}


void Queue::SetCapacity(int len)
{
    return ;
}

void Queue::Clear()
{
    return ;
}

void Queue::Enqueue(byte dat)
{
    return ;
}

byte Queue::Dequeue()
{
    return 0;
}

// 批量写入
int Queue::Write(const Buffer &bs)
{
    return 0;
}

// 批量读取
int Queue::Read(Buffer &bs)

{
    return 0;
}
