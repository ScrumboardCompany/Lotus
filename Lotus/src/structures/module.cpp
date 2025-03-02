#include "structures/module.h"

using namespace lotus;

FieldMemberInfo lotus::FIELD(const AccessModifierType& accessModifier, const Value& value) {
	return FieldMemberInfo(value, accessModifier);
}