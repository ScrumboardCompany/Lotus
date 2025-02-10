#include "parser/expression/setExpression.h"

using namespace lotus;

lotus::SetExpression::SetExpression(const String& name, Expression expression, Variables& variables)
	: name(name), expression(expression), variables(variables) {}

Value lotus::SetExpression::eval() {
	variables.set(name, expression->eval());

	return variables.get(name);
}
