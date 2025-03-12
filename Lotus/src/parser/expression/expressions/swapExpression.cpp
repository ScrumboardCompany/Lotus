#include "parser/expression/swapExpression.h"
#include "parser/expression/indexExpression.h"
#include "parser/expression/fieldExpression.h"
#include "parser/expression/wordExpression.h"
#include "parser/expression/staticFieldOrEnumExpression.h"
#include "parser/value/undefinedValue.h"
#include "structures/module.h"

using namespace lotus;

lotus::SwapExpression::SwapExpression(const Expression& expr1, const Expression& expr2)
    : expr1(expr1), expr2(expr2) {
}

Value lotus::SwapExpression::eval(Module& module) {
    Value* value1 = nullptr;
    Value* value2 = nullptr;

    Value container1;
    Value index1;
    Value tempValue1;

    if (auto varExpr = std::dynamic_pointer_cast<WordExpression>(expr1)) {
        value1 = &module.variables.get(varExpr->name);
    }
    else if (auto fieldExpr = std::dynamic_pointer_cast<FieldExpression>(expr1)) {
        Value value = fieldExpr->expr->eval(module);
        String name = fieldExpr->field;

        value1 = &value->getField(name);
    }
    else if (auto indexExpr = std::dynamic_pointer_cast<IndexExpression>(expr1)) {
        container1 = indexExpr->expression->eval(module);
        index1 = indexExpr->index->eval(module);

        tempValue1 = container1->getOfIndex(index1, module);
        value1 = &tempValue1;
    }
    else if (auto staticField = std::dynamic_pointer_cast<StaticFieldOrEnumExpression>(expr1)) {
        value1 = &module.statics.get(staticField->staticName).getField(staticField->field);
    }
    else {
        static Value temp1;
        temp1 = expr1->eval(module);
        value1 = &temp1;
    }

    if (value1 == nullptr) return UNDEFINED();

    Value container2;
    Value index2;
    Value tempValue2;

    if (auto varExpr = std::dynamic_pointer_cast<WordExpression>(expr2)) {
        value2 = &module.variables.get(varExpr->name);
    }
    else if (auto fieldExpr = std::dynamic_pointer_cast<FieldExpression>(expr2)) {
        Value value = fieldExpr->expr->eval(module);
        String name = fieldExpr->field;

        value2 = &value->getField(name);
    }
    else if (auto indexExpr = std::dynamic_pointer_cast<IndexExpression>(expr2)) {
        container2 = indexExpr->expression->eval(module);
        index2 = indexExpr->index->eval(module);

        tempValue2 = container2->getOfIndex(index2, module);
        value2 = &tempValue2;
    }
    else if (auto staticField = std::dynamic_pointer_cast<StaticFieldOrEnumExpression>(expr2)) {
        value2 = &module.statics.get(staticField->staticName).getField(staticField->field);
    }
    else {
        static Value temp2;
        temp2 = expr2->eval(module);
        value2 = &temp2;
    }

    if (value2 == nullptr) return UNDEFINED();

    Value temp = *value1;
    *value1 = *value2;
    *value2 = temp;

    if (auto indexExpr = std::dynamic_pointer_cast<IndexExpression>(expr1)) {
        container1->setOfIndex(index1, *value1, module);
    }
    if (auto indexExpr = std::dynamic_pointer_cast<IndexExpression>(expr2)) {
        container2->setOfIndex(index2, *value2, module);
    }

    return UNDEFINED();
}
