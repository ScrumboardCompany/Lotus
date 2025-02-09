#include "parser/parser.h"
#include "parser/statement/printStatement.h"

using namespace lotus;

Statement lotus::Parser::handlePrintStatement() {
	Expression expr = expression();
	return MAKE_PTR<PrintStatement>(expr);
}