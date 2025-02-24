#include "parser/statement/defStatement.h"
#include "utils/utils.h"
#include "structures/module.h"
#include "parser/value/intValue.h"
#include "parser/parser.h"

using namespace lotus;

lotus::DefStatement::DefStatement(const String& name, const Function& function)
	: name(name), function(function) {}

void lotus::DefStatement::execute(Module& module) {
	module.functions.declare(name, function);
}