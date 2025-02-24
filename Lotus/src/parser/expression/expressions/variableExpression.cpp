#include "parser/expression/variableExpression.h"
#include "structures/module.h"

using namespace lotus;

lotus::VariableExpression::VariableExpression(const String& name) : name(name) {}

Value lotus::VariableExpression::eval(Module& module) {
	return module.variables.get(name);
}