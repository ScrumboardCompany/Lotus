#include "parser/parser.h"
#include "parser/statement/structStatement.h"

using namespace lotus;

Statement lotus::Parser::handleStructStatement() {
	String name = consume(TokenType::WORD).text;

	return MAKE_PTR<StructStatement>(module.functions, name, handleFields());
}