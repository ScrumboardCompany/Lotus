#include "parser/parser.h"
#include "parser/expression/unaryExpression.h"
#include "parser/expression/indexExpression.h"
#include "parser/expression/setExpression.h"

using namespace lotus;

Expression lotus::Parser::unary() {

    std::vector<UnaryOperationType> operations;

    while (true) {
        if (match(TokenType::PLUS)) {
            operations.push_back(UnaryOperationType::PLUS);
        }
        else if (match(TokenType::MINUS)) {
            operations.push_back(UnaryOperationType::MINUS);
        }
        else if (match(TokenType::NOT)) {
            operations.push_back(UnaryOperationType::NOT);
        }
        else {
            break;
        }
    }

    Expression result = primary();

    for (auto it = operations.rbegin(); it != operations.rend(); ++it) {
        result = MAKE_PTR<UnaryExpression>(result, *it);
    }

	while (true) {
		if (match(TokenType::LBRACKET)) {
			Expression index = expression();
			consume(TokenType::RBRACKET);
			result = MAKE_PTR<IndexExpression>(result, index);
		}
		else break;
	}

    if (match(TokenType::EQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression());
    }

	return result;
}