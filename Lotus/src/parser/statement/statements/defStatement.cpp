#include "parser/statement/defStatement.h"
#include "utils/utils.h"
#include "structures/functions.h"
#include "parser/value/intValue.h"
#include "parser/parser.h"

using namespace lotus;

lotus::DefStatement::DefStatement(const String& name, Functions& functions, Variables& variables, const Function& function)
	: name(name), functions(functions), variables(variables), function(function) {}

void lotus::DefStatement::execute() {
	functions.declare(name, function);
}