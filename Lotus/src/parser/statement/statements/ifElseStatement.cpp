#include "parser/statement/ifElseStatement.h"
#include "utils/utils.h"
#include "structures/module.h"

using namespace lotus;

lotus::IfElseStatement::IfElseStatement(const std::vector<Expression>& conditionPart, const Statement& ifBody, const Statement& elseBody)
	: conditionPart(conditionPart), ifBody(ifBody), elseBody(elseBody) {}

void lotus::IfElseStatement::execute(Module& module) {
	module.variables.enterScope();

	if (callAllExpressionsAndReturnLastValue(conditionPart, module)->asBool(module)) {
		ifBody->execute(module);
	}
	else if (elseBody) {
		elseBody->execute(module);
	}

	module.variables.exitScope();
}
