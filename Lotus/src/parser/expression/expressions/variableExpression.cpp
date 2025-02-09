#include "parser/expression/variableExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::VariableExpression::VariableExpression(const String& name, Variables& variables) : name(name), variables(variables) {}

Value lotus::VariableExpression::eval() {
	return variables.get(name);
}