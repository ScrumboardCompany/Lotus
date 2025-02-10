#include "parser/statement/ifElseStatement.h"
#include "structures/variables.h"
#include "utils/utils.h"

using namespace lotus;

lotus::IfElseStatement::IfElseStatement(std::vector<Expression> conditionPart, Statement ifBody, Statement elseBody)
	: conditionPart(conditionPart), ifBody(ifBody), elseBody(elseBody) {}

void lotus::IfElseStatement::execute() {
	if (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {
		ifBody->execute();
	} else if (elseBody) {
		elseBody->execute();
	}
}