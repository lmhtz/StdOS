#ifndef _List_H_
#define _List_H_
#include "Type.h"

typedef int (*IComparer)(const void* v1, const void* v2);

// 变长列表。仅用于存储指针
class IList
{
public:
    IComparer	Comparer;	// 比较器

	IList();
   	
	inline int Count()	const { return _Count; }

	// 添加单个元素
    void Add(void* item);

	// 删除指定位置元素
	void RemoveAt(int index);

	// 删除指定元素
	int Remove(const void* item);
	
	// 查找指定项。不存在时返回-1
	int FindIndex(const void* item) const;
	
    // 重载索引运算符[]，返回指定元素的第一个
    void* operator[](int i) const;
	
private:
	int		_Count;
	int		_Capacity;

	uint32_t _tmpbuf[30];
private:
	void Init();
};

template<typename T>
class List : public IList
{
	static_assert(sizeof(T) <= 4, "List only support pointer or int");
public:	
	// 添加单个元素
    void Add(T item) { IList::Add((void*)item); }

	// 删除指定元素
	int Remove(const T item) { return IList::Remove((const void*)item); }

	// 查找指定项。不存在时返回-1
	int FindIndex(const T item) const { return IList::FindIndex((const void*)item); }

    // 重载索引运算符[]，返回指定元素的第一个
    T operator[](int i) const	{ return (T)IList::operator[](i); }
};

#endif
