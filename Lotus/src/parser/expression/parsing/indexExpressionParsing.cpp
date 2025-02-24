#include "parser/parser.h"
#include "parser/expression/indexExpression.h"

using namespace lotus;

Expression lotus::Parser::index() {
	Expression result = callFunction();

	while (true) {
		if (match(TokenType::LBRACKET)) {
			Expression index = expression();
			consume(TokenType::RBRACKET);
			result = MAKE_PTR<IndexExpression>(result, index, module.variables);
			continue;
		}
		break;
	}

	return result;
}