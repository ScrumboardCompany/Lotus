#include "parser/function/function.h"
#include "utils/lotusTypes.h"
#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"
#include "parser/statement/cppFunctionStatement.h"
#include "parser/statement/returnStatement.h"
#include "parser/value/arrayValue.h"

using namespace lotus;

Function::Function(const Statement& body, const std::vector<Argument>& args) : body(body), args(args) {}

Function::Function(const Statement& body, const std::vector<const char*>& args, int) : body(body) {
	for (auto& arg : args) {
		std::string argInString = arg;

		bool isVariadic = !argInString.empty() && argInString.back() == '*';
		if (isVariadic) {
			argInString.pop_back();
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

Value Function::call(const std::vector<Value>& callArgs, Variables& variables) {
	if (!hasVariadic() && callArgs.size() != args.size()) {
		throw LotusException(STRING_LITERAL("Incorrect number of arguments"));
	}

	variables.enterScope();

	size_t fixedArgsCount = args.size();
	if (hasVariadic()) fixedArgsCount--;

	for (size_t i = 0; i < fixedArgsCount; i++) {
		variables.declare(args[i].name, callArgs[i]);
	}

	if (hasVariadic()) {
		std::vector<Value> variadicArgs(callArgs.begin() + fixedArgsCount, callArgs.end());
		variables.declare(args.back().name, MAKE_PTR<ArrayValue>(variadicArgs));
	}

	try {
		body->execute();

		variables.exitScope();
		return UNDEFINED();
	}
	catch (const Value& returnValue) {
		variables.exitScope();
		return returnValue;
	}
}
