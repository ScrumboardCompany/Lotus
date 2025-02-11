#include "parser/parser.h"
#include "parser/statement/breakStatement.h"

using namespace lotus;

Statement lotus::Parser::handleBreakStatement() {
	return MAKE_PTR<BreakStatement>();
}