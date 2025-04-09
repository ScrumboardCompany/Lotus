#include "parser/statement/cppFunctionStatement.h"

using namespace lotus;

lotus::CppFunctionStatement::CppFunctionStatement(const ModuleBody_t& body)
	: body(body) {}

void lotus::CppFunctionStatement::execute(Module& module) {
	body(module);
}
