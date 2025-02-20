#include "parser/expression/functionExpression.h"
#include "parser/value/lambdaValue.h"
#include "structures/variables.h"
#include "structures/functions.h"

using namespace lotus;

lotus::FunctionExpression::FunctionExpression(const String& name, Functions& functions, Variables& variables, const std::vector<Expression>& args)
	: name(name), functions(functions), variables(variables), args(args) {
}

Value lotus::FunctionExpression::eval() {
	
	std::vector<Value> values;

	for (auto& arg : args) {
		values.push_back(arg->eval());
	}

	if (variables.isExists(name)) {
		if (auto lambda = std::dynamic_pointer_cast<LambdaValue>(variables.get(name))) {
			if(lambda->getArgsCount() == values.size()) return lambda->call(values, variables);
		}
	}

	return functions.call(name, values, variables);
}
