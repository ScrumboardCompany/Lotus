#include "parser/parser.h"
#include "parser/statement/continueStatement.h"

using namespace lotus;

Statement lotus::Parser::handleContinueStatement() {
	return MAKE_PTR<ContinueStatement>();
}