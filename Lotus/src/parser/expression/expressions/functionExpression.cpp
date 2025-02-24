#include "parser/expression/functionExpression.h"
#include "parser/value/lambdaValue.h"
#include "structures/module.h"

using namespace lotus;

lotus::FunctionExpression::FunctionExpression(const String& name, const std::vector<Expression>& args)
	: name(name), args(args) {
}

Value lotus::FunctionExpression::eval(Module& module) {
	
	std::vector<Value> values;

	for (auto& arg : args) {
		values.push_back(arg->eval(module));
	}

	if (module.variables.isExists(name)) {
		if (auto lambda = std::dynamic_pointer_cast<LambdaValue>(module.variables.get(name))) {
			if(lambda->getArgsCount() == values.size()) return lambda->call(values, module);
		}
	}

	return module.functions.call(name, values, module);
}
