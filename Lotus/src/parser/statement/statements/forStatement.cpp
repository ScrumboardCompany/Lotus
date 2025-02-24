#include "parser/statement/forStatement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "utils/utils.h"
#include "structures/module.h"

using namespace lotus;

lotus::ForStatement::ForStatement(const std::vector<Expression>& declaringPart, const std::vector<Expression>& conditionPart, const std::vector<Expression>& actionPart, const Statement& body)
    : declaringPart(declaringPart), conditionPart(conditionPart), actionPart(actionPart), body(body) {}

void lotus::ForStatement::execute(Module& module) {
    module.variables.enterScope();

    for (auto& declare : declaringPart) declare->eval(module);

    auto performAction = [&]() {
        for (auto& action : actionPart) action->eval(module);
        };

    while (callAllExpressionsAndReturnLastValue(conditionPart, module)->asBool(module)) {

        try {
            body->execute(module);
            performAction();
        }
        catch (const ContinueStatement&) {
            performAction();
            continue;
        }
        catch (const BreakStatement&) {
            break;
        }
    }

    module.variables.exitScope();
}