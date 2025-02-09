#include "parser/parser.h"
#include "utils/lotusError.h"
#include "parser/expression/intExpression.h"
#include "parser/expression/floatExpression.h"

using namespace lotus;

Expression lotus::Parser::primary() {
	
	const Token CurrentToken = get(0);

	if (match(TokenType::INT_TYPE)) {
		return MAKE_PTR<IntExpression>(std::stoi(CurrentToken.text));
	}
	if (match(TokenType::FLOAT_TYPE)) {
		return MAKE_PTR<FloatExpression>(std::stod(CurrentToken.text));
	}

	if (match(TokenType::LPAREN)) {
		Expression result = expression();
		match(TokenType::RPAREN);
		return result;
	}

	throw LotusException("Undefined expression");
}