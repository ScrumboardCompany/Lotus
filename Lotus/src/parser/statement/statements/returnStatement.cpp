#include "parser/statement/returnStatement.h"
#include <iostream>

using namespace lotus;

lotus::ReturnStatement::ReturnStatement(const Expression& expr) : expr(expr) {}

void lotus::ReturnStatement::execute() {
	throw expr->eval();
}