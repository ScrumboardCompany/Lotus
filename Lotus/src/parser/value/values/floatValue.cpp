#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/value/floatValue.h"

using namespace lotus;

lotus::FloatValue::FloatValue(double value) : value(value) {}

int lotus::FloatValue::asInt() {
	return static_cast<int>(value);
}

double lotus::FloatValue::asDouble() {
	return value;
}

String lotus::FloatValue::asString() {
	return std::to_wstring(value);
}

String lotus::FloatValue::getType() const {
	return STRING_LITERAL("float");
}

Value lotus::FloatValue::add(const Value& other) {
	return FLOAT(value + other->asDouble());
}

Value lotus::FloatValue::substract(const Value& other) {
	return FLOAT(value - other->asDouble());
}

Value lotus::FloatValue::multiply(const Value& other) {
	return FLOAT(value * other->asDouble());
}

Value lotus::FloatValue::divide(const Value& other) {
	double value2 = other->asDouble();
	if (value2 == 0) throw LotusException("Can`t divide by zero");
	return FLOAT(value / value2);
}

Value lotus::FloatValue::unary_plus() {
	return FLOAT(+value);
}

Value lotus::FloatValue::unary_minus() {
	return FLOAT(-value);
}

