#pragma once

#ifndef _LOTUSTYPES_
#define _LOTUSTYPES_

#include <string>
#include <unordered_map>
#include <type_traits>
#include <memory>

namespace lotus {

    class IValue;
    class IExpression;
    class IStatement;

	using String = std::wstring;
    using Char = wchar_t;

    template<typename _KeyTy, typename _ValTy>
    using Map = std::unordered_map<_KeyTy, _ValTy>;

    template<typename _ValTy>
    using StringMap = Map<String, _ValTy>;

    template<typename _Ty>
    using Ptr = std::shared_ptr<_Ty>;

    using Value = Ptr<IValue>;
    using Expression = Ptr<IExpression>;
    using Statement = Ptr<IStatement>;
}

#endif // _LOTUSTYPES_
