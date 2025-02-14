#include "parser/statement/defStatement.h"
#include "utils/utils.h"
#include "structures/functions.h"
#include "parser/value/intValue.h"
#include "parser/parser.h"

using namespace lotus;

lotus::DefStatement::DefStatement(const String& name, Functions& functions, Variables& variables, const Statement& body, std::vector<String> args) 
	: name(name), functions(functions), variables(variables), body(body), args(args) {}

void lotus::DefStatement::execute() {

	Function function(body, args);

	functions.declare(name, function);

}