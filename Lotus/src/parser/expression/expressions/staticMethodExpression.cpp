#include "parser/expression/staticMethodExpression.h"
#include "structures/variables.h"
#include "structures/statics.h"

using namespace lotus;

lotus::StaticMethodExpression::StaticMethodExpression(const String& staticName, const String& method, const std::vector<Expression>& args, Variables& variables, Statics& statics)
	: staticName(staticName), method(method), args(args), variables(variables), statics(statics) {}

Value lotus::StaticMethodExpression::eval() {
	std::vector<Value> values;

	for (auto& arg : args) {
		values.push_back(arg->eval());
	}

	return statics.get(staticName).callMethod(method, values, variables);
}
