#include "string_utility.hpp"

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>


int main()
{
    std::string test = " aBc中文123 ";
    assert(string_utility_a::to_upper(test) == " ABC中文123 ");
    assert(string_utility_a::to_lower(test) == " abc中文123 ");
    assert(string_utility_a::trim(test) == "aBc中文123");
    assert(string_utility_a::starts_with(test, " aBc中") == true);
    assert(string_utility_a::ends_with(test, "c中文123 ") == true);
    assert(string_utility_a::starts_with(test, " ABc中") == false);
    assert(string_utility_a::ends_with(test, "C中文123 ") == false);
    assert(string_utility_a::istarts_with(test, " ABc中") == true);
    assert(string_utility_a::iends_with(test, "C中文123 ") == true);
    assert(string_utility_a::equals_ignore_case(test, " ABC中文123 ") == true);
    assert(string_utility_a::from_string<int>("123") == 123);
    assert(string_utility_a::from_string("false") == false);
    assert(string_utility_a::from_string("true") == true);
    assert(string_utility_a::to_string(123) == "123");
    assert(string_utility_a::to_string(true) == "true");
    assert(string_utility_a::to_string(false) == "false");
    assert(string_utility_a::from_hex_string<int>("007b") == 123);
    assert(string_utility_a::to_hex_string(123, 4) == "007b");
    assert(string_utility_a::split(test, "1")[0] == " aBc中文");
    assert(string_utility_a::split(test, "1")[1] == "23 ");

    std::wstring testw = L" aBc中文123 ";
    assert(string_utility_w::to_upper(testw) == L" ABC中文123 ");
    assert(string_utility_w::to_lower(testw) == L" abc中文123 ");
    assert(string_utility_w::trim(testw) == L"aBc中文123");
    assert(string_utility_w::starts_with(testw, L" aBc") == true);
    assert(string_utility_w::ends_with(testw, L"c中文123 ") == true);
    assert(string_utility_w::starts_with(testw, L" ABc") == false);
    assert(string_utility_w::ends_with(testw, L"C中文123 ") == false);
    assert(string_utility_w::istarts_with(testw, L" ABc") == true);
    assert(string_utility_w::iends_with(testw, L"C中文123 ") == true);
    assert(string_utility_w::equals_ignore_case(testw, L" ABC中文123 ") == true);
    assert(string_utility_w::from_string<int>(L"123") == 123);
    assert(string_utility_w::from_string(L"true") == true);
    assert(string_utility_w::from_string(L"false") == false);
    assert(string_utility_w::to_string(123) == L"123");
    assert(string_utility_w::to_string(true) == L"true");
    assert(string_utility_w::to_string(false) == L"false");
    assert(string_utility_w::from_hex_string<int>(L"007b") == 123);
    assert(string_utility_w::to_hex_string(123, 4) == L"007b");
    assert(string_utility_w::split(testw, L"1")[0] == L" aBc中文");
    assert(string_utility_w::split(testw, L"1")[1] == L"23 ");


    return 0;
}
