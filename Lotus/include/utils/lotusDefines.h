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

#define STRING_LITERAL(str) []{ \
    if constexpr (std::is_same_v<lotus::String, std::string>) \
        return str; \
    else \
        return L##str; \
}()

#define CHAR_LITERAL(ch) []{ \
    if constexpr (std::is_same_v<Char, char>) \
        return ch; \
    else \
        return L##ch; \
}()

#endif // _LOTUSDEFINES_