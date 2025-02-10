#include "parser/statement/forStatement.h"
#include "utils/utils.h"

using namespace lotus;

lotus::ForStatement::ForStatement(std::vector<Expression> declaringPart, std::vector<Expression> conditionPart, std::vector<Expression> actionPart, Statement body) 
	: declaringPart(declaringPart), conditionPart(conditionPart), actionPart(actionPart), body(body) {}

void lotus::ForStatement::execute() {
    for (auto& declare : declaringPart) declare->eval();

    while (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {
        body->execute();
        for (auto& action : actionPart) action->eval();
    }
}