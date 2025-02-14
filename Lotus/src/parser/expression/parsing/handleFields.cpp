#include "parser/parser.h"

using namespace lotus;

StringMap<Expression> lotus::Parser::handleFields() {
	StringMap<Expression> fields;

	consume(TokenType::LBRACE);

	while (!match(TokenType::RBRACE)) {
		String fieldName = consume(TokenType::WORD).text;
		Expression fieldValue = nullptr;

		if (match(TokenType::EQUAL)) {
			fieldValue = expression();
		}

		while (match(TokenType::SEMICOLON));

		fields.emplace(fieldName, fieldValue);
	}

	return fields;
}