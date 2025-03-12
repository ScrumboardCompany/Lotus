#pragma once

#ifndef _LOTUSDEFINES_
#define _LOTUSDEFINES_

#define MAKE_PTR std::make_shared

#define INT MAKE_PTR<IntValue>
#define FLOAT MAKE_PTR<FloatValue>
#define BOOL MAKE_PTR<BoolValue>
#define STRING MAKE_PTR<StringValue>
#define UNDEFINED MAKE_PTR<UndefinedValue>
#define ARRAY MAKE_PTR<ArrayValue>
#define OBJECT MAKE_PTR<ObjectValue>
#define LAMBDA MAKE_PTR<LambdaValue>

#define LOTUS_VERSION 1.17
#define EOF_TOKEN lotus::Token({ lotus::TokenType::END_OF_FILE, STRING_LITERAL("")})

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