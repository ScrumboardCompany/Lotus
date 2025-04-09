#pragma once

#ifndef _LOTUSTYPES_
#define _LOTUSTYPES_

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>
#include <functional>

namespace lotus {

    class IValue;
    class IExpression;
    class IStatement;
    struct Module;

    struct ClassMemberInfo;
    struct FieldMemberInfo;
    struct MethodMemberInfo;

	using Int = int64_t;
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

    using RawFields_t = StringMap<std::pair<Expression, ClassMemberInfo>>;
    using Fields_t = StringMap<FieldMemberInfo>;
    using Methods_t = StringMap<std::vector<MethodMemberInfo>>;
    using ModuleBody_t = std::function<void(Module&)>;
}

#endif // _LOTUSTYPES_
