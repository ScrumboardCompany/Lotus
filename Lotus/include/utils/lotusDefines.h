#pragma once

#ifndef _LOTUSDEFINES_
#define _LOTUSDEFINES_

#define MAKE_PTR std::make_shared

#define LOTUS_VERSION 1.18
#define EOF_TOKEN lotus::Token({ lotus::TokenType::END_OF_FILE, STRING_LITERAL("")})

#ifdef BUILDING_DLL
#define LOTUS_API __declspec(dllexport)
#elif defined(USING_DLL)
#define LOTUS_API __declspec(dllimport)
#else
#define LOTUS_API
#endif

#define RETURN_VALUE(value) throw Value(value);

#define STRING_LITERAL(str) []{ \
    if constexpr (::std::is_same_v<lotus::String, std::string>) \
        return str; \
    else \
        return L##str; \
}()

#define STRING_VAR_LITERAL(var) ([](const char* str) { \
    if constexpr (::std::is_same_v<lotus::String, std::string>) \
        return std::string(str); \
    else \
        return std::wstring(str, str + std::char_traits<char>::length(str)); \
})(var)

#define CHAR_LITERAL(ch) []{ \
    if constexpr (::std::is_same_v<Char, char>) \
        return ch; \
    else \
        return L##ch; \
}()

#endif // _LOTUSDEFINES_