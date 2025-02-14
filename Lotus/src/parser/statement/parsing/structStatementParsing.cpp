#include "parser/parser.h"
#include "parser/statement/structStatement.h"

using namespace lotus;

Statement lotus::Parser::handleStructStatement() {
	String name = consume(TokenType::WORD).text;
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

	return MAKE_PTR<StructStatement>(module.functions, name, fields);
}