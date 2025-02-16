#include "parser/parser.h"
#include "parser/statement/defStatement.h"

using namespace lotus;

Statement lotus::Parser::handleDefStatement() {
	String name = consume(TokenType::WORD).text;

	std::vector<String> args = handleArgs();

	Statement body = handleBlockStatement();

	return MAKE_PTR<DefStatement>(name, module.functions, module.variables, Function(body, args));
}