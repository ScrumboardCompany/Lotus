#include "parser/statement/whileStatement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "structures/module.h"
#include "utils/utils.h"

using namespace lotus;

lotus::WhileStatement::WhileStatement(const std::vector<Expression>& conditionPart, const Statement& body)
	: conditionPart(conditionPart), body(body) {}

void lotus::WhileStatement::execute(Module& module) {
	module.variables.enterScope();

	while (callAllExpressionsAndReturnLastValue(conditionPart, module)->asBool(module)) {
		try {
			body->execute(module);
		}
		catch (const ContinueStatement&) {
			continue;
		}
		catch (const BreakStatement&) {
			break;
		}
	}

	module.variables.exitScope();
}