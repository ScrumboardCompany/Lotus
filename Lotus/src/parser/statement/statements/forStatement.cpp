#include "parser/statement/forStatement.h"
#include "utils/utils.h"
#include "structures/variables.h"

using namespace lotus;

lotus::ForStatement::ForStatement(std::vector<Expression> declaringPart, std::vector<Expression> conditionPart, std::vector<Expression> actionPart, Statement body, Variables& variables)
	: declaringPart(declaringPart), conditionPart(conditionPart), actionPart(actionPart), body(body), variables(variables) {}

void lotus::ForStatement::execute() {
    variables.saveState();

    for (auto& declare : declaringPart) declare->eval();

    while (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {
        body->execute();
        for (auto& action : actionPart) action->eval();
    }

    variables.restoreState();
}