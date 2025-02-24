#include "parser/parser.h"
#include "utils/lotusError.h"
#include "parser/expression/intExpression.h"
#include "parser/expression/floatExpression.h"
#include "parser/expression/stringExpression.h"
#include "parser/expression/variableExpression.h"
#include "parser/expression/undefinedExpression.h"
#include "parser/expression/boolExpression.h"
#include "parser/expression/arrayExpression.h"
#include "parser/expression/fieldExpression.h"
#include "parser/expression/objectExpression.h"
#include "parser/expression/lambdaExpression.h"
#include "parser/expression/staticFieldExpression.h"
#include "parser/expression/staticMethodExpression.h"

using namespace lotus;

Expression lotus::Parser::primary() {
	
	const Token CurrentToken = get(0);

	if (match(TokenType::INT_TYPE)) {
		return MAKE_PTR<IntExpression>(std::stoi(CurrentToken.text));
	}
	if (match(TokenType::FLOAT_TYPE)) {
		return MAKE_PTR<FloatExpression>(std::stod(CurrentToken.text));
	}
	if (match(TokenType::STRING_TYPE)) {
		return MAKE_PTR<StringExpression>(CurrentToken.text);
	}
	if (match(TokenType::WORD)) {
		if (match(TokenType::COLONCOLON)) {
			String name = consume(TokenType::WORD).text;

			if (match(TokenType::LPAREN)) {
				std::vector<Expression> args;

				if (!match(TokenType::RPAREN)) {
					args = handleExpressions();

					consume(TokenType::RPAREN);
				}

				return MAKE_PTR<StaticMethodExpression>(CurrentToken.text, name, args);
			}
			else {
				return MAKE_PTR<StaticFieldExpression>(CurrentToken.text, name);
			}
		}
		else return MAKE_PTR<VariableExpression>(CurrentToken.text);
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

	throw LotusException(STRING_LITERAL("Undefined expression"));
}