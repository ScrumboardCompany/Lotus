#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/module.h"
#include <cmath>

using namespace lotus;

IntValue::IntValue(int value) : value(value) {
    type = STRING_LITERAL("int");
}

int lotus::IntValue::asInt(Module& module) {
	return value;
}

double lotus::IntValue::asDouble(Module& module) {
	return static_cast<double>(value);
}

bool lotus::IntValue::asBool(Module& module) {
    return static_cast<bool>(value);
}


String lotus::IntValue::asString(Module& module) {
    return std::to_wstring(value);
}

Value lotus::IntValue::add(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value + other->asInt(module));
    return FLOAT(value + other->asDouble(module));
}

Value lotus::IntValue::substract(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value - other->asInt(module));
    return FLOAT(value - other->asDouble(module));
}

Value lotus::IntValue::multiply(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value * other->asInt(module));
    else if (other->getType() == STRING_LITERAL("string")) {
        String result;
        for (int i = 0; i < value; i++) {
            result += other->asString(module);
        }
        return STRING(result);
    }
    return FLOAT(value * other->asDouble(module));
}

Value lotus::IntValue::divide(const Value& other, Module& module) {
    double value2 = other->asDouble(module);
    if (value2 == 0) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t divide by zero"));

    return FLOAT(static_cast<double>(value) / value2);
}

Value lotus::IntValue::power(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int")) return INT(static_cast<int>(pow(value, other->asInt(module))));
    return FLOAT(pow(value, other->asDouble(module)));
}

Value lotus::IntValue::divideModule(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("float")) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t use module operator over float type"));
    return INT(value % other->asInt(module));
}

Value lotus::IntValue::bitwiseAnd(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value & other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseAnd"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseOr(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value | other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseOr"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseXor(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value ^ other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseXor"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseNot(Module& module) {
    return INT(~value);
}

Value lotus::IntValue::bitwiseLeftShift(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value << other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseLeftShift"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseRightShift(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(value >> other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseRightShift"), getType(), other->getType());
}


Value lotus::IntValue::greater(const Value& other, Module& module) {
    return BOOL(value > other->asDouble(module));
}

Value lotus::IntValue::less(const Value& other, Module& module) {
    return BOOL(value < other->asDouble(module));
}

Value lotus::IntValue::greaterEqual(const Value& other, Module& module) {
    return BOOL(value >= other->asDouble(module));
}

Value lotus::IntValue::lessEqual(const Value& other, Module& module) {
    return BOOL(value <= other->asDouble(module));
}

Value lotus::IntValue::equality(const Value& other, Module& module) {
    return BOOL(value == other->asDouble(module));
}

Value lotus::IntValue::inequality(const Value& other, Module& module) {
    return BOOL(value != other->asDouble(module));
}

Value lotus::IntValue::logicalOr(const Value& other, Module& module) {
    return BOOL(asBool(module) || other->asBool(module));
}

Value lotus::IntValue::logicalAnd(const Value& other, Module& module) {
    return BOOL(asBool(module) && other->asBool(module));
}

Value lotus::IntValue::addSet(const Value& other, Module& module) {
    value = add(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::substractSet(const Value& other, Module& module) {
    value = substract(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::multiplySet(const Value& other, Module& module) {
    value = multiply(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::divideSet(const Value& other, Module& module) {
    value = divide(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::powerSet(const Value& other, Module& module) {
    value = power(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::divideModuleSet(const Value& other, Module& module) {
    value = divideModule(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::bitwiseAndSet(const Value& other, Module& module) {
    value = bitwiseAnd(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::bitwiseOrSet(const Value& other, Module& module) {
    value = bitwiseOr(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::bitwiseXorSet(const Value& other, Module& module) {
    value = bitwiseXor(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::bitwiseNotSet(Module& module) {
    value = bitwiseNot(module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::bitwiseLeftShiftSet(const Value& other, Module& module) {
    value = bitwiseLeftShift(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::bitwiseRightShiftSet(const Value& other, Module& module) {
    value = bitwiseRightShift(other, module)->asInt(module);
    return INT(value);
}

Value lotus::IntValue::unaryPlus(Module& module) {
    return INT(+value);
}

Value lotus::IntValue::unaryMinus(Module& module) {
    return INT(-value);
}

Value lotus::IntValue::unaryNot(Module& module) {
    return BOOL(!value);
}

Value lotus::IntValue::prefixIncrement(Module& module) {
    return INT(++value);
}

Value lotus::IntValue::postfixIncrement(Module& module) {
    return INT(value++);
}

Value lotus::IntValue::prefixDecrement(Module& module) {
    return INT(--value);
}

Value lotus::IntValue::postfixDecrement(Module& module) {
    return INT(value--);
}


Value lotus::IntValue::size(Module& module) {
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