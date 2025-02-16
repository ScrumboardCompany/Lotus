#include "parser/parser.h"
#include "parser/function/function.h"

using namespace lotus;

std::pair<StringMap<Expression>, StringMap<Function>> lotus::Parser::handleFieldsMethods() {
	StringMap<Expression> fields;
	StringMap<Function> methods;

	consume(TokenType::LBRACE);

	while (!match(TokenType::RBRACE)) {
		if (match(TokenType::DEF)) {
			String methodName = consume(TokenType::WORD).text;

			std::vector<String> args = handleArgs();

			Statement body = handleBlockStatement();

			methods.emplace(methodName, Function(body, args));
		}
		else {
			String fieldName = consume(TokenType::WORD).text;
			Expression fieldValue = nullptr;

			if (match(TokenType::EQUAL)) {
				fieldValue = expression();
			}

			while (match(TokenType::SEMICOLON));

			fields.emplace(fieldName, fieldValue);
		}
	}

	return std::make_pair(fields, methods);
}

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