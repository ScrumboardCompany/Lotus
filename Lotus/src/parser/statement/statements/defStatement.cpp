#include "parser/statement/defStatement.h"
#include "utils/utils.h"
#include "structures/functions.h"
#include "parser/value/intValue.h"
#include "parser/parser.h"

using namespace lotus;

lotus::DefStatement::DefStatement(const String& name, Functions& functions, Variables& variables, const Statement& body) : name(name), functions(functions), variables(variables), body(body) {}

void lotus::DefStatement::execute() {

	Function function(body, &variables);

	functions.declare(name, function);

}