#include "parser/expression/letExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::LetExpression::LetExpression(const String& name, Expression expression, Variables& variables)
	: name(name), expression(expression), variables(variables) {}

Value lotus::LetExpression::eval() {
	if (expression) {
		variables.declare(name, expression->eval());
	}
	else {
		variables.declare(name);
	}
	return variables.get(name);
}
