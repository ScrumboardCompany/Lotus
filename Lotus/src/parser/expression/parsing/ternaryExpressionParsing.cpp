#include "parser/parser.h"
#include "parser/expression/ternaryExpression.h"

using namespace lotus;

Expression lotus::Parser::ternary() {
	Expression result = logicalOr();

	while (true) {
		if (match(TokenType::QUESTION)) {
			Expression expr1 = logicalOr();

			consume(TokenType::COLON);

			result = MAKE_PTR<TernaryExpression>(result, expr1, logicalOr());
			continue;
		}
		break;
	}
	return result;
}