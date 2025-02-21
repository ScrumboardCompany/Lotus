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

	struct ClassMemberInfo {
		ClassMemberInfo() = default;
		ClassMemberInfo(const AccessModifierType& accessModifier) : accessModifier(accessModifier) {}

		AccessModifierType accessModifier = AccessModifierType::PRIVATE;
	};

	struct FieldMemberInfo : public ClassMemberInfo {
		FieldMemberInfo() = default;
		FieldMemberInfo(const Value& value, const AccessModifierType& accessModifier) 
			: value(value), ClassMemberInfo(accessModifier) {}

		Value value;
	};

	struct MethodMemberInfo : public ClassMemberInfo {
		MethodMemberInfo() = default;
		MethodMemberInfo(const Function& value, const AccessModifierType& accessModifier)
			: value(value), ClassMemberInfo(accessModifier) {}

		Function value;
	};
}

#endif // _CLASSSTRUCTURESINFO_