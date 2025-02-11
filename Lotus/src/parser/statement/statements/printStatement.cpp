#include "parser/statement/printStatement.h"
#include <iostream>

using namespace lotus;

lotus::PrintStatement::PrintStatement(const Expression& arg) : arg(arg) {}

void lotus::PrintStatement::execute() {
	std::wcout << arg->eval()->asString();
}