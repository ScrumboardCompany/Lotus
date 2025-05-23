#pragma once

#ifndef _CLASSSTRUCTURESINFO_
#define _CLASSSTRUCTURESINFO_

#include "utils/lotusTypes.h"
#include "parser/function/function.h"

namespace lotus {

	enum class AccessModifierType {
		PUBLIC,
		PRIVATE,
		PROTECTED,
	};

	struct LOTUS_API ClassMemberInfo {
		ClassMemberInfo() = default;
		ClassMemberInfo(const AccessModifierType& accessModifier) : accessModifier(accessModifier) {}

		AccessModifierType accessModifier = AccessModifierType::PRIVATE;
	};

	struct LOTUS_API FieldMemberInfo : public ClassMemberInfo {
		FieldMemberInfo() = default;
		FieldMemberInfo(const Value& value, const AccessModifierType& accessModifier) 
			: ClassMemberInfo(accessModifier), value(value) {}

		Value value;
	};

	struct LOTUS_API MethodMemberInfo : public ClassMemberInfo {
		MethodMemberInfo() = default;
		MethodMemberInfo(const Function& value, const AccessModifierType& accessModifier)
			: ClassMemberInfo(accessModifier), value(value) {}

		Function value;
	};
}

#endif // _CLASSSTRUCTURESINFO_