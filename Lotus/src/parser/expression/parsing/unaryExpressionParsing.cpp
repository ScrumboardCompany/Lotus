#include "parser/parser.h"
#include "parser/expression/unaryExpression.h"
#include "parser/expression/arithmeticExpression.h"
#include "parser/expression/bitwiseExpression.h"
#include "parser/expression/indexExpression.h"
#include "parser/expression/callLambdaExpression.h"
#include "parser/expression/methodExpression.h"
#include "parser/expression/fieldExpression.h"
#include "parser/expression/setExpression.h"

using namespace lotus;

Expression lotus::Parser::unary() {
    if (match(TokenType::PLUS)) {
        return MAKE_PTR<UnaryExpression>(unary(), UnaryOperationType::PLUS);
    }
    if (match(TokenType::MINUS)) {
        return MAKE_PTR<UnaryExpression>(unary(), UnaryOperationType::MINUS);
    }
    if (match(TokenType::NOT)) {
        return MAKE_PTR<UnaryExpression>(unary(), UnaryOperationType::LOGICALNOT);
    }
    if (match(TokenType::TILDA)) {
        return MAKE_PTR<UnaryExpression>(unary(), UnaryOperationType::BITWISENOT);
    }
    if (match(TokenType::PLUSPLUS)) {
        return MAKE_PTR<UnaryExpression>(unary(), UnaryOperationType::PREFIXINCREMENT);
    }
    if (match(TokenType::MINUSMINUS)) {
        return MAKE_PTR<UnaryExpression>(unary(), UnaryOperationType::PREFIXDECREMENT);
    }

    Expression result = primary();

    while (true) {
        if (match(TokenType::LBRACKET)) {
            Expression index = expression();
            consume(TokenType::RBRACKET);
            result = MAKE_PTR<IndexExpression>(result, index);
        }
        else if (match(TokenType::LPAREN)) {
            std::pair<std::vector<Expression>, StringMap<Expression>> args;

            if (!match(TokenType::RPAREN)) {
                args = handleTakenArgs();

                consume(TokenType::RPAREN);
            }

            result = MAKE_PTR<CallLambdaExpression>(args.first, args.second, result);
        }
        else if (match(TokenType::PLUSPLUS)) {
            result = MAKE_PTR<UnaryExpression>(result, UnaryOperationType::POSTFIXINCREMENT);
        }
        else if (match(TokenType::MINUSMINUS)) {
            result = MAKE_PTR<UnaryExpression>(result, UnaryOperationType::POSTFIXDECREMENT);
        }
        else if (match(TokenType::DOT)) {
            String name = consume(TokenType::IDENTIFIER).text;
            if (match(TokenType::LPAREN)) {
                std::pair<std::vector<Expression>, StringMap<Expression>> args;

                if (!match(TokenType::RPAREN)) {
                    args = handleTakenArgs();

                    consume(TokenType::RPAREN);
                }

                result = MAKE_PTR<MethodExpression>(result, name, args.first, args.second);
            }
            else result = MAKE_PTR<FieldExpression>(result, name);
        }
        else break;
    }

    return result;
}