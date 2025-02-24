#include "parser/expression/letExpression.h"
#include "structures/module.h"

using namespace lotus;

lotus::LetExpression::LetExpression(const String& name, const Expression& expression)
	: name(name), expression(expression) {}

Value lotus::LetExpression::eval(Module& module) {
	if (expression) {
		module.variables.declare(name, expression->eval(module));
	}
	else {
		module.variables.declare(name);
	}
	return module.variables.get(name);
}
