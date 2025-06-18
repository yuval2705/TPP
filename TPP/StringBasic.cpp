#include <stdlib.h>
#include "StringBasic.h"
#include <string>

StringBasic::StringBasic(char* str)
{
    this->m_length = (unsigned)std::strlen(str);

    this->m_str = new char[this->m_length + 1]{0};
    std::memcpy(this->m_str, str, m_length);
}

StringBasic::StringBasic(const char str[]) : StringBasic((char*)(str))
{
}

StringBasic::StringBasic() : StringBasic("")
{
}

StringBasic::StringBasic(char chr) : StringBasic("-")
{
    this->m_str[0] = chr;
}

StringBasic::StringBasic(StringBasic& str) : StringBasic(str.getStr())
{
}

unsigned StringBasic::getLength()
{
    return this->m_length;
}

char* StringBasic::getStr()
{
    return this->m_str;
}

StringBasic::~StringBasic()
{
    delete[] this->m_str;
}
