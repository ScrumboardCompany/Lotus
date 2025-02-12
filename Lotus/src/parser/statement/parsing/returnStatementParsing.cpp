#include "parser/parser.h"
#include "parser/statement/returnStatement.h"

using namespace lotus;

Statement lotus::Parser::handleReturnStatement() {
	Expression expr = expression();

	return MAKE_PTR<ReturnStatement>(expr);
}