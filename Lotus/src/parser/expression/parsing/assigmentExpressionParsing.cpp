#include "parser/parser.h"
#include "parser/expression/setExpression.h"

using namespace lotus;

Expression lotus::Parser::assigment() {
    Expression result = ternary();

    if (match(TokenType::EQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::SET, module.variables);
    }
    else if (match(TokenType::PLUSEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::ADDSET, module.variables);
    }
    else if (match(TokenType::MINUSQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::SUBSTRACTSET, module.variables);
    }
    else if (match(TokenType::STARQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::MULTIPLYSET, module.variables);
    }
    else if (match(TokenType::SLASHQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::DIVIDESET, module.variables);
    }
    else if (match(TokenType::STARSTAREQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::POWERSET, module.variables);
    }
    else if (match(TokenType::SLASHSLASHEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::DIVIDEMODULESET, module.variables);
    }
    else if (match(TokenType::GREATERGREATEREQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITIWSERIGHTSHIFTSET, module.variables);
    }
    else if (match(TokenType::LESSLESSEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISELEFTSHIFTSET, module.variables);
    }
    else if (match(TokenType::AMPEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISEANDSET, module.variables);
    }
    else if (match(TokenType::BAREQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISEORSET, module.variables);
    }
    else if (match(TokenType::CARETEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISEXORSET, module.variables);
    }
    else if (match(TokenType::TILDAEQUAL)) {
        result = MAKE_PTR<SetExpression>(result, expression(), SetOperationType::BITWISENOTSET, module.variables);
    }

    return result;
}