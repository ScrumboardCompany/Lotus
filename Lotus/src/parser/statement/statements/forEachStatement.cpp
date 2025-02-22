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

    expression->eval()->foreach(name, body, variables);

    variables.exitScope();
}