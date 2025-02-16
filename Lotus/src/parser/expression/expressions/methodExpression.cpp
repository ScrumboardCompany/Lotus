#include "parser/expression/methodExpression.h"

using namespace lotus;

lotus::MethodExpression::MethodExpression(const Expression& expr, const String& method, const std::vector<Expression>& args, Variables& variables)
	: expr(expr), method(method), args(args), variables(variables) {}

Value lotus::MethodExpression::eval() {

	std::vector<Value> values;

	for (auto& arg : args) {
		values.push_back(arg->eval());
	}

	return expr->eval()->callMethod(method, values, variables);
}
