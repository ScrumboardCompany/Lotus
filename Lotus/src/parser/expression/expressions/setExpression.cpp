#include "parser/expression/setExpression.h"
#include "parser/expression/indexExpression.h"
#include "parser/expression/fieldExpression.h"
#include "parser/expression/variableExpression.h"
#include "structures/variables.h"
#include "utils/lotusError.h"
#include "parser/value/stringCharReference.h"

using namespace lotus;

lotus::SetExpression::SetExpression(const Expression& expression1, const Expression& expression2, const SetOperationType& operation)
	: expression1(expression1), expression2(expression2), operation(operation) {}

Value lotus::SetExpression::eval() {

    Value newValue = expression2->eval();

    auto applyOperation = [&](Value& target) -> Value {
        switch (operation) {
        case lotus::SetOperationType::SET:
            return target = newValue;
        case lotus::SetOperationType::ADDSET:
            return target->addSet(newValue);
        case lotus::SetOperationType::SUBSTRACTSET:
            return target->substractSet(newValue);
        case lotus::SetOperationType::MULTIPLYSET:
            return target->multiplySet(newValue);
        case lotus::SetOperationType::DIVIDESET:
            return target->divideSet(newValue);
        default:
            throw LotusException(STRING_LITERAL("Undefined set operation"));
        }
        };

    if (auto varExpr = std::dynamic_pointer_cast<VariableExpression>(expression1)) {
        Value& varRef = varExpr->variables.get(varExpr->name);
        return applyOperation(varRef);
    }

    if (auto indexExpr = std::dynamic_pointer_cast<IndexExpression>(expression1)) {
        Value container = indexExpr->expression->eval();
        Value index = indexExpr->index->eval();

        Value& element = container->index(index);

        if (operation == lotus::SetOperationType::SET) {
            if (auto stringElement = std::dynamic_pointer_cast<StringCharReference>(element)) {
                stringElement->set(newValue);
            }
            else {
                element = newValue;
            }
        }
        else {
            return applyOperation(element);
        }

        return container;
    }

    if (auto fieldExpr = std::dynamic_pointer_cast<FieldExpression>(expression1)) {
        Value value = fieldExpr->expr->eval();
        String name = fieldExpr->field;

        Value& element = value->getField(name);

        return applyOperation(element);
    }

    return newValue;
}
