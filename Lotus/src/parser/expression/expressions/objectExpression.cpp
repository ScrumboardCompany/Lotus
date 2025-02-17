#include "parser/expression/objectExpression.h"
#include "parser/value/classValue.h"
#include "structures/variables.h"

using namespace lotus;

lotus::ObjectExpression::ObjectExpression(const StringMap<Expression>& fields)
	: fields(fields) {
}

Value lotus::ObjectExpression::eval() {
	ClassValue value;
	for (auto& field : fields) {
		value.fields.emplace(field.first, field.second ? field.second->eval() : UNDEFINED());
	}
	value.type = STRING_LITERAL("object");

	return MAKE_PTR<ClassValue>(value);
}
