#include "List.h"
#include "Sys.h"

IList::IList()
{
	this->Init();
}

// 添加单个元素
void IList::Add(void *item)
{
	if (this->_Count < this->_Capacity)
	{
		this->_tmpbuf[this->_Count++] = (uint32_t)item;
	}
	else
	{
		debug_printf("列表容量不够 %d，请增加\n",this->_Capacity);
	}
}

// 删除指定位置元素
void IList::RemoveAt(int index)
{
	return;
}

// 删除指定元素
int IList::Remove(const void *item)
{
	int idx=this->FindIndex(item);
	if(idx>=0)
	this->RemoveAt(idx);
    return idx;
}

// 查找指定项。不存在时返回-1
int IList::FindIndex(const void *item)const
{
    for (int i = 0; this->_Count > i; ++i)
    {
        if ((const void*)(this->_tmpbuf[i]) == item)
            return i;
        if (this->Comparer((void*)this->_tmpbuf[i], item))
        {
            return i;
        }
    }
    return  - 1;
}

// 重载索引运算符[]，返回指定元素的第一个
void *IList::operator[](int i)const
{
	if(i>=0&&this->_Count>i)
	{
		return (void *)(this->_tmpbuf[i]);
	}
	else
	{
		return nullptr;
	}
}

void IList::Init()
{
	this->_Count=0;
	this->_Capacity = ArrayLength(this->_tmpbuf);
}
