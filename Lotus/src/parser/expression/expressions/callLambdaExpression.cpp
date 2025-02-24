#include "parser/expression/callLambdaExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::CallLambdaExpression::CallLambdaExpression(const std::vector<Expression>& args, const Expression& function)
	: args(args), function(function) {
}

Value lotus::CallLambdaExpression::eval(Module& module) {

	std::vector<Value> values;

	for (auto& arg : args) {
		values.push_back(arg->eval(module));
	}

	return function->eval(module)->call(values, module);
}
