#include "parser/parser.h"
#include "parser/expression/unaryExpression.h"
#include "parser/expression/indexExpression.h"

using namespace lotus;

Expression lotus::Parser::unary() {
	
	Expression result;

	while (true) {
		if (match(TokenType::PLUS)) {
			result = MAKE_PTR<UnaryExpression>(primary(), UnaryOperationType::PLUS);
		}
		else if (match(TokenType::MINUS)) {
			result = MAKE_PTR<UnaryExpression>(primary(), UnaryOperationType::MINUS);
		}
		else if (match(TokenType::NOT)) {
			result = MAKE_PTR<UnaryExpression>(primary(), UnaryOperationType::NOT);
		}
		else {
			result = primary();
			break;
		}
	}

	//if (!result) result = primary();

	while (true) {
		if (match(TokenType::LBRACKET)) {
			Expression index = expression();
			consume(TokenType::RBRACKET);
			result = MAKE_PTR<IndexExpression>(result, index);
		}
		else break;
	}

	return result;
}