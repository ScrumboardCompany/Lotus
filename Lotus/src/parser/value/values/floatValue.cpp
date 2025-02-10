#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"

using namespace lotus;

lotus::FloatValue::FloatValue(double value) : value(value) {}

int lotus::FloatValue::asInt() {
	return static_cast<int>(value);
}

double lotus::FloatValue::asDouble() {
	return value;
}

bool lotus::FloatValue::asBool() {
	return static_cast<bool>(value);
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
	if (value2 == 0) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t divide by zero"));
	return FLOAT(value / value2);
}

Value lotus::FloatValue::greater(const Value& other) {
	return BOOL(value > other->asDouble());
}

Value lotus::FloatValue::less(const Value& other) {
	return BOOL(value < other->asDouble());
}

Value lotus::FloatValue::greaterEqual(const Value& other) {
	return BOOL(value >= other->asDouble());
}

Value lotus::FloatValue::lessEqual(const Value& other) {
	return BOOL(value <= other->asDouble());
}

Value lotus::FloatValue::equality(const Value& other) {
	return BOOL(value == other->asDouble());
}

Value lotus::FloatValue::inequality(const Value& other) {
	return BOOL(value != other->asDouble());
}

Value lotus::FloatValue::logicalOr(const Value& other) {
	return BOOL(asBool() || other->asBool());
}

Value lotus::FloatValue::logicalAnd(const Value& other) {
	return BOOL(asBool() && other->asBool());
}

Value lotus::FloatValue::unaryPlus() {
	return FLOAT(+value);
}

Value lotus::FloatValue::unaryMinus() {
	return FLOAT(-value);
}

Value lotus::FloatValue::unaryNot() {
	return BOOL(!value);
}

