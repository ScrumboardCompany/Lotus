#include "parser/parser.h"
#include "parser/expression/functionExpression.h"
#include "parser/expression/callLambdaExpression.h"

using namespace lotus;

Expression lotus::Parser::callFunction() {
	Expression result;

	while(true) {
		if (get(0).type == TokenType::WORD && get(1).type == TokenType::LPAREN) {
			String name = consume(TokenType::WORD).text;

			consume(TokenType::LPAREN);

			std::vector<Expression> args;

			if (!match(TokenType::RPAREN)) {
				args = handleExpressions();

				consume(TokenType::RPAREN);
			}

			return MAKE_PTR<FunctionExpression>(name, module.functions, module.variables, args);
		}
		else {
			result = unaryPostfix();

			if (match(TokenType::LPAREN)) {
				std::vector<Expression> args;

				if (!match(TokenType::RPAREN)) {
					args = handleExpressions();

					consume(TokenType::RPAREN);
				}

				result = MAKE_PTR<CallLambdaExpression>(module.variables, args, result);
				continue;
			}
		}
		break;
	}

	return result;
}