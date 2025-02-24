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

			std::pair<std::vector<Expression>, StringMap<Expression>> args;

			if (!match(TokenType::RPAREN)) {
				args = handleTakenArgs();

				consume(TokenType::RPAREN);
			}

			return MAKE_PTR<FunctionExpression>(name, args.first, args.second);
		}
		else {
			result = unaryPostfix();

			if (match(TokenType::LPAREN)) {
				std::pair<std::vector<Expression>, StringMap<Expression>> args;

				if (!match(TokenType::RPAREN)) {
					args = handleTakenArgs();

					consume(TokenType::RPAREN);
				}

				result = MAKE_PTR<CallLambdaExpression>(args.first, args.second, result);
				continue;
			}
		}
		break;
	}

	return result;
}