#include "parser/parser.h"
#include "parser/statement/defStatement.h"

using namespace lotus;

Statement lotus::Parser::handleDefStatement() {
	String name = consume(TokenType::WORD).text;

	consume(TokenType::LPAREN);

	std::vector<String> args;

	while (true) {
		args.push_back(consume(TokenType::WORD).text);

		if (!match(TokenType::COMMA)) {
			break;
		}
	}

	consume(TokenType::RPAREN);

	Statement body = handleBlockStatement();

	return MAKE_PTR<DefStatement>(name, module.functions, module.variables, body, args);
}