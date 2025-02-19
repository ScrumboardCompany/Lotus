#include "parser/statement/whileStatement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "structures/variables.h"
#include "utils/utils.h"

using namespace lotus;

lotus::WhileStatement::WhileStatement(const std::vector<Expression>& conditionPart, const Statement& body, Variables& variables)
	: conditionPart(conditionPart), body(body), variables(variables) {}

void lotus::WhileStatement::execute() {
	variables.enterScope();

	while (callAllExpressionsAndReturnLastValue(conditionPart)->asBool()) {
		try {
			body->execute();
		}
		catch (const ContinueStatement&) {
			continue;
		}
		catch (const BreakStatement&) {
			break;
		}
	}

	variables.exitScope();
}