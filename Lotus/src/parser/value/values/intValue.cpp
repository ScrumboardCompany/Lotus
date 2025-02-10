#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"

using namespace lotus;

IntValue::IntValue(int value) : value(value) {}

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

String lotus::IntValue::getType() const {
	return STRING_LITERAL("int");
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
    if (value2 == 0) throw LotusException("Can`t divide by zero");

    return FLOAT(static_cast<double>(value) / value2);
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

Value lotus::IntValue::unaryPlus() {
	return INT(+value);
}

Value lotus::IntValue::unaryMinus() {
	return INT(-value);
}

Value lotus::IntValue::unaryNot() {
    return BOOL(!value);
}

