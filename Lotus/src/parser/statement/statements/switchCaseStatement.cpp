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
            variables.enterScope();

            try {
                Case.second->execute();
                variables.exitScope();
            }
            catch (const BreakStatement&) {
                variables.exitScope();
                return;
            }
        }
    }

    if (!caseMatched && defaultBody) {
        variables.enterScope();
        defaultBody->execute();
        variables.exitScope();
    }
}