#include "parser/parser.h"
#include "parser/function/function.h"
#include "structures/classStructures.h"

using namespace lotus;

std::pair<RawFields_t, Methods_t> lotus::Parser::handleFieldsMethods() {
	RawFields_t fields;
	Methods_t methods;

	consume(TokenType::LBRACE);

	AccessModifierType accessModifier = AccessModifierType::PRIVATE;

	while (!match(TokenType::RBRACE)) {

		if (match(TokenType::PUBLIC)) {
			accessModifier = AccessModifierType::PUBLIC;
			consume(TokenType::COLON);
		}
		if (match(TokenType::PRIVATE)) {
			accessModifier = AccessModifierType::PRIVATE;
			consume(TokenType::COLON);
		}

		if (match(TokenType::DEF)) {
			String methodName = consume(TokenType::WORD).text;

			std::vector<String> args = handleArgs();

			Statement body = handleBlockStatement();

			MethodMemberInfo memberInfo;
			memberInfo.value = Function(body, args);
			memberInfo.accessModifier = accessModifier;

			methods.emplace(methodName, memberInfo);
		}
		else {
			String fieldName = consume(TokenType::WORD).text;
			Expression fieldValue = nullptr;

			if (match(TokenType::EQUAL)) {
				fieldValue = expression();
			}

			while (match(TokenType::SEMICOLON));

			ClassMemberInfo memberInfo;
			memberInfo.accessModifier = accessModifier;

			fields.emplace(fieldName, std::make_pair(fieldValue, memberInfo));
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