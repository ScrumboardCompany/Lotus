#include "parser/parser.h"
#include "parser/statement/tryCatchStatement.h"

using namespace lotus;

Statement lotus::Parser::handleTryCatch() {
	Statement tryBlock = handleBlockStatement();

	consume(TokenType::CATCH);

	consume(TokenType::LPAREN);
	String name = consume(TokenType::WORD).text;
	consume(TokenType::RPAREN);

	Statement catchBlock = handleBlockStatement();

	return MAKE_PTR<TryCatchStatement>(tryBlock, name, catchBlock);
}