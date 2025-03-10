#include "parser/expression/callLambdaExpression.h"
#include "parser/expression/wordExpression.h"
#include "parser/value/lambdaValue.h"
#include "structures/module.h"
#include "utils/lotusError.h"

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

	if (auto word = std::dynamic_pointer_cast<WordExpression>(function)) {

		if (module.functions.isExists(word->name)) {
			if (specifiedValues.empty()) {
				return module.functions.call(word->name, values, module);
			}

			return module.functions.call(word->name, values, specifiedValues, module);
		}
		else if (module.variables.isExists(word->name)) {
			if (auto lambda = std::dynamic_pointer_cast<LambdaValue>(module.variables.get(word->name))) {
				Ptr<Function> variadic = nullptr;

				size_t argsCount = values.size() + specifiedValues.size();
				if (lambda->function.hasVariadic() && argsCount >= lambda->function.getArgsCount() - 1) variadic = MAKE_PTR<Function>(lambda->function);
				if (lambda->function.getArgsCount() == argsCount) return lambda->function.call(values, specifiedValues, module);

				if (variadic) {
					return variadic->call(values, specifiedValues, module);
				}
			}
		}
		else {
			throw LotusException(STRING_LITERAL("Function or variable \"") + word->name + STRING_LITERAL("\" is not found"));
		}
	}

	if (specifiedValues.empty()) {
		return function->eval(module)->call(values, module);
	}

	return function->eval(module)->call(values, module, specifiedValues);
}
