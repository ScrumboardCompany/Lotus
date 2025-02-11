#include "parser/statement/whileStatement.h"
#include "structures/variables.h"
#include "utils/utils.h"

using namespace lotus;

lotus::WhileStatement::WhileStatement(const std::vector<Expression>& conditionPart, const Statement& body, Variables& variables)
	: conditionPart(conditionPart), body(body), variables(variables) {}

void lotus::WhileStatement::execute() {
	variables.saveState();

	while (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {
		body->execute();
	}

	variables.restoreState();
}