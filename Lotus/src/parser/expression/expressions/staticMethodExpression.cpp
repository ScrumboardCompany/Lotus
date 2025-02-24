#include "parser/expression/staticMethodExpression.h"
#include "structures/module.h"

using namespace lotus;

lotus::StaticMethodExpression::StaticMethodExpression(const String& staticName, const String& method, const std::vector<Expression>& args)
	: staticName(staticName), method(method), args(args) {}

Value lotus::StaticMethodExpression::eval(Module& module) {
	std::vector<Value> values;

	for (auto& arg : args) {
		values.push_back(arg->eval(module));
	}

	return module.statics.get(staticName).callMethod(method, values, module);
}
