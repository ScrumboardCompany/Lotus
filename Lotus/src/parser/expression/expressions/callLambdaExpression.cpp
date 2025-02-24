#include "parser/expression/callLambdaExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::CallLambdaExpression::CallLambdaExpression(const std::vector<Expression>& args, const StringMap<Expression>& specifiedArgs, const Expression& function)
	: args(args), specifiedArgs(specifiedArgs), function(function) {
}

Value lotus::CallLambdaExpression::eval(Module& module) {

	std::vector<Value> values;
	StringMap<Value> specifiedValues;

	for (auto& arg : args) {
		values.push_back(arg->eval(module));
	}

	for (auto& arg : specifiedArgs) {
		specifiedValues.emplace(arg.first, arg.second->eval(module));
	}

	if (specifiedValues.empty()) {
		return function->eval(module)->call(values, module);
	}

	return function->eval(module)->call(values, module, specifiedValues);
}
