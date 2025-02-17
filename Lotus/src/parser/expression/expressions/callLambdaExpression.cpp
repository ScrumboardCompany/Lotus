#include "parser/expression/callLambdaExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::CallLambdaExpression::CallLambdaExpression(Variables& variables, const std::vector<Expression>& args, const Expression& function)
	: variables(variables), args(args), function(function) {
}

Value lotus::CallLambdaExpression::eval() {

	std::vector<Value> values;

	for (auto& arg : args) {
		values.push_back(arg->eval());
	}

	return function->eval()->call(values, variables);
}
