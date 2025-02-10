#include "utils/utils.h"
#include "parser/expression/expresion.h"
#include "parser/value/value.h"
#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"

using namespace lotus;

Value lotus::callAllExpressionsAndReturnLastValue(const std::vector<Expression>& expressions) {
    if (expressions.empty()) return UNDEFINED();
    Value lastExpression;
    for (auto& expr : expressions) {
        lastExpression = expr->eval();
    }
    return lastExpression;
}