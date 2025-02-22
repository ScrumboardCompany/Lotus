#include "parser/expression/setExpression.h"
#include "parser/expression/indexExpression.h"
#include "parser/expression/fieldExpression.h"
#include "parser/expression/variableExpression.h"
#include "parser/expression/staticFieldExpression.h"
#include "structures/variables.h"
#include "structures/statics.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::SetExpression::SetExpression(const Expression& expression1, const Expression& expression2, const SetOperationType& operation, Variables& variables)
	: expression1(expression1), expression2(expression2), operation(operation), variables(variables) {}

Value lotus::SetExpression::eval() {

    Value newValue = expression2->eval();

    auto applyOperation = [&](Value& target) -> Value {
        switch (operation) {
        case lotus::SetOperationType::SET:
            return target = newValue;
        case lotus::SetOperationType::ADDSET:
            return target->addSet(newValue, variables);
        case lotus::SetOperationType::SUBSTRACTSET:
            return target->substractSet(newValue, variables);
        case lotus::SetOperationType::MULTIPLYSET:
            return target->multiplySet(newValue, variables);
        case lotus::SetOperationType::DIVIDESET:
            return target->divideSet(newValue, variables);
        case lotus::SetOperationType::POWERSET:
            return target->powerSet(newValue, variables);
        case lotus::SetOperationType::DIVIDEMODULESET:
            return target->divideModuleSet(newValue, variables);
        case lotus::SetOperationType::BITWISEANDSET:
            return target->bitwiseAndSet(newValue, variables);
        case lotus::SetOperationType::BITWISEORSET:
            return target->bitwiseOrSet(newValue, variables);
        case lotus::SetOperationType::BITWISEXORSET:
            return target->bitwiseXorSet(newValue, variables);
        case lotus::SetOperationType::BITWISENOTSET:
            return target->bitwiseNotSet(variables);
        case lotus::SetOperationType::BITWISELEFTSHIFTSET:
            return target->bitwiseLeftShiftSet(newValue, variables);
        case lotus::SetOperationType::BITIWSERIGHTSHIFTSET:
            return target->bitwiseRightShiftSet(newValue, variables);
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

        Value element = container->getOfIndex(indexExpr->index->eval(), variables);

        return container->setOfIndex(indexExpr->index->eval(), applyOperation(element), variables);
    }

    if (auto fieldExpr = std::dynamic_pointer_cast<FieldExpression>(expression1)) {
        Value value = fieldExpr->expr->eval();
        String name = fieldExpr->field;

        Value& element = value->getField(name);

        return applyOperation(element);
    }

    if (auto staticField = std::dynamic_pointer_cast<StaticFieldExpression>(expression1)) {
        Value& field = staticField->statics.get(staticField->staticName).getField(staticField->field);
        return applyOperation(field);
    }

    return newValue;
}
