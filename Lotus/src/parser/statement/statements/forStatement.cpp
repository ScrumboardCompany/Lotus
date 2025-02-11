#include "parser/statement/forStatement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "utils/utils.h"
#include "structures/variables.h"

using namespace lotus;

lotus::ForStatement::ForStatement(const std::vector<Expression>& declaringPart, const std::vector<Expression>& conditionPart, const std::vector<Expression>& actionPart, const Statement& body, Variables& variables)
: declaringPart(declaringPart), conditionPart(conditionPart), actionPart(actionPart), body(body), variables(variables) {}

void lotus::ForStatement::execute() {
    variables.saveState();

    for (auto& declare : declaringPart) declare->eval();

    auto performAction = [&]() {
        for (auto& action : actionPart) action->eval();
        };

    while (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {

        try {
            body->execute();
            performAction();
        } catch (const ContinueStatement&) {
            performAction();
            continue;
        } catch (const BreakStatement&) {
            break;
        }
    }

    variables.restoreState();
}