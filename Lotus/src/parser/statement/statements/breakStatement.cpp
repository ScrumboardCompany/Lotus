#include "parser/statement/breakStatement.h"
#include <iostream>

using namespace lotus;

lotus::BreakStatement::BreakStatement() {}

void lotus::BreakStatement::execute(Module&) {
	throw *this;
}