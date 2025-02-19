#include "parser/statement/ifElseStatement.h"
#include "utils/utils.h"
#include "structures/variables.h"

using namespace lotus;

lotus::IfElseStatement::IfElseStatement(const std::vector<Expression>& conditionPart, const Statement& ifBody, const Statement& elseBody, Variables& variables)
	: conditionPart(conditionPart), ifBody(ifBody), elseBody(elseBody), variables(variables) {}

void lotus::IfElseStatement::execute() {
	variables.enterScope();

	if (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {
		ifBody->execute();
	} else if (elseBody) {
		elseBody->execute();
	}

	variables.exitScope();
}