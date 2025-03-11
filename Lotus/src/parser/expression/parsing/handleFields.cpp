#include "parser/parser.h"
#include "parser/function/function.h"
#include "structures/classStructures.h"
#include "utils/lotusError.h"
#include "parser/expression/undefinedExpression.h"

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
		if (match(TokenType::PROTECTED)) {
			accessModifier = AccessModifierType::PROTECTED;
			consume(TokenType::COLON);
		}

		if (match(TokenType::DEF)) {
			Token methodName = consume(TokenType::IDENTIFIER);

			std::vector<Argument> args = handleArgs();

			Statement body = handleBlockStatement();

			MethodMemberInfo memberInfo;
			memberInfo.value = Function(body, args);
			memberInfo.accessModifier = accessModifier;

			if (methods.find(methodName.text) != methods.end()) {
				for (auto& method : methods[methodName.text]) {
					if (method.value.getArgsCount() == args.size()) throw LotusException(STRING_LITERAL("Method \"") + methodName.text + STRING_LITERAL("\" with ") + std::to_wstring(args.size()) + STRING_LITERAL(" arguments already exists"), methodName.line);
				}

				methods[methodName.text].push_back(memberInfo);
			} else methods.emplace(methodName.text, std::vector<MethodMemberInfo>{memberInfo});
		}
		else {
			Token fieldName = consume(TokenType::IDENTIFIER);
			Expression fieldValue = MAKE_PTR<UndefinedExpression>();

			if (match(TokenType::EQUAL)) {
				fieldValue = expression();
			}

			while (match(TokenType::SEMICOLON));

			ClassMemberInfo memberInfo;
			memberInfo.accessModifier = accessModifier;

			if (fields.find(fieldName.text) != fields.end()) throw LotusException(STRING_LITERAL("Field \"") + fieldName.text + STRING_LITERAL("\" already exists"), fieldName.line);

			fields.emplace(fieldName.text, std::make_pair(fieldValue, memberInfo));
		}
	}

	return std::make_pair(fields, methods);
}

StringMap<Expression> lotus::Parser::handleObject() {
	StringMap<Expression> fields;

	consume(TokenType::LBRACE);

	while (!match(TokenType::RBRACE)) {
		Token fieldName = consume(TokenType::IDENTIFIER);
		Expression fieldValue = MAKE_PTR<UndefinedExpression>();

		if (match(TokenType::EQUAL)) {
			fieldValue = expression();
		}

		while (match(TokenType::SEMICOLON));

		if (fields.find(fieldName.text) != fields.end()) throw LotusException(STRING_LITERAL("Field \"") + fieldName.text + STRING_LITERAL("\" already exists"), fieldName.line);

		fields.emplace(fieldName.text, fieldValue);
	}

	return fields;
}