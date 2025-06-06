#include "parser/function/function.h"
#include "utils/lotusTypes.h"
#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"
#include "parser/statement/cppFunctionStatement.h"
#include "parser/statement/returnStatement.h"
#include "parser/value/arrayValue.h"
#include "structures/module.h"
#include "algorithm"

using namespace lotus;

Function::Function(const Statement& body, const std::vector<Argument>& args) : body(body), args(args) {}

Function::Function(const Statement& body, const std::vector<const char*>& args, int) : body(body) {
	for (auto& arg : args) {
		std::string argInString = arg;

		bool isVariadic = argInString.size() >= 3 && argInString.substr(argInString.size() - 3) == "...";
		if (isVariadic) {
			argInString.erase(argInString.size() - 3);
		}

		this->args.emplace_back(STRING_VAR_LITERAL(argInString.c_str()), isVariadic);
	}
}

bool Function::hasVariadic() const {
	return !args.empty() && args.back().isVariadic;
}

size_t Function::getArgsCount() const {
	return args.size();
}

Value Function::call(const std::vector<Value>& callArgs, Module& module) {
	if (!hasVariadic() && callArgs.size() != args.size()) {
		throw LotusException(STRING_LITERAL("Incorrect number of arguments"));
	}

	module.variables.enterScope();

	size_t fixedArgsCount = args.size();
	if (hasVariadic()) fixedArgsCount--;

	for (size_t i = 0; i < fixedArgsCount; i++) {
		module.variables.declare(args[i].name, callArgs[i]);
	}

	if (hasVariadic()) {
		std::vector<Value> variadicArgs(callArgs.begin() + fixedArgsCount, callArgs.end());
		module.variables.declare(args.back().name, ARRAY(variadicArgs));
	}

	try {
		body->execute(module);

		module.variables.exitScope();
		return UNDEFINED();
	}
	catch (const Value& returnValue) {
		module.variables.exitScope();
		return returnValue;
	}
}

Value lotus::Function::call(const std::vector<Value>& callArgs, const StringMap<Value>& specifiedArgs, Module& module) {
	if (!hasVariadic() && (callArgs.size() + specifiedArgs.size()) != args.size()) {
		throw LotusException(STRING_LITERAL("Incorrect number of arguments"));
	}

	std::vector<Argument> filteredArgs = args;
	for (auto& arg : specifiedArgs) {
		filteredArgs.erase(std::remove_if(filteredArgs.begin(), filteredArgs.end(), [&](const Argument& el) {
			return el.name == arg.first;
			}), filteredArgs.end());
	}

	module.variables.enterScope();

	size_t fixedArgsCount = filteredArgs.size();
	if (hasVariadic()) fixedArgsCount--;

	for (size_t i = 0; i < fixedArgsCount; i++) {
		module.variables.declare(filteredArgs[i].name, callArgs[i]);
	}

	for (auto& arg : specifiedArgs) {
		module.variables.declare(arg.first, arg.second);
	}

	if (hasVariadic()) {
		std::vector<Value> variadicArgs(callArgs.begin() + fixedArgsCount, callArgs.end());
		module.variables.declare(filteredArgs.back().name, ARRAY(variadicArgs));
	}

	try {
		body->execute(module);

		module.variables.exitScope();
		return UNDEFINED();
	}
	catch (const Value& returnValue) {
		module.variables.exitScope();
		return returnValue;
	}
}
