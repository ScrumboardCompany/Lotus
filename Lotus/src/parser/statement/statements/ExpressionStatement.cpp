#include "parser/statement/expressionStatement.h"

using namespace lotus;

lotus::ExpressionStatement::ExpressionStatement(Expression expression) : expression(expression) {}

void lotus::ExpressionStatement::execute() {
	expression->eval();
}