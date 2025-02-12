#include "parser/expression/functionExpression.h"
#include "structures/variables.h"
#include "structures/functions.h"

using namespace lotus;

lotus::FunctionExpression::FunctionExpression(const String& name, Functions& functions, std::vector<Expression> args)
	: name(name), functions(functions), args(args) {
}

Value lotus::FunctionExpression::eval() {
	
	std::vector<Value> values;

	for (auto& arg : args)
	{
		values.push_back(arg->eval());
	}

	return functions.get(name).call(values);
}
