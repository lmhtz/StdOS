/*
缓冲区 Buffer
Buffer 表示一个缓冲区，内部由一个指针和一个长度组成。
整个系统设计不允许传输单字节指针， 以避免因处理不当而带来的内存泄漏
或非法修改其它对象的数据。
常用操作：
1) 使用指针和长度构造一个缓冲区。GetBuffer 返回指针，Length 返回长度。
Buffer 可直接与指针进行相等比较。
2) 从源指针拷贝数据到缓冲区。赋值号是拷贝数据而不是替换内部指针。
以下例程，bs=bts 将会从 bts 拷贝 4 个字节到 bs，也就是 buf 所在内存区域。
如果源指针数据少于缓冲区长度， 那么会在源指针数据后面接着拷贝其它数
从缓冲区拷贝数据到另一个缓冲区。特别注意源缓冲区长度大于目标缓冲区
的情况。
改变缓冲区长度 SetLength。
SetLength 可以把缓冲区长度设置的更小。如果设置更大，则涉及自动扩容
问题。
当源缓冲区长度大于目标缓冲区时，Buffer 本身会报错，但是 Buffer 的子类
Array/ByteArray/String 等会调用 SetLength 自动扩容，加大缓冲区。
5) 高级拷贝 Copy/CopyTo。
支持缓冲区和缓冲区、缓冲区和数据指针之间指定偏移和长度的高级拷贝。
特别注意，目标缓冲区长度不足时，参考 SetLength 扩容原则。
6) 截取子缓冲区 Sub
7) 转为十六进制字符串 ToHex
8) 缓冲区与整型数据互换 ToUInt32/Write
9) 二进制数据直接作为字符串 AsString()
 */
#pragma once

#include <Type.h>

class Buffer
{
    public:
        //返回指针
        void GetBuffer();
        //长度
        ushort Length();
        //设置长度，可自动扩容
        void SetLength(ushort len);
        //拷贝数据，默认-1长度表示当前长度
        virtual void Copy(int destIndex, const void *src, int len);
        //把数据复制到目标缓冲区，默认-1长度表示当前长度
        virtual void CopyTo(int destIndex, const void *dest, int len)const;
        //拷贝数据，默认-1长度表示两者最小长度
        virtual void Copy(int destIndex, const Buffer &sec, int srcIndex, int len);
        //从另一个对象拷贝数据和长度，长度不足且扩容失败时报错
        int Copy(const Buffer &src, int destIndex = 0);
        //截取自缓冲区
        void Sub();
        //转换为16进制字符串
        void ToHex();
        //二进制数据直接作为字符串
        void AsString();

};
