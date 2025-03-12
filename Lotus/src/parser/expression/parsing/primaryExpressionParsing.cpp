#include "parser/parser.h"
#include "utils/lotusError.h"
#include "parser/expression/intExpression.h"
#include "parser/expression/floatExpression.h"
#include "parser/expression/stringExpression.h"
#include "parser/expression/wordExpression.h"
#include "parser/expression/undefinedExpression.h"
#include "parser/expression/boolExpression.h"
#include "parser/expression/arrayExpression.h"
#include "parser/expression/fieldExpression.h"
#include "parser/expression/objectExpression.h"
#include "parser/expression/lambdaExpression.h"
#include "parser/expression/staticFieldOrEnumExpression.h"
#include "parser/expression/staticMethodExpression.h"

using namespace lotus;

Expression lotus::Parser::primary() {
	
	const Token currentToken = get(0);

	if (match(TokenType::HEX)) {
		return MAKE_PTR<IntExpression>(std::stoll(currentToken.text, nullptr, 16));
	}
	if (match(TokenType::INT_TYPE)) {
		return MAKE_PTR<IntExpression>(std::stoll(currentToken.text));
	}
	if (match(TokenType::FLOAT_TYPE)) {
		return MAKE_PTR<FloatExpression>(std::stod(currentToken.text));
	}
	if (match(TokenType::STRING_TYPE)) {
		return MAKE_PTR<StringExpression>(currentToken.text);
	}
	if (match(TokenType::IDENTIFIER)) {
		if (match(TokenType::COLONCOLON)) {
			String name = consume(TokenType::IDENTIFIER).text;

			if (match(TokenType::LPAREN)) {
				std::pair<std::vector<Expression>, StringMap<Expression>> args;

				if (!match(TokenType::RPAREN)) {
					args = handleTakenArgs();

					consume(TokenType::RPAREN);
				}

				return MAKE_PTR<StaticMethodExpression>(currentToken.text, name, args.first, args.second);
			}
			else {
				return MAKE_PTR<StaticFieldOrEnumExpression>(currentToken.text, name);
			}
		}
		else return MAKE_PTR<WordExpression>(currentToken.text);
	}
	if (match(TokenType::UNDEFINED_)) {
		return MAKE_PTR<UndefinedExpression>();
	}
	if (match(TokenType::TRUE)) {
		return MAKE_PTR<BoolExpression>(true);
	}
	if (match(TokenType::FALSE)) {
		return MAKE_PTR<BoolExpression>(false);
	}
	if (match(TokenType::FLAGVALUE)) {

		consume(TokenType::LPAREN);
		String flag = consume(TokenType::IDENTIFIER).text;
		consume(TokenType::RPAREN);

		return MAKE_PTR<BoolExpression>(module.flags.get(flag));
	}
	if (match(TokenType::LET)) {
		return handleLetExpression();
	}
	if (match(TokenType::DEF)) {
		std::vector<Argument> args = handleArgs();

		Statement body = handleBlockStatement();

		Function function(body, args);

		return MAKE_PTR<LambdaExpression>(function);
	}
	if (match(TokenType::LBRACKET)) {

		std::vector<Expression> elements;
		
		if (!match(TokenType::RBRACKET)) {
			elements = handleExpressions();
			consume(TokenType::RBRACKET);
		}
		return MAKE_PTR<ArrayExpression>(elements);
	}

	if (match(TokenType::LPAREN)) {
		Expression result = expression();
		match(TokenType::RPAREN);
		return result;
	}
	if (get(0).type == TokenType::LBRACE) {
		return MAKE_PTR<ObjectExpression>(handleObject());
	}

	throw LotusException(STRING_LITERAL("Undefined expression"), currentToken.line);
}