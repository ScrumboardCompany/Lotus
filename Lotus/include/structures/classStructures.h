#pragma once

#ifndef _CLASSMEMBERINFO_
#define _CLASSMEMBERINFO_

#include "utils/lotusTypes.h"
#include "parser/function/function.h"

namespace lotus {

	enum class AccessModifierType {
		PUBLIC,
		PRIVATE,
	};

	struct ClassMemberInfo {
		AccessModifierType accessModifier = AccessModifierType::PRIVATE;
	};

	struct FieldMemberInfo : public ClassMemberInfo {
		Value value;
	};

	struct MethodMemberInfo : public ClassMemberInfo {
		Function value;
	};
}

#endif // _CLASSMEMBERINFO_