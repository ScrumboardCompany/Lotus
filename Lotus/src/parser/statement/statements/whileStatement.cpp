#include "parser/statement/whileStatement.h"
#include "structures/variables.h"
#include "utils/utils.h"

using namespace lotus;

lotus::WhileStatement::WhileStatement(std::vector<Expression> conditionPart, Statement body, Variables& variables)
	: conditionPart(conditionPart), body(body), variables(variables) {}

void lotus::WhileStatement::execute() {
	variables.saveState();

	while (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {
		body->execute();
	}

	variables.restoreState();
}