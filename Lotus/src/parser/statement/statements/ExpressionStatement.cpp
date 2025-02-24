#include "parser/statement/expressionStatement.h"

using namespace lotus;

lotus::ExpressionStatement::ExpressionStatement(const Expression& expression) : expression(expression) {}

void lotus::ExpressionStatement::execute(Module& module) {
	expression->eval(module);
}