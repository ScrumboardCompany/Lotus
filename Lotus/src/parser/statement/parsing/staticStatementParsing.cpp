#include "parser/parser.h"
#include "parser/statement/staticStatement.h"

using namespace lotus;

Statement lotus::Parser::handleStaticStatement() {
	String name = consume(TokenType::IDENTIFIER).text;

	auto staticInfo = handleFieldsMethods();

	return MAKE_PTR<StaticStatement>(name, staticInfo.first, staticInfo.second);
}