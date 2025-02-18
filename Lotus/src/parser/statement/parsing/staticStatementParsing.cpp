#include "parser/parser.h"
#include "parser/statement/staticStatement.h"

using namespace lotus;

Statement lotus::Parser::handleStaticStatement() {
	String name = consume(TokenType::WORD).text;

	auto staticInfo = handleFieldsMethods();

	return MAKE_PTR<StaticStatement>(module.statics, name, staticInfo.first, staticInfo.second);
}