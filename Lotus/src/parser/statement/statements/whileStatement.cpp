#include "parser/statement/whileStatement.h"
#include "structures/variables.h"

using namespace lotus;

lotus::WhileStatement::WhileStatement(Expression condition, Statement body) : condition(condition), body(body) {}

void lotus::WhileStatement::execute() {
	while (condition->eval()->asInt()) {
		body->execute();
	}
}