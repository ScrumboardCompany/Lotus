#include "parser/expression/functionExpression.h"
#include "parser/value/lambdaValue.h"
#include "structures/module.h" 
#include "utils/lotusError.h"

using namespace lotus;

lotus::FunctionExpression::FunctionExpression(const String& name, const std::vector<Expression>& args, const StringMap<Expression>& specifiedArgs)
	: name(name), args(args), specifiedArgs(specifiedArgs) {
}

Value lotus::FunctionExpression::eval(Module& module) {
	
	std::vector<Value> values;
	StringMap<Value> specifiedValues;

	for (auto& arg : args) {
		values.push_back(arg->eval(module));
	}

	for (auto& arg : specifiedArgs) {
		specifiedValues.emplace(arg.first, arg.second->eval(module));
	}

	if (module.variables.isExists(name)) {
		if (auto lambda = std::dynamic_pointer_cast<LambdaValue>(module.variables.get(name))) {
			Ptr<Function> variadic = nullptr;

			size_t argsCount = values.size() + specifiedValues.size();
			if (lambda->function.hasVariadic() && argsCount >= lambda->function.getArgsCount() - 1) variadic = MAKE_PTR<Function>(lambda->function);
			if (lambda->function.getArgsCount() == argsCount) return lambda->function.call(values, specifiedValues, module);

			if (variadic) {
				return variadic->call(values, specifiedValues, module);
			}
		}
	}

	if (specifiedValues.empty()) {
		return module.functions.call(name, values, module);
	}

	return module.functions.call(name, values, specifiedValues, module);
}
