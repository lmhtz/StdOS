#ifndef _Buffer_H_
#define _Buffer_H_

#include "Type.h"

/*
数据区设计原则：
1，固定数据区封装 Buffer	=> Object

赋值运算符原则：
1，赋值运算拷贝长度和数据，核心语义为拷贝一份数据区
2，左值长度大于等于右值时，左值长度变小
3，左值长度小于右值时，左值尝试SetLength扩容
4，如果扩容失败，调试版断言失败，发行版左值长度保持不变
*/

// 内存数据区。包装指针和长度
// 参考C#的Byte[]，主要实现对象与指针的相互转化、赋值、拷贝、设置、截取、比较等操作。
// 内部指针指向的内存和长度，都由外部传入，内部不会自动分配。
// 所有的进出拷贝都是针对内部指针和最大长度，不会自动扩容，除非子类继承扩展SetLength。
// 拷贝的原则是尽力而为，有多少可用空间就拷贝多少长度。
class Buffer 
{
public:
	// 打包一个指针和长度指定的数据区
	Buffer(void* ptr, int len);
	// 禁用拷贝构造函数
	Buffer(const Buffer& buf) = delete;
	// 对象mov操作，指针和长度归我，清空对方
	Buffer(Buffer&& rval);

	// 从另一个对象拷贝数据和长度，长度不足且扩容失败时报错
	Buffer& operator = (const Buffer& rhs);
	// 从指针拷贝，使用我的长度
	Buffer& operator = (const void* ptr);
	// 对象mov操作，指针和长度归我，清空对方
	Buffer& operator = (Buffer&& rval);

	// 拿出指针供外部使用
	inline uint8_t* GetBuffer()				{ return (uint8_t*)_Arr; }
	inline const uint8_t* GetBuffer() const	{ return (uint8_t*)_Arr; }
	inline int Length() const				{ return _Length; }

	// 设置数组长度。只能缩小不能扩大，子类可以扩展以实现自动扩容
	virtual bool SetLength(int len);
	//virtual void SetBuffer(void* ptr, int len);

	// 设置指定位置的值，长度不足时自动扩容
	bool SetAt(int index, uint8_t value);

    // 重载索引运算符[]，返回指定元素的第一个字节
    uint8_t operator[](int i) const;
	// 支持 buf[i] = 0x36 的语法
    uint8_t& operator[](int i);

	// 原始拷贝、清零，不检查边界
	static void Copy(void* dest, const void* src, int len);
	static void Zero(void* dest, int len);

	// 拷贝数据，默认-1长度表示当前长度
	virtual int Copy(int destIndex, const void* src, int len);
	// 把数据复制到目标缓冲区，默认-1长度表示当前长度
	virtual int CopyTo(int srcIndex, void* dest, int len) const;
	// 拷贝数据，默认-1长度表示两者最小长度
	virtual int Copy(int destIndex, const Buffer& src, int srcIndex, int len);
	// 从另一个对象拷贝数据和长度，长度不足且扩容失败时报错
	int Copy(const Buffer& src, int destIndex = 0);

	// 用指定字节设置初始化一个区域
	int Set(uint8_t item, int index, int len);
	void Clear(uint8_t item = 0);

	// 截取一个子缓冲区，默认-1长度表示剩余全部
	//### 这里逻辑可以考虑修改为，当len大于内部长度时，直接用内部长度而不报错，方便应用层免去比较长度的啰嗦
	Buffer Sub(int index, int len);
	const Buffer Sub(int index, int len) const;

	uint16_t	ToUInt16(int index = 0) const;
	uint32_t	ToUInt32(int index = 0) const;
	uint64_t	ToUInt64(int index = 0) const;
	void Write(uint16_t value, int index = 0);
	void Write(short value, int index = 0);
	void Write(uint32_t value, int index = 0);
	void Write(int value, int index = 0);
	void Write(uint64_t value, int index = 0);

    explicit operator bool() const { return _Length > 0; }
    bool operator !() const { return _Length == 0; }
	int CompareTo(const Buffer& bs) const;
	int CompareTo(const void* ptr, int len = -1) const;
	friend bool operator == (const Buffer& bs1, const Buffer& bs2);
	friend bool operator == (const Buffer& bs1, const void* ptr);
	friend bool operator != (const Buffer& bs1, const Buffer& bs2);
	friend bool operator != (const Buffer& bs1, const void* ptr);

protected:
    char*	_Arr;		// 数据指针
	int		_Length;	// 长度
	int		_LengthOrigin;//原始长度，可以设置长度不超过原始长度

	void move(Buffer& rval);
public:
	virtual void Show(bool newLine = false) const;
	virtual void ShowHex(bool newLine = false, char sep = 0X20) const;
};

#endif
