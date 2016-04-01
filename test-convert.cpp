#include "string_convert.hpp"

#include <cassert>
#include <iostream>


int main()
{
    std::string ansi_str = "中文123";
    std::string utf8_str = u8"中文123";
    std::wstring unic_str = L"中文123";
    
    assert(string_convert::ansi_to_unicode(ansi_str) == unic_str);
    assert(string_convert::unicode_to_ansi(unic_str) == ansi_str);
    assert(string_convert::utf8_to_unicode(utf8_str) == unic_str);
    assert(string_convert::unicode_to_utf8(unic_str) == utf8_str);
    assert(string_convert::ansi_to_utf8(ansi_str) == utf8_str);
    assert(string_convert::utf8_to_ansi(utf8_str) == ansi_str);

    return 0;
}
