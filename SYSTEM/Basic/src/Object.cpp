#include "stdio.h"
#include "Object.h"

#if 0
    //输出对象的字符串表示方式
    virtual String &Object::ToStr(String &str)const{}
    //输出对象的字符串表示方式.支持RVO优化
    virtual String &Object::ToString()const{}
#endif 
void Object::Show(bool newLine)const
{
    if (newLine)
    {
        printf("\r\n");
    }
}

#if 0
    const CType Object::GetType()const{}
#endif
#if 0
//输出对象的字符串表示方式.支持RVO优化
String Object::ToString()const
{	
	return String("Object");
}
#endif
