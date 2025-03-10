#include "parser/parser.h"
#include "parser/statement/enumStatement.h"

using namespace lotus;

Statement lotus::Parser::handleEnumStatement() {
	String name = consume(TokenType::IDENTIFIER).text;

	auto elements = handleObject();

	return MAKE_PTR<EnumStatement>(name, elements);
}