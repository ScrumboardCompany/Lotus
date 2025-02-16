#include "parser/statement/switchCaseStatement.h"
#include "parser/statement/breakStatement.h"
#include "structures/variables.h"

using namespace lotus;

lotus::SwitchCaseStatement::SwitchCaseStatement(const Expression& exprToCheck, const std::vector<std::pair<Expression, Statement>>& cases, const Statement& defaultBody, Variables& variables)
	: exprToCheck(exprToCheck), cases(cases), defaultBody(defaultBody), variables(variables) {}

void lotus::SwitchCaseStatement::execute() {
    Value valueToCheck = exprToCheck->eval();
    bool caseMatched = false;

    for (auto& Case : cases) {
        if (caseMatched || valueToCheck->equality(Case.first->eval())->asBool()) {
            caseMatched = true;
            variables.saveState();

            try {
                Case.second->execute();
                variables.restoreState();
            }
            catch (const BreakStatement&) {
                variables.restoreState();
                return;
            }
        }
    }

    if (!caseMatched && defaultBody) {
        variables.saveState();
        defaultBody->execute();
        variables.restoreState();
    }
}