#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include <cmath>

using namespace lotus;

IntValue::IntValue(int value) : value(value) {
    type = STRING_LITERAL("int");
}

int lotus::IntValue::asInt(Variables& variables) {
	return value;
}

double lotus::IntValue::asDouble(Variables& variables) {
	return static_cast<double>(value);
}

bool lotus::IntValue::asBool(Variables& variables) {
    return static_cast<bool>(value);
}


String lotus::IntValue::asString(Variables& variables) {
    return std::to_wstring(value);
}

Value lotus::IntValue::add(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value + other->asInt(variables));
    return FLOAT(value + other->asDouble(variables));
}

Value lotus::IntValue::substract(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value - other->asInt(variables));
    return FLOAT(value - other->asDouble(variables));
}

Value lotus::IntValue::multiply(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value * other->asInt(variables));
    else if (other->getType() == STRING_LITERAL("string")) {
        String result;
        for (int i = 0; i < value; i++) {
            result += other->asString(variables);
        }
        return STRING(result);
    }
    return FLOAT(value * other->asDouble(variables));
}

Value lotus::IntValue::divide(const Value& other, Variables& variables) {
    double value2 = other->asDouble(variables);
    if (value2 == 0) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t divide by zero"));

    return FLOAT(static_cast<double>(value) / value2);
}

Value lotus::IntValue::power(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int")) return INT(static_cast<int>(pow(value, other->asInt(variables))));
    return FLOAT(pow(value, other->asDouble(variables)));
}

Value lotus::IntValue::divideModule(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("float")) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t use module operator over float type"));
    return INT(value % other->asInt(variables));
}

Value lotus::IntValue::bitwiseAnd(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value & other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseAnd"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseOr(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value | other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseOr"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseXor(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value ^ other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseXor"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseNot(Variables& variables) {
    return INT(~value);
}

Value lotus::IntValue::bitwiseLeftShift(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value << other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseLeftShift"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseRightShift(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value >> other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseRightShift"), getType(), other->getType());
}


Value lotus::IntValue::greater(const Value& other, Variables& variables) {
    return BOOL(value > other->asDouble(variables));
}

Value lotus::IntValue::less(const Value& other, Variables& variables) {
    return BOOL(value < other->asDouble(variables));
}

Value lotus::IntValue::greaterEqual(const Value& other, Variables& variables) {
    return BOOL(value >= other->asDouble(variables));
}

Value lotus::IntValue::lessEqual(const Value& other, Variables& variables) {
    return BOOL(value <= other->asDouble(variables));
}

Value lotus::IntValue::equality(const Value& other, Variables& variables) {
    return BOOL(value == other->asDouble(variables));
}

Value lotus::IntValue::inequality(const Value& other, Variables& variables) {
    return BOOL(value != other->asDouble(variables));
}

Value lotus::IntValue::logicalOr(const Value& other, Variables& variables) {
    return BOOL(asBool(variables) || other->asBool(variables));
}

Value lotus::IntValue::logicalAnd(const Value& other, Variables& variables) {
    return BOOL(asBool(variables) && other->asBool(variables));
}

Value lotus::IntValue::addSet(const Value& other, Variables& variables) {
    value = add(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::substractSet(const Value& other, Variables& variables) {
    value = substract(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::multiplySet(const Value& other, Variables& variables) {
    value = multiply(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::divideSet(const Value& other, Variables& variables) {
    value = divide(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::powerSet(const Value& other, Variables& variables) {
    value = powerSet(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::divideModuleSet(const Value& other, Variables& variables) {
    value = divideModuleSet(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::bitwiseAndSet(const Value& other, Variables& variables) {
    value = bitwiseAndSet(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::bitwiseOrSet(const Value& other, Variables& variables) {
    value = bitwiseOrSet(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::bitwiseXorSet(const Value& other, Variables& variables) {
    value = bitwiseXorSet(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::bitwiseNotSet(Variables& variables) {
    value = bitwiseNotSet(variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::bitwiseLeftShiftSet(const Value& other, Variables& variables) {
    value = bitwiseLeftShiftSet(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::bitwiseRightShiftSet(const Value& other, Variables& variables) {
    value = bitwiseRightShiftSet(other, variables)->asInt(variables);
    return INT(value);
}

Value lotus::IntValue::unaryPlus(Variables& variables) {
    return INT(+value);
}

Value lotus::IntValue::unaryMinus(Variables& variables) {
    return INT(-value);
}

Value lotus::IntValue::unaryNot(Variables& variables) {
    return BOOL(!value);
}

Value lotus::IntValue::prefixIncrement(Variables& variables) {
    return INT(++value);
}

Value lotus::IntValue::postfixIncrement(Variables& variables) {
    return INT(value++);
}

Value lotus::IntValue::prefixDecrement(Variables& variables) {
    return INT(--value);
}

Value lotus::IntValue::postfixDecrement(Variables& variables) {
    return INT(value--);
}


Value lotus::IntValue::size(Variables& variables) {
    if (value == 0)
        return INT(1);

    int count = 0;

    while (value != 0) {
        value = value / 10;
        ++count;
    }

    return INT(count);
}

Value lotus::IntValue::sizeInRam() {
    return INT(sizeof(IntValue));
}