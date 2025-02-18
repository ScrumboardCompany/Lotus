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

int lotus::IntValue::asInt() {
	return value;
}

double lotus::IntValue::asDouble() {
	return static_cast<double>(value);
}

bool lotus::IntValue::asBool() {
    return static_cast<bool>(value);
}


String lotus::IntValue::asString() {
    return std::to_wstring(value);
}

Value lotus::IntValue::add(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value + other->asInt());
    return FLOAT(value + other->asDouble());
}

Value lotus::IntValue::substract(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value - other->asInt());
    return FLOAT(value - other->asDouble());
}

Value lotus::IntValue::multiply(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value * other->asInt());
    else if (other->getType() == STRING_LITERAL("string")) {
        String result;
        for (int i = 0; i < value; i++) {
            result += other->asString();
        }
        return STRING(result);
    }
    return FLOAT(value * other->asDouble());
}

Value lotus::IntValue::divide(const Value& other) {
    double value2 = other->asDouble();
    if (value2 == 0) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t divide by zero"));

    return FLOAT(static_cast<double>(value) / value2);
}

Value lotus::IntValue::power(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(static_cast<int>(pow(value, other->asInt())));
    return FLOAT(pow(value, other->asDouble()));
}

Value lotus::IntValue::divideModule(const Value& other) {
    if (other->getType() == STRING_LITERAL("float")) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t use module operator over float type"));
    return INT(value % other->asInt());
}

Value lotus::IntValue::bitwiseAnd(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value & other->asInt());
    if (other->getType() == STRING_LITERAL("bool")) return INT(value & other->asBool());
    throwOverloadError(STRING_LITERAL("bitwiseAnd"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseOr(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value | other->asInt());
    if (other->getType() == STRING_LITERAL("bool")) return INT(value | other->asBool());
    throwOverloadError(STRING_LITERAL("bitwiseOr"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseXor(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value ^ other->asInt());
    if (other->getType() == STRING_LITERAL("bool")) return INT(value ^ other->asBool());
    throwOverloadError(STRING_LITERAL("bitwiseXor"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseNot() {
    return INT(~value);
}

Value lotus::IntValue::bitwiseLeftShift(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value << other->asInt());
    if (other->getType() == STRING_LITERAL("bool")) return INT(value << other->asBool());
    throwOverloadError(STRING_LITERAL("bitwiseLeftShift"), getType(), other->getType());
}

Value lotus::IntValue::bitwiseRightShift(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) return INT(value >> other->asInt());
    if (other->getType() == STRING_LITERAL("bool")) return INT(value >> other->asBool());
    throwOverloadError(STRING_LITERAL("bitwiseRightShift"), getType(), other->getType());
}

Value lotus::IntValue::greater(const Value& other) {
    return BOOL(value > other->asDouble());
}

Value lotus::IntValue::less(const Value& other) {
    return BOOL(value < other->asDouble());
}

Value lotus::IntValue::greaterEqual(const Value& other) {
    return BOOL(value >= other->asDouble());
}

Value lotus::IntValue::lessEqual(const Value& other) {
    return BOOL(value <= other->asDouble());
}

Value lotus::IntValue::equality(const Value& other) {
    return BOOL(value == other->asDouble());
}

Value lotus::IntValue::inequality(const Value& other) {
    return BOOL(value != other->asDouble());
}

Value lotus::IntValue::logicalOr(const Value& other) {
    return BOOL(asBool() || other->asBool());
}

Value lotus::IntValue::logicalAnd(const Value& other) {
    return BOOL(asBool() && other->asBool());
}

Value lotus::IntValue::addSet(const Value& other) {
    value = add(other)->asInt();
    return INT(value);
}

Value lotus::IntValue::substractSet(const Value& other) {
    value = substract(other)->asInt();
    return INT(value);
}

Value lotus::IntValue::multiplySet(const Value& other) {
    value = multiply(other)->asInt();
    return INT(value);
}

Value lotus::IntValue::divideSet(const Value& other) {
    value = divide(other)->asInt();
    return INT(value);
}

Value lotus::IntValue::unaryPlus() {
	return INT(+value);
}

Value lotus::IntValue::unaryMinus() {
	return INT(-value);
}

Value lotus::IntValue::unaryNot() {
    return BOOL(!value);
}

Value lotus::IntValue::prefixIncrement() {
    return INT(++value);
}

Value lotus::IntValue::postfixIncrement() {
    return INT(value++);
}

Value lotus::IntValue::prefixDecrement() {
    return INT(--value);
}

Value lotus::IntValue::postfixDecrement() {
    return INT(value--);
}

Value lotus::IntValue::size() {
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