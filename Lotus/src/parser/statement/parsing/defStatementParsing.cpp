#include "parser/parser.h"
#include "parser/statement/defStatement.h"

using namespace lotus;

Statement lotus::Parser::handleDefStatement() {
	String name = consume(TokenType::WORD).text;

	std::vector<Argument> args = handleArgs();

	Statement body = handleBlockStatement();

	return MAKE_PTR<DefStatement>(name, module.functions, Function(body, args));
}