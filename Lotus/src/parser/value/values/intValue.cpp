#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "utils/lotusError.h"

using namespace lotus;

IntValue::IntValue(int value) : value(value) {}

int lotus::IntValue::asInt() {
	return value;
}

double lotus::IntValue::asDouble() {
	return static_cast<double>(value);
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

Value lotus::IntValue::unary_plus() {
	return INT(+value);
}

Value lotus::IntValue::unary_minus() {
	return INT(-value);
}

