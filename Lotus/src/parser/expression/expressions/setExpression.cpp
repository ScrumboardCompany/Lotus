#include "parser/expression/setExpression.h"
#include "parser/expression/indexExpression.h"
#include "parser/expression/variableExpression.h"
#include "structures/variables.h"
#include "utils/lotusError.h"
#include "parser/value/stringCharReference.h"

using namespace lotus;

lotus::SetExpression::SetExpression(const Expression& expression1, const Expression& expression2)
	: expression1(expression1), expression2(expression2) {}

Value lotus::SetExpression::eval() {
    Value newValue = expression2->eval();

    if (auto varExpr = std::dynamic_pointer_cast<VariableExpression>(expression1)) {
        varExpr->variables.set(varExpr->name, newValue);
        return newValue;
    }

    if (auto indexExpr = std::dynamic_pointer_cast<IndexExpression>(expression1)) {
        Value container = indexExpr->expression->eval();
        Value index = indexExpr->index->eval();

        Value& element = container->index(index);

        if (auto stringElement = std::dynamic_pointer_cast<StringCharReference>(element)) {
            stringElement->set(newValue);
        }
        else element = newValue;

        return container;
    }

    return newValue;
}
