#include "parser/parser.h"
#include "parser/expression/unaryExpression.h"
#include "parser/expression/indexExpression.h"
#include "parser/expression/fieldExpression.h"
#include "parser/expression/setExpression.h"
#include "parser/expression/arithmeticExpression.h"
#include "parser/expression/methodExpression.h"

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
        else if (match(TokenType::PLUSPLUS)) {
            operations.push_back(UnaryOperationType::PREFIXINCREMENT);
        }
        else if (match(TokenType::MINUSMINUS)) {
            operations.push_back(UnaryOperationType::PREFIXDECREMENT);
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
        else if (match(TokenType::PLUSPLUS)) {
            result = MAKE_PTR<UnaryExpression>(result, UnaryOperationType::POSTFIXINCREMENT);
        }
        else if (match(TokenType::MINUSMINUS)) {
            result = MAKE_PTR<UnaryExpression>(result, UnaryOperationType::POSTFIXDECREMENT);
        }
        else if (match(TokenType::DOT)) {
            String name = consume(TokenType::WORD).text;

            if (match(TokenType::LPAREN)) {

                std::vector<Expression> args;

                if (!match(TokenType::RPAREN)) {
                    args = handleExpressions();

                    consume(TokenType::RPAREN);
                }

                result = MAKE_PTR<MethodExpression>(result, name, args, module.variables);
            }
            else result = MAKE_PTR<FieldExpression>(result, name);
        }
		else break;
	}

    if (match(TokenType::EQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::SET);
    }
    else if (match(TokenType::PLUSEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::ADDSET);
    }
    else if (match(TokenType::MINUSQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::SUBSTRACTSET);
    }
    else if (match(TokenType::STARQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::MULTIPLYSET);
    }
    else if (match(TokenType::SLASHQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::DIVIDESET);
    }

	return result;
}