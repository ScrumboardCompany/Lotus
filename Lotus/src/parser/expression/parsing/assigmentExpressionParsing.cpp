#include "parser/parser.h"
#include "parser/expression/setExpression.h"

using namespace lotus;

Expression lotus::Parser::assigment() {
    Expression result = ternary();

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
    else if (match(TokenType::STARSTAREQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::POWERSET);
    }
    else if (match(TokenType::SLASHSLASHEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::DIVIDEMODULESET);
    }
    else if (match(TokenType::GREATERGREATEREQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITIWSERIGHTSHIFTSET);
    }
    else if (match(TokenType::LESSLESSEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISELEFTSHIFTSET);
    }
    else if (match(TokenType::AMPEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISEANDSET);
    }
    else if (match(TokenType::BAREQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISEORSET);
    }
    else if (match(TokenType::CARETEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISEXORSET);
    }
    else if (match(TokenType::TILDAEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISENOTSET);
    }

    return result;
}