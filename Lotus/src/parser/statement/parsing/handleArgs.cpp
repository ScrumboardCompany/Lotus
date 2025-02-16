#include "parser/parser.h"

using namespace lotus;

std::vector<String> lotus::Parser::handleArgs() {
	std::vector<String> args;

	consume(TokenType::LPAREN);

	if (!match(TokenType::RPAREN)) {

		while (true) {
			args.push_back(consume(TokenType::WORD).text);

			if (!match(TokenType::COMMA)) {
				break;
			}
		}

		consume(TokenType::RPAREN);
	}

	return args;
}