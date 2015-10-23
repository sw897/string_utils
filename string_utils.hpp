#ifndef UTIL_STRING_UTILS_HPP
#define UTIL_STRING_UTILS_HPP

//http://sourceforge.net/projects/utfcpp/
#ifdef USE_UTFCPP
#include <utf8.h>
#endif

#ifdef _WINDOWS
  #include <windows.h>
#endif

#include <cstring>
#include <algorithm>
#include <sstream>
#include <iomanip>

namespace string_utils {

    template <typename Str> struct tokenizer;

    template <typename Str>
    Str to_upper(const Str& str)
    {
        Str temp(str);
        std::transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
        return temp;
    }

    template <typename Str>
    Str to_lower(const Str& str)
    {
        Str temp(str);
        std::transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        return temp;
    }

    template <typename Str>
    Str trim_left(const Str& str)
    {
        Str temp(str);
        for (auto it = temp.begin(); it != temp.end(); it++) {
            if (!isspace(*it)) {
                break;
            }
        }
        if (it == temp.end()) {
            temp.clear();
        } else {
            temp.erase(temp.begin(), it);
        }
    }

    template <typename Str>
    Str trim_right(const Str& str)
    {
        Str temp(str);
        for (auto it = temp.end() - 1; ;it--) {
            if (!isspace(*it)) {
                temp.erase(it + 1, temp.end());
                break;
            }
            if (it == temp.begin()) {
                temp.clear();
                break;
            }
        }
        return temp;
    }

    template <typename Str>
    Str trim(const Str& str)
    {
        Str temp = trim_left(str);
        return trim_right(temp);
    }

    template <typename Str>
    bool starts_with(Str const & value, Str const & starting)
    {
        if (starting.size() > value.size()) return false;
        return std::equal(starting.begin(), starting.end(), value.begin());
    }

    template <typename Str>
    bool ends_with(Str const & value, Str const & ending)
    {
        if (ending.size() > value.size()) return false;
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    template <typename Str>
    bool equals_ignore_case(const Str& str1, const Str& str2)
    {
        return to_lower(str1) == to_lower(str2);
    }

    template <typename T, typename Str>
    T from_string(const Str& str)
    {
        T obj;
        std::basic_istringstream<typename Str::value_type> temp(str);
        temp >> obj;
        return obj;
    }

    template <typename Str>
    bool from_string(const Str& str)
    {
        bool obj;
        std::basic_istringstream<typename Str::value_type> temp(str);
        temp >> std::boolalpha >> obj;
        return obj;
    }

    template <typename T, typename Str>
    T from_hex_string(const Str& str)
    {
        T obj;
        std::basic_istringstream<typename Str::value_type> temp(str);
        temp >> std::hex >> obj;
        return obj;
    }

    template <typename Str, typename T>
    Str to_string(const T& var)
    {
        std::basic_ostringstream<typename Str::value_type> temp;
        temp << var;
        return temp.str();
    }

    template <typename Str>
    Str to_string(bool var)
    {
        std::basic_ostringstream<typename Str::value_type> temp;
        temp << std::boolalpha << var;
        return temp.str();
    }

    template <typename Str, typename T>
    Str to_hex_string(const T& var, int width)
    {
        std::basic_ostringstream<typename Str::value_type> temp;
        temp << std::hex;
        if(width > 0)
        {
            temp << std::setw(width) << std::setfill<typename Str::value_type>('0');
        }
        temp << var;
        return temp.str();
    }

    template <typename Str>
    std::vector<Str> split(Str const& str, Str const& delimiters)
    {
        std::vector<Str> ss;
        tokenizer<Str> token(str, delimiters);
        while (token.next_token())
        {
            ss.push_back(token.get_token());
        }
        return ss;
    }

    std::string url_decode(std::string const& in)
    {
        std::string out;
        out.reserve(in.size());
        for (std::size_t i = 0; i < in.size(); ++i)
        {
            if (in[i] == '%')
            {
                if (i + 3 <= in.size())
                {
                    int value = 0;
                    std::istringstream is(in.substr(i + 1, 2));
                    if (is >> std::hex >> value)
                    {
                        out += static_cast<char>(value);
                        i += 2;
                    }
                    else
                    {
                        out.clear();
                        return out;
                    }
                }
                else
                {
                    out.clear();
                    return out;
                }
            }
            else if (in[i] == '+')
            {
                out += ' ';
            }
            else
            {
                out += in[i];
            }
        }
        return out;
    }

    std::wstring utf8_to_unicode(std::string const& str)
    {
        size_t source_len = str.length();
        if (source_len == 0)
        {
            return std::wstring();
        }
        const char* source = str.c_str();
        size_t dest_len = 0;
#ifdef _WINDOWS
        dest_len = MultiByteToWideChar(CP_UTF8, 0, source, source_len, 0, 0);
#else
        dest_len = mbstowcs(nullptr, source, source_len);
#endif
        if (dest_len <= 0)
        {
            return std::wstring();
        }
        std::wstring dest(dest_len, L'\0');
#ifdef _WINDOWS
        dest_len = MultiByteToWideChar(CP_UTF8, 0, source, source_len, &dest[0], dest.length());
#else
        dest_len = mbstowcs(&dest[0], source, source_len);
#endif
        if (dest_len <= 0)
        {
            return std::wstring();
        }
        return dest;
    }

    std::string unicode_to_utf8(std::wstring const& str)
    {
        size_t source_len = str.length();
        if (source_len <= 0)
        {
            return std::string();
        }
        const wchar_t * source = str.c_str();
        size_t dest_len = 0;
#ifdef _WINDOWS
        dest_len = WideCharToMultiByte(CP_UTF8, 0, source, source_len, 0, 0, 0, 0);
#else
        dest_len = wcstombs(nullptr, source, source_len);
#endif
        if (dest_len <= 0)
        {
            return std::string();
        }
        std::string dest(dest_len, '\0');
#ifdef _WINDOWS
        dest_len = WideCharToMultiByte(CP_UTF8, 0, source, source_len, &dest[0], dest_len, 0, 0);
#else
        dest_len = wcstombs(&dest[0], source, source_len);
#endif
        if (dest_len <= 0)
        {
            return std::string();
        }
        return dest;
    }

    std::wstring ansi_to_unicode(std::string const& str)
    {
        const char* source = str.c_str();
        size_t source_len = str.length();
        if (source_len == 0)
        {
            return std::wstring();
        }
        size_t dest_len = 0;
#ifdef _WINDOWS
        dest_len = MultiByteToWideChar(CP_ACP, 0, source, source_len, 0, 0);
#else
        dest_len = mbstowcs(nullptr, source, source_len);
#endif
        if (dest_len <= 0)
        {
            return std::wstring();
        }
        std::wstring dest(dest_len, L'\0');
#ifdef _WINDOWS
        dest_len = MultiByteToWideChar(CP_ACP, 0, source, source_len, &dest[0], dest.length());
#else
        dest_len = mbstowcs(&dest[0], source, source_len);
#endif
        if (dest_len <= 0)
        {
            return std::wstring();
        }
        return dest;
    }

    std::string unicode_to_ansi(std::wstring const& str)
    {
        size_t source_len = str.length();
        if (source_len <= 0)
        {
            return std::string();
        }
        const wchar_t * source = str.c_str();
        size_t dest_len = 0;
#ifdef _WINDOWS
        dest_len = WideCharToMultiByte(CP_ACP, 0, source, source_len, 0, 0, 0, 0);
#else
        dest_len = wcstombs(nullptr, source, source_len);
#endif
        if (dest_len <= 0)
        {
            return std::string();
        }
        std::string dest(dest_len, '\0');
#ifdef _WINDOWS
        dest_len = WideCharToMultiByte(CP_ACP, 0, source, source_len, &dest[0], dest_len, 0, 0);
#else
        dest_len = wcstombs(&dest[0], source, source_len);
#endif
        if (dest_len <= 0)
        {
            return std::string();
        }
        return dest;
    }

    std::string utf8_to_gbk(std::string const& str)
    {
        std::wstring temp = utf8_to_unicode(str);
#ifdef _WINDOWS
#else
        setlocale(LC_ALL, "zh_CN.GBK")
#endif
        std::string dest = unicode_to_ansi(temp);
#ifdef _WINDOWS
#else
        setlocale(LC_ALL, "")
#endif
        return dest;
    }

    std::string gbk_to_utf8(std::string const& str)
    {
#ifdef _WINDOWS
#else
        setlocale(LC_ALL, "zh_CN.GBK")
#endif
        std::wstring temp = ansi_to_unicode(str);
#ifdef _WINDOWS
#else
        setlocale(LC_ALL, "")
#endif
        std::string dest = unicode_to_utf8(temp);
        return dest;
    }

    std::string utf8_to_locale(std::string const& str)
    {
#ifdef _WINDOWS
        return utf8_to_gbk(str);
#else
        return std::string(str);
#endif
    }

    std::string locale_to_utf8(std::string const& str)
    {
#ifdef _WINDOWS
        return gbk_to_utf8(str);
#else
        return std::string(str);
#endif
    }

#ifdef USE_UTFCPP
    bool is_valid_utf8(std::string const& str)
    {
        return utf8::is_valid(str.begin(), str.end());
    }

    bool starts_with_bom(std::string const&str)
    {
        return utf8::starts_with_bom(str.begin(), str.end());
    }
#endif

    template <typename Str>
    struct tokenizer
    {
        tokenizer(Str const& str)
            : _string(str), _offset(0), _delimiters(" ")
        {}
        tokenizer(Str const& str, Str const& delimiters)
            : _string(str), _offset(0), _delimiters(delimiters)
        {}

        bool next_token()
        {
            return next_token(_delimiters);
        }

        bool next_token(Str const& delimiters)
        {
            size_t i = _string.find_first_not_of(delimiters, _offset);
            if (i == Str::npos)
            {
                _offset = _string.length();
                return false;
            }

            size_t j = _string.find_first_of(delimiters, i);
            if (j == Str::npos) {
                _token = _string.substr(i);
                _offset = _string.length();
                return true;
            }

            _token = _string.substr(i, j - i);
            _offset = j;
            return true;
        }

        const Str get_token() const
        {
            return _token;
        }

        void reset()
        {
            _offset = 0;
        }

        size_t _offset;
        const Str _string;
        Str _token;
        Str _delimiters;
    };
}

#endif // UTIL_STRING_UTILS_HPP
