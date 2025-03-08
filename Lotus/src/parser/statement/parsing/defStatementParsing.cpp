#include "parser/parser.h"
#include "parser/statement/defStatement.h"

using namespace lotus;

Statement lotus::Parser::handleDefStatement() {
	String name = consume(TokenType::IDENTIFIER).text;

	std::vector<Argument> args = handleArgs();

	Statement body = handleBlockStatement();

	return MAKE_PTR<DefStatement>(name, Function(body, args));
}