#include "parser/statement/letStatement.h"
#include "structures/variables.h"

using namespace lotus;

lotus::LetStatement::LetStatement(const String& name, Expression expression, Variables& variables) : name(name), expression(expression), variables(variables) {}

void lotus::LetStatement::execute() {
	if (expression) {
		variables.declare(name, expression->eval());
	}
	else {
		variables.declare(name);
	}
}