#include "parser/parser.h"
#include "parser/expression/unaryExpression.h"
#include "parser/expression/arithmeticExpression.h"
#include "parser/expression/bitwiseExpression.h"

using namespace lotus;

Expression lotus::Parser::unaryNot() {
    Expression result;

    while (true) {
        if (match(TokenType::NOT)) {
            result = MAKE_PTR<UnaryExpression>(unaryPlusMinus(), UnaryOperationType::LOGICALNOT);
            continue;
        }
        if (match(TokenType::TILDA)) {
            result = MAKE_PTR<UnaryExpression>(unaryPlusMinus(), UnaryOperationType::BITWISENOT);
            continue;
        }
        break;
    }

    return result ? result : unaryPlusMinus();
}

Expression lotus::Parser::unaryPlusMinus() {
    Expression result;
    
    while (true) {
        if (match(TokenType::PLUS)) {
            result = MAKE_PTR<UnaryExpression>(unaryPrefix(), UnaryOperationType::PLUS);
            continue;
        }
        if (match(TokenType::MINUS)) {
            result = MAKE_PTR<UnaryExpression>(unaryPrefix(), UnaryOperationType::MINUS);
            continue;
        }
        break;
    }

    return result ? result : unaryPrefix();
}

Expression lotus::Parser::unaryPrefix() {
    if (match(TokenType::PLUSPLUS)) {
        return MAKE_PTR<UnaryExpression>(dot(), UnaryOperationType::PREFIXINCREMENT);
    }
    else if (match(TokenType::MINUSMINUS)) {
        return MAKE_PTR<UnaryExpression>(dot(), UnaryOperationType::PREFIXDECREMENT);
    }

    return dot();
}

Expression lotus::Parser::unaryPostfix() {
    Expression result = primary();

    if (match(TokenType::PLUSPLUS)) {
        result = MAKE_PTR<UnaryExpression>(result, UnaryOperationType::POSTFIXINCREMENT);
    } 
    else if (match(TokenType::MINUSMINUS)) {
        result = MAKE_PTR<UnaryExpression>(result, UnaryOperationType::POSTFIXDECREMENT);
    }

    return result;
}