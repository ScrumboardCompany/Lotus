#include "parser/parser.h"
#include "parser/expression/methodExpression.h"
#include "parser/expression/fieldExpression.h"

using namespace lotus;

Expression lotus::Parser::dot() {
	Expression result = index();

	while (true) {
        if (match(TokenType::DOT)) {
            String name = consume(TokenType::WORD).text;

            if (match(TokenType::LPAREN)) {

                std::vector<Expression> args;

                if (!match(TokenType::RPAREN)) {
                    args = handleExpressions();

                    consume(TokenType::RPAREN);
                }

                result = MAKE_PTR<MethodExpression>(result, name, args);
            }
            else result = MAKE_PTR<FieldExpression>(result, name);
            continue;
        }
        break;
	}

    return result;
}