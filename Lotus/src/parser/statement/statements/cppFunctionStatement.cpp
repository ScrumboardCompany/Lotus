#include "parser/statement/cppFunctionStatement.h"

using namespace lotus;

lotus::CppFunctionStatement::CppFunctionStatement(const std::function<void(Variables&)>& body)
	: body(body), variables(variables) {}

void lotus::CppFunctionStatement::setVariables(Variables& variables) {
	this->variables = MAKE_PTR<Variables>(variables);
}

void lotus::CppFunctionStatement::execute() {
	if (variables) {
		body(*variables);
	}
}
