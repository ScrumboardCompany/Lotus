#include "parser/expression/staticMethodExpression.h"
#include "structures/module.h"

using namespace lotus;

lotus::StaticMethodExpression::StaticMethodExpression(const String& staticName, const String& method, const std::vector<Expression>& args, const StringMap<Expression>& specifiedArgs)
	: staticName(staticName), method(method), args(args), specifiedArgs(specifiedArgs) {}

Value lotus::StaticMethodExpression::eval(Module& module) {
	std::vector<Value> values;
	StringMap<Value> specifiedValues;

	for (auto& arg : args) {
		values.push_back(arg->eval(module));
	}

	for (auto& arg : specifiedArgs) {
		specifiedValues.emplace(arg.first, arg.second->eval(module));
	}

	return module.STATIC_METHOD_WITH_SPECIFIED_ARGS(staticName, method, values, specifiedValues);
}
