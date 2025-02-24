#include "parser/statement/cppFunctionStatement.h"

using namespace lotus;

lotus::CppFunctionStatement::CppFunctionStatement(const std::function<void()>& body)
	: body(body) {}

void lotus::CppFunctionStatement::execute(Module&) {
	body();
}
