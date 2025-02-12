#include "parser/expression/functionExpression.h"
#include "structures/variables.h"
#include "structures/functions.h"

using namespace lotus;

lotus::FunctionExpression::FunctionExpression(const String& name, Functions& functions)
	: name(name), functions(functions) {
}

Value lotus::FunctionExpression::eval() {
	
	return functions.get(name).call();
}
