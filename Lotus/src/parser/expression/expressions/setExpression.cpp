#include "parser/expression/setExpression.h"
#include "parser/expression/indexExpression.h"
#include "parser/expression/fieldExpression.h"
#include "parser/expression/wordExpression.h"
#include "parser/expression/staticFieldExpression.h"
#include "structures/module.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::SetExpression::SetExpression(const Expression& expression1, const Expression& expression2, const SetOperationType& operation)
	: expression1(expression1), expression2(expression2), operation(operation) {}

Value lotus::SetExpression::eval(Module& module) {

    Value newValue = expression2->eval(module);

    auto applyOperation = [&](Value& target) -> Value {
        switch (operation) {
        case lotus::SetOperationType::SET:
            return target = newValue;
        case lotus::SetOperationType::ADDSET:
            return target->addSet(newValue, module);
        case lotus::SetOperationType::SUBSTRACTSET:
            return target->substractSet(newValue, module);
        case lotus::SetOperationType::MULTIPLYSET:
            return target->multiplySet(newValue, module);
        case lotus::SetOperationType::DIVIDESET:
            return target->divideSet(newValue, module);
        case lotus::SetOperationType::POWERSET:
            return target->powerSet(newValue, module);
        case lotus::SetOperationType::DIVIDEMODULESET:
            return target->divideModuleSet(newValue, module);
        case lotus::SetOperationType::BITWISEANDSET:
            return target->bitwiseAndSet(newValue, module);
        case lotus::SetOperationType::BITWISEORSET:
            return target->bitwiseOrSet(newValue, module);
        case lotus::SetOperationType::BITWISEXORSET:
            return target->bitwiseXorSet(newValue, module);
        case lotus::SetOperationType::BITWISENOTSET:
            return target->bitwiseNotSet(module);
        case lotus::SetOperationType::BITWISELEFTSHIFTSET:
            return target->bitwiseLeftShiftSet(newValue, module);
        case lotus::SetOperationType::BITIWSERIGHTSHIFTSET:
            return target->bitwiseRightShiftSet(newValue, module);
        default:
            throw LotusException(STRING_LITERAL("Undefined set operation"));
        }
        };

    if (auto varExpr = std::dynamic_pointer_cast<WordExpression>(expression1)) {
        Value& varRef = module.variables.get(varExpr->name);
        return applyOperation(varRef);
    }

    if (auto indexExpr = std::dynamic_pointer_cast<IndexExpression>(expression1)) {
        Value container = indexExpr->expression->eval(module);
        Value index = indexExpr->index->eval(module);

        Value element = container->getOfIndex(indexExpr->index->eval(module), module);

        return container->setOfIndex(indexExpr->index->eval(module), applyOperation(element), module);
    }

    if (auto fieldExpr = std::dynamic_pointer_cast<FieldExpression>(expression1)) {
        Value value = fieldExpr->expr->eval(module);
        String name = fieldExpr->field;

        Value& element = value->getField(name);

        return applyOperation(element);
    }

    if (auto staticField = std::dynamic_pointer_cast<StaticFieldExpression>(expression1)) {
        Value& field = module.statics.get(staticField->staticName).getField(staticField->field);
        return applyOperation(field);
    }

    return newValue;
}
