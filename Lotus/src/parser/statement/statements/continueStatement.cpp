#include "parser/statement/continueStatement.h"
#include <iostream>

using namespace lotus;

lotus::ContinueStatement::ContinueStatement() {}

void lotus::ContinueStatement::execute(Module&) {
	throw *this;
}