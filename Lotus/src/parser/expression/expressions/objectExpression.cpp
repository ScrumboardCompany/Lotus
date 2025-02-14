#include "parser/expression/objectExpression.h"
#include "parser/value/structValue.h"
#include "structures/variables.h"

using namespace lotus;

lotus::ObjectExpression::ObjectExpression(const StringMap<Expression>& fields)
	: fields(fields) {
}

Value lotus::ObjectExpression::eval() {
	Value value = MAKE_PTR<StructValue>();
	for (auto& field : fields) {
		value->fields.emplace(field.first, field.second ? field.second->eval() : UNDEFINED());
	}

	return value;
}
