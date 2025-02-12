#include "parser/statement/defStatement.h"
#include "utils/utils.h"
#include "structures/functions.h"
#include "parser/value/intValue.h"
#include "parser/parser.h"

using namespace lotus;

lotus::DefStatement::DefStatement(const String& name, Functions& functions, const Statement& body) : name(name), functions(functions), body(body) {}

void lotus::DefStatement::execute() {

	Function function(body);

	functions.declare(name, function);

}