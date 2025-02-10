#include "parser/statement/whileStatement.h"
#include "structures/variables.h"
#include "utils/utils.h"

using namespace lotus;

lotus::WhileStatement::WhileStatement(std::vector<Expression> conditionPart, Statement body)
	: conditionPart(conditionPart), body(body) {}

void lotus::WhileStatement::execute() {
	while (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {
		body->execute();
	}
}