#include "parser/parser.h"
#include "utils/lotusError.h"
#include "parser/expression/intExpression.h"
#include "parser/expression/floatExpression.h"
#include "parser/expression/stringExpression.h"
#include "parser/expression/variableExpression.h"
#include "parser/expression/undefinedExpression.h"
#include "parser/expression/boolExpression.h"
#include "parser/expression/arrayExpression.h"
#include "parser/expression/functionExpression.h"

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

		if (match(TokenType::LPAREN)) {

			consume(TokenType::RPAREN);

			return MAKE_PTR<FunctionExpression>(CurrentToken.text, functions);
		}
		else {
			return MAKE_PTR<VariableExpression>(CurrentToken.text, variables);
		}
		
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
	if (match(TokenType::LBRACKET)) {
		std::vector<Expression> elements = handleCommas();
		consume(TokenType::RBRACKET);
		return MAKE_PTR<ArrayExpression>(elements);
	}
	if (match(TokenType::LPAREN)) {
		Expression result = expression();
		match(TokenType::RPAREN);
		return result;
	}

	throw LotusException(STRING_LITERAL("Undefined expression"));
}