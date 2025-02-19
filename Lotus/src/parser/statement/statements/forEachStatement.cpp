#include "parser/statement/forEachStatement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "utils/utils.h"
#include "structures/variables.h"
#include "parser/value/intValue.h"

using namespace lotus;

lotus::ForEachStatement::ForEachStatement(const Expression& expression, const String& name, Variables& variables, const Statement& body) : expression(expression), name(name), variables(variables), body(body) {}

void lotus::ForEachStatement::execute() {
    variables.enterScope();

    variables.declare(name);

    Value evaled = expression->eval();

    for (int i = 0; i < evaled->size()->asInt(); i++) {
        variables.set(name, evaled->index(INT(i)));
		try {
			body->execute();
		}
		catch (const ContinueStatement&) {
			continue;
		}
		catch (const BreakStatement&) {
			break;
		}

		//evaled->index(INT(i)) = variables.get(name);
    }

    variables.exitScope();
}