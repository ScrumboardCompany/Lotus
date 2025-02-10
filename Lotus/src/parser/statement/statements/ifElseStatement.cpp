#include "parser/statement/ifElseStatement.h"
#include "structures/variables.h"

using namespace lotus;

lotus::IfElseStatement::IfElseStatement(Expression condition, Statement ifBody, Statement elseBody) : condition(condition), ifBody(ifBody), elseBody(elseBody) {}

void lotus::IfElseStatement::execute() {
	if (condition->eval()->asInt()) {
		ifBody->execute();
	} else if (elseBody) {
		elseBody->execute();
	}
}