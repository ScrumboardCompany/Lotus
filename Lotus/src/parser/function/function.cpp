#include "parser/function/function.h"
#include "utils/lotusTypes.h"
#include "parser/value/undefinedValue.h"

using namespace lotus;

Function::Function(const Statement& body, Variables* variables) : body(body), variables(variables) {}

Value Function::call() {
	variables->saveState();

	try {
		body->execute();
		variables->restoreState();
		return UNDEFINED();
	}
	catch (const Expression& returnValue) {
		variables->restoreState();
		return returnValue->eval();
	}

}
