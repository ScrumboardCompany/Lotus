#include "parser/statement/setStatement.h"
#include "structures/variables.h"

using namespace lotus;

lotus::SetStatement::SetStatement(const String& name, Expression expression, Variables& variables) : name(name), expression(expression), variables(variables) {}

void lotus::SetStatement::execute() {
	variables.set(name, expression->eval());
}