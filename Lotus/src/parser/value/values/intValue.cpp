#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"
#include "utils/utils.h"
#include "parser/function/function.h"
#include "structures/module.h"
#include <cmath>

using namespace lotus;

IntValue::IntValue(Int value) : value(value) {
    type = STRING_LITERAL("int");
}

Int lotus::IntValue::asInt(Module&) {
	return value;
}

double lotus::IntValue::asDouble(Module&) {
    return static_cast<double>(value);
}

bool lotus::IntValue::asBool(Module&) {
    return static_cast<bool>(value);
}


String lotus::IntValue::asString(Module&) {
    return std::to_wstring(value);
}

Value lotus::IntValue::add(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("add"), getType(), other->getType());
    if (other->getType() == STRING_LITERAL("int")) return INT(value + other->asInt(module));
    return FLOAT(value + other->asDouble(module));
}

Value lotus::IntValue::substract(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("substract"), getType(), other->getType());
    if (other->getType() == STRING_LITERAL("int")) return INT(value - other->asInt(module));
    return FLOAT(value - other->asDouble(module));
}

Value lotus::IntValue::multiply(const Value& other, Module& module) {
    if (!isNumber(other) && !other->instanceOf("string")) throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
    if (other->getType() == STRING_LITERAL("int")) return INT(value * other->asInt(module));
    else if (other->getType() == STRING_LITERAL("string")) {
        String result;
        for (int i = 0; i < value; i++) {
            result += other->asString(module);
        }
        return STRING(result, module);
    }
    return FLOAT(value * other->asDouble(module));
}

Value lotus::IntValue::divide(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("divide"), getType(), other->getType());
    double value2 = other->asDouble(module);
    if (value2 == 0) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t divide by zero"));

    return FLOAT(static_cast<double>(value) / value2);
}

Value lotus::IntValue::power(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("power"), getType(), other->getType());
    if (other->getType() == STRING_LITERAL("int")) return INT(static_cast<int>(pow(value, other->asInt(module))));
    return FLOAT(pow(value, other->asDouble(module)));
}

Value lotus::IntValue::divideModule(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("divideModule"), getType(), other->getType());
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

Value lotus::IntValue::bitwiseNot(Module&) {
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
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("greater"), getType(), other->getType());
    return BOOL(value > other->asDouble(module));
}

Value lotus::IntValue::less(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("less"), getType(), other->getType());
    return BOOL(value < other->asDouble(module));
}

Value lotus::IntValue::greaterEqual(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("greaterEqual"), getType(), other->getType());
    return BOOL(value >= other->asDouble(module));
}

Value lotus::IntValue::lessEqual(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("lessEqual"), getType(), other->getType());
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
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("addSet"), getType(), other->getType());
    value = add(other, module)->asInt(module);
    if (other->getType() == STRING_LITERAL("int")) return INT(value);
    return FLOAT(asDouble(module));
}

Value lotus::IntValue::substractSet(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("substractSet"), getType(), other->getType());
    value = substract(other, module)->asInt(module);
    if (other->getType() == STRING_LITERAL("int")) return INT(value);
    return FLOAT(asDouble(module));
}

Value lotus::IntValue::multiplySet(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("multiplySet"), getType(), other->getType());
    value = multiply(other, module)->asInt(module);
    if (other->getType() == STRING_LITERAL("int")) return INT(value);
    return FLOAT(asDouble(module));
}

Value lotus::IntValue::divideSet(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("divideSet"), getType(), other->getType());
    value = divide(other, module)->asInt(module);
    if (other->getType() == STRING_LITERAL("int")) return INT(value);
    return FLOAT(asDouble(module));
}

Value lotus::IntValue::powerSet(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("powerSet"), getType(), other->getType());
    value = power(other, module)->asInt(module);
    if (other->getType() == STRING_LITERAL("int")) return INT(value);
    return FLOAT(asDouble(module));
}

Value lotus::IntValue::divideModuleSet(const Value& other, Module& module) {
    if (!isNumber(other)) throwOverloadError(STRING_LITERAL("powerSet"), getType(), other->getType());
    value = divideModule(other, module)->asInt(module);
    if (other->getType() == STRING_LITERAL("float")) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t use module operator over float type"));
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

Value lotus::IntValue::unaryPlus(Module&) {
    return INT(+value);
}

Value lotus::IntValue::unaryMinus(Module&) {
    return INT(-value);
}

Value lotus::IntValue::unaryNot(Module&) {
    return BOOL(!value);
}

Value lotus::IntValue::prefixIncrement(Module&) {
    return INT(++value);
}

Value lotus::IntValue::postfixIncrement(Module&) {
    return INT(value++);
}

Value lotus::IntValue::prefixDecrement(Module&) {
    return INT(--value);
}

Value lotus::IntValue::postfixDecrement(Module&) {
    return INT(value--);
}


Value lotus::IntValue::size(Module&) {
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
    return INT(static_cast<Int>(sizeof(*this)));
}

Value lotus::INT(Int value) {
    return MAKE_PTR<IntValue>(value);
}