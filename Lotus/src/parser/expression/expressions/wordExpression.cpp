#include "parser/expression/wordExpression.h"
#include "structures/module.h"
#include "parser/value/lambdaValue.h"

using namespace lotus;

lotus::WordExpression::WordExpression(const String& name) : name(name) {}

Value lotus::WordExpression::eval(Module& module) {
	return module.variables.get(name);
}