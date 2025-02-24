#include "parser/expression/methodExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::MethodExpression::MethodExpression(const Expression& expr, const String& method, const std::vector<Expression>& args, const StringMap<Expression>& specifiedArgs)
	: expr(expr), method(method), args(args), specifiedArgs(specifiedArgs) {}

Value lotus::MethodExpression::eval(Module& module) {

	std::vector<Value> values;
	StringMap<Value> specifiedValues;

	for (auto& arg : args) {
		values.push_back(arg->eval(module));
	}

	for (auto& arg : specifiedArgs) {
		specifiedValues.emplace(arg.first, arg.second->eval(module));
	}

	if (specifiedValues.empty()) {
		return expr->eval(module)->callMethod(method, values, module);
	}

	return expr->eval(module)->callMethod(method, values, module, specifiedValues);
}
