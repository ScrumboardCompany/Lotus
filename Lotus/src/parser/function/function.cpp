#include "parser/function/function.h"
#include "utils/lotusTypes.h"
#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"
#include "parser/statement/cppFunctionStatement.h"
#include "parser/statement/returnStatement.h"

using namespace lotus;

Function::Function(const Statement& body, const std::vector<String>& args) : body(body), args(args) {}

Function::Function(const Statement& body, const std::vector<const char*>& args, int) : body(body) {
	for (auto& arg : args) {
		this->args.push_back(STRING_VAR_LITERAL(arg));
	}
}

Value Function::call(const std::vector<Value>& args, Variables& variables) {
	if (args.size() != this->args.size()) {
		throw LotusException(STRING_LITERAL("Incorrect number of arguments"));
	}

	variables.saveState();

	for (size_t i = 0; i < args.size(); i++) {
		variables.declare(this->args[i], args[i]);
	}

	try {
		body->execute();

		variables.restoreState();
		return UNDEFINED();
	}
	catch (const Value& returnValue) {
		variables.restoreState();
		return returnValue;
	}

}

size_t lotus::Function::getArgsCount() const {
	return args.size();
}
