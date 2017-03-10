/*
栈：向下生长
堆：向上生长，内存分配从此处分配



 */
#include "NewDelete.h"
#include <stdlib.h>
#include "Sys.h"

extern "C"
{
    extern uint __heap_base;
    extern uint __heap_limit;
}

void *operator new(uint size)
{
    debug_printf("new size: %d", size);
    void *p = malloc(size);
    if (!p)
	{
        debug_printf(" malloc failed! size=%d", size);
	}
    else
    {
        debug_printf(" 0X%08x", p);
        // 如果堆只剩下64字节，则报告失败，要求用户扩大堆空间以免不测
		#if 0
        uint end = (uint) &__heap_limit;
        if ((uint)p + size + 0x40 >= end)
            debug_printf(" + %d near HeapEnd=0X%08x", size, end);
		#endif
    }
	debug_printf("\r\n");
    //assert_param(p);
    return p;
}

void *operator new[](uint size)
{
    debug_printf("new size[]: %d", size);
    void *p = malloc(size);
    if (!p)
        debug_printf(" malloc failed! size=%d", size);
    else
    {
        debug_printf(" 0x%08x", p);
        // 如果堆只剩下64字节，则报告失败，要求用户扩大堆空间以免不测
		#if 0
        uint end = (uint) &__heap_limit;
        if ((uint)p + size + 0x40 >= end)
            debug_printf(" + %d near HeapEnd=0x%08x", size, end);
		#endif
    }
	debug_printf("\r\n");
    //assert_param(p);
    return p;
}

void operator delete (void *p)
{
    debug_printf("delete 0x%08x\r\n", p);
    if (p)
        free(p);
}

void operator delete [](void *p)
{
    debug_printf("delete[] 0x%08x\r\n", p);
    if (p)
        free(p);
}
