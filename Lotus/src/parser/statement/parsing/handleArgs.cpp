#include "parser/parser.h"
#include "structures/argument.h"
#include "utils/lotusError.h"

using namespace lotus;

std::vector<Argument> lotus::Parser::handleArgs() {
	std::vector<Argument> args;

	consume(TokenType::LPAREN);

	if (!match(TokenType::RPAREN)) {

		while (true) {
			Token name = consume(TokenType::IDENTIFIER);

			for (auto& arg : args) {
				if (name.text == arg.name) throw LotusException(STRING_LITERAL("Cannot have two arguments with same name \"") + name.text + STRING_LITERAL("\""), name.line);
			}

			args.push_back(name.text);

			if (match(TokenType::DOTDOTDOT)) args.back().isVariadic = true;

			if (!match(TokenType::COMMA)) {
				break;
			}
		}

		consume(TokenType::RPAREN);
	}

	bool hasVariadic = false;
	for (size_t i = 0; i < args.size(); i++) {

		if (args[i].isVariadic) {
			if (hasVariadic) {
				throw LotusException(STRING_LITERAL("Cannot have more one variadic argument"), get(0).line);
			}
			else hasVariadic = true;
		}
	}
	if (hasVariadic && !args.back().isVariadic) {
		throw LotusException(STRING_LITERAL("Variadic argument should be the last one"), get(0).line);
	}

	return args;
}