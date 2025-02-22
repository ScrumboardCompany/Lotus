#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include "parser/function/function.h"
#include <cmath>

using namespace lotus;

lotus::FloatValue::FloatValue(double value) : value(value) {
	type = STRING_LITERAL("float");
}

int lotus::FloatValue::asInt(Variables& variables) {
	return static_cast<int>(value);
}

double lotus::FloatValue::asDouble(Variables& variables) {
	return value;
}

bool lotus::FloatValue::asBool(Variables& variables) {
	return static_cast<bool>(value);
}

String lotus::FloatValue::asString(Variables& variables) {
	return std::to_wstring(value);
}

Value lotus::FloatValue::add(const Value& other, Variables& variables) {
	return FLOAT(value + other->asDouble(variables));
}

Value lotus::FloatValue::substract(const Value& other, Variables& variables) {
	return FLOAT(value - other->asDouble(variables));
}

Value lotus::FloatValue::multiply(const Value& other, Variables& variables) {
	return FLOAT(value * other->asDouble(variables));
}

Value lotus::FloatValue::divide(const Value& other, Variables& variables) {
	double value2 = other->asDouble(variables);
	if (value2 == 0) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t divide by zero"));
	return FLOAT(value / value2);
}

Value lotus::FloatValue::power(const Value& other, Variables& variables) {
	return FLOAT(pow(value, other->asDouble(variables)));
}

Value lotus::FloatValue::divideModule(const Value& other, Variables& variables) {
	throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t use module operator over float type"));
}

Value lotus::FloatValue::greater(const Value& other, Variables& variables) {
	return BOOL(value > other->asDouble(variables));
}

Value lotus::FloatValue::less(const Value& other, Variables& variables) {
	return BOOL(value < other->asDouble(variables));
}

Value lotus::FloatValue::greaterEqual(const Value& other, Variables& variables) {
	return BOOL(value >= other->asDouble(variables));
}

Value lotus::FloatValue::lessEqual(const Value& other, Variables& variables) {
	return BOOL(value <= other->asDouble(variables));
}

Value lotus::FloatValue::equality(const Value& other, Variables& variables) {
	return BOOL(value == other->asDouble(variables));
}

Value lotus::FloatValue::inequality(const Value& other, Variables& variables) {
	return BOOL(value != other->asDouble(variables));
}

Value lotus::FloatValue::logicalOr(const Value& other, Variables& variables) {
	return BOOL(asBool(variables) || other->asBool(variables));
}

Value lotus::FloatValue::logicalAnd(const Value& other, Variables& variables) {
	return BOOL(asBool(variables) && other->asBool(variables));
}

Value lotus::FloatValue::addSet(const Value& other, Variables& variables) {
	value = add(other, variables)->asDouble(variables);
	return FLOAT(value);
}

Value lotus::FloatValue::substractSet(const Value& other, Variables& variables) {
	value = substract(other, variables)->asDouble(variables);
	return FLOAT(value);
}

Value lotus::FloatValue::multiplySet(const Value& other, Variables& variables) {
	value = multiply(other, variables)->asDouble(variables);
	return FLOAT(value);
}

Value lotus::FloatValue::divideSet(const Value& other, Variables& variables) {
	value = divide(other, variables)->asDouble(variables);
	return FLOAT(value);
}

Value lotus::FloatValue::powerSet(const Value& other, Variables& variables) {
	value = power(other, variables)->asDouble(variables);
	return FLOAT(value);
}

Value lotus::FloatValue::divideModuleSet(const Value& other, Variables& variables) {
	value = divideModule(other, variables)->asDouble(variables);
	return FLOAT(value);
}

Value lotus::FloatValue::unaryPlus(Variables& variables) {
	return FLOAT(+value);
}

Value lotus::FloatValue::unaryMinus(Variables& variables) {
	return FLOAT(-value);
}

Value lotus::FloatValue::unaryNot(Variables& variables) {
	return BOOL(!value);
}

Value lotus::FloatValue::prefixIncrement(Variables& variables) {
	return FLOAT(++value);
}

Value lotus::FloatValue::postfixIncrement(Variables& variables) {
	return FLOAT(value++);
}

Value lotus::FloatValue::prefixDecrement(Variables& variables) {
	return FLOAT(--value);
}

Value lotus::FloatValue::postfixDecrement(Variables& variables) {
	return FLOAT(value--);
}

Value lotus::FloatValue::sizeInRam() {
	return INT(sizeof(FloatValue));
}