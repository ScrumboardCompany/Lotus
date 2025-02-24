#include "parser/expression/methodExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::MethodExpression::MethodExpression(const Expression& expr, const String& method, const std::vector<Expression>& args)
	: expr(expr), method(method), args(args) {}

Value lotus::MethodExpression::eval(Module& module) {

	std::vector<Value> values;

	for (auto& arg : args) {
		values.push_back(arg->eval(module));
	}

	return expr->eval(module)->callMethod(method, values, module);
}
