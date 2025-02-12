#include "parser/function/function.h"
#include "utils/lotusTypes.h"
#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"

using namespace lotus;

Function::Function(const Statement& body, Variables* variables, const std::vector<String>& args) : body(body), variables(variables), args(args) {}

Value Function::call(const std::vector<Value>& args) {
	if (args.size() != this->args.size()) {
		throw LotusException(STRING_LITERAL("Incorrect number of arguments"));
	}

	variables->saveState();

	for (size_t i = 0; i < args.size(); i++) {
		variables->declare(this->args[i], args[i]);
	}

	try {
		body->execute();
		variables->restoreState();
		return UNDEFINED();
	}
	catch (const Value& returnValue) {
		variables->restoreState();
		return returnValue;
	}

}
