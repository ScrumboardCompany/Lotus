#include "parser/statement/forEachStatement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "utils/utils.h"
#include "structures/module.h"
#include "parser/value/intValue.h"

using namespace lotus;

lotus::ForEachStatement::ForEachStatement(const Expression& expression, const String& name, const Statement& body)
    : expression(expression), name(name), body(body) {}

void lotus::ForEachStatement::execute(Module& module) {
    module.variables.enterScope();

    module.variables.declare(name);

    expression->eval(module)->foreach(name, body, module);

    module.variables.exitScope();
}