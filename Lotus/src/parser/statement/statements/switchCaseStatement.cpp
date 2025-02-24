#include "parser/statement/switchCaseStatement.h"
#include "parser/statement/breakStatement.h"
#include "structures/module.h"

using namespace lotus;

lotus::SwitchCaseStatement::SwitchCaseStatement(const Expression& exprToCheck, const std::vector<std::pair<Expression, Statement>>& cases, const Statement& defaultBody)
	: exprToCheck(exprToCheck), cases(cases), defaultBody(defaultBody) {}

void lotus::SwitchCaseStatement::execute(Module& module) {
    Value valueToCheck = exprToCheck->eval(module);
    bool caseMatched = false;

    for (auto& Case : cases) {
        if (caseMatched || valueToCheck->equality(Case.first->eval(module), module)->asBool(module)) {
            caseMatched = true;
            module.variables.enterScope();

            try {
                Case.second->execute(module);
                module.variables.exitScope();
            }
            catch (const BreakStatement&) {
                module.variables.exitScope();
                return;
            }
        }
    }

    if (!caseMatched && defaultBody) {
        module.variables.enterScope();
        defaultBody->execute(module);
        module.variables.exitScope();
    }
}