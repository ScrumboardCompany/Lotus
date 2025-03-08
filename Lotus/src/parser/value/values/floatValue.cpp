#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include "parser/function/function.h"
#include "structures/module.h"
#include <cmath>

using namespace lotus;

lotus::FloatValue::FloatValue(double value) : value(value) {
	type = STRING_LITERAL("float");
}

int lotus::FloatValue::asInt(Module&) {
	return static_cast<int>(value);
}

double lotus::FloatValue::asDouble(Module&) {
	return value;
}

bool lotus::FloatValue::asBool(Module&) {
	return static_cast<bool>(value);
}

String lotus::FloatValue::asString(Module&) {
	if (value == static_cast<int>(value)) {
		return std::to_wstring(static_cast<int>(value));
	}
	return std::to_wstring(value);
}

Value lotus::FloatValue::add(const Value& other, Module& module) {
	return FLOAT(value + other->asDouble(module));
}

Value lotus::FloatValue::substract(const Value& other, Module& module) {
	return FLOAT(value - other->asDouble(module));
}

Value lotus::FloatValue::multiply(const Value& other, Module& module) {
	return FLOAT(value * other->asDouble(module));
}

Value lotus::FloatValue::divide(const Value& other, Module& module) {
	double value2 = other->asDouble(module);
	if (value2 == 0) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t divide by zero"));
	return FLOAT(value / value2);
}

Value lotus::FloatValue::power(const Value& other, Module& module) {
	return FLOAT(pow(value, other->asDouble(module)));
}

Value lotus::FloatValue::divideModule(const Value&, Module&) {
	throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t use module operator over float type"));
}

Value lotus::FloatValue::greater(const Value& other, Module& module) {
	return BOOL(value > other->asDouble(module));
}

Value lotus::FloatValue::less(const Value& other, Module& module) {
	return BOOL(value < other->asDouble(module));
}

Value lotus::FloatValue::greaterEqual(const Value& other, Module& module) {
	return BOOL(value >= other->asDouble(module));
}

Value lotus::FloatValue::lessEqual(const Value& other, Module& module) {
	return BOOL(value <= other->asDouble(module));
}

Value lotus::FloatValue::equality(const Value& other, Module& module) {
	return BOOL(value == other->asDouble(module));
}

Value lotus::FloatValue::inequality(const Value& other, Module& module) {
	return BOOL(value != other->asDouble(module));
}

Value lotus::FloatValue::logicalOr(const Value& other, Module& module) {
	return BOOL(asBool(module) || other->asBool(module));
}

Value lotus::FloatValue::logicalAnd(const Value& other, Module& module) {
	return BOOL(asBool(module) && other->asBool(module));
}

Value lotus::FloatValue::addSet(const Value& other, Module& module) {
	value = add(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::substractSet(const Value& other, Module& module) {
	value = substract(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::multiplySet(const Value& other, Module& module) {
	value = multiply(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::divideSet(const Value& other, Module& module) {
	value = divide(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::powerSet(const Value& other, Module& module) {
	value = power(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::divideModuleSet(const Value& other, Module& module) {
	value = divideModule(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::unaryPlus(Module&) {
	return FLOAT(+value);
}

Value lotus::FloatValue::unaryMinus(Module&) {
	return FLOAT(-value);
}

Value lotus::FloatValue::unaryNot(Module&) {
	return BOOL(!value);
}

Value lotus::FloatValue::prefixIncrement(Module&) {
	return FLOAT(++value);
}

Value lotus::FloatValue::postfixIncrement(Module&) {
	return FLOAT(value++);
}

Value lotus::FloatValue::prefixDecrement(Module&) {
	return FLOAT(--value);
}

Value lotus::FloatValue::postfixDecrement(Module&) {
	return FLOAT(value--);
}

Value lotus::FloatValue::sizeInRam() {
	return INT(static_cast<int>(sizeof(FloatValue)));
}