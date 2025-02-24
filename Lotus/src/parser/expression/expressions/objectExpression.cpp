#include "parser/expression/objectExpression.h"
#include "parser/value/objectValue.h"
#include "structures/variables.h"

using namespace lotus;

lotus::ObjectExpression::ObjectExpression(const StringMap<Expression>& fields)
	: fields(fields) {
}

Value lotus::ObjectExpression::eval(Module& module) {
	StringMap<Value> value;
	for (auto& field : fields) {
		value.emplace(field.first, field.second ? field.second->eval(module) : UNDEFINED());
	}

	return MAKE_PTR<ObjectValue>(value);
}
