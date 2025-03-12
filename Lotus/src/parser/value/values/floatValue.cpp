#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "utils/utils.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include "parser/function/function.h"
#include "structures/module.h"
#include <cmath>

using namespace lotus;

lotus::FloatValue::FloatValue(double value) : value(value) {
	type = STRING_LITERAL("float");
}

Int lotus::FloatValue::asInt(Module&) {
	return static_cast<Int>(value);
}

double lotus::FloatValue::asDouble(Module&) {
	return value;
}

bool lotus::FloatValue::asBool(Module&) {
	return static_cast<bool>(value);
}

String lotus::FloatValue::asString(Module&) {
	if (value == static_cast<Int>(value)) {
		return std::to_wstring(static_cast<Int>(value));
	}
	return std::to_wstring(value);
}

Value lotus::FloatValue::add(const Value& other, Module& module) {
	if(!isNumber(other)) throwOverloadError(STRING_LITERAL("add"), getType(), other->getType());
	return FLOAT(value + other->asDouble(module));
}

Value lotus::FloatValue::substract(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("substract"), getType(), other->getType());
	return FLOAT(value - other->asDouble(module));
}

Value lotus::FloatValue::multiply(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
	return FLOAT(value * other->asDouble(module));
}

Value lotus::FloatValue::divide(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("divide"), getType(), other->getType());
	double value2 = other->asDouble(module);
	if (value2 == 0) throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t divide by zero"));
	return FLOAT(value / value2);
}

Value lotus::FloatValue::power(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("power"), getType(), other->getType());
	return FLOAT(pow(value, other->asDouble(module)));
}

Value lotus::FloatValue::divideModule(const Value&, Module&) {
	throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Can`t use module operator over float type"));
}

Value lotus::FloatValue::greater(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("greater"), getType(), other->getType());
	return BOOL(value > other->asDouble(module));
}

Value lotus::FloatValue::less(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("less"), getType(), other->getType());
	return BOOL(value < other->asDouble(module));
}

Value lotus::FloatValue::greaterEqual(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("greaterEqual"), getType(), other->getType());
	return BOOL(value >= other->asDouble(module));
}

Value lotus::FloatValue::lessEqual(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("lessEqual"), getType(), other->getType());
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
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("addSet"), getType(), other->getType());
	value = add(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::substractSet(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("substractSet"), getType(), other->getType());
	value = substract(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::multiplySet(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("multiplySet"), getType(), other->getType());
	value = multiply(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::divideSet(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("divideSet"), getType(), other->getType());
	value = divide(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::powerSet(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("powerSet"), getType(), other->getType());
	value = power(other, module)->asDouble(module);
	return FLOAT(value);
}

Value lotus::FloatValue::divideModuleSet(const Value& other, Module& module) {
	if (!isNumber(other)) throwOverloadError(STRING_LITERAL("divideModuleSet"), getType(), other->getType());
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
	return INT(static_cast<Int>(sizeof(*this)));
}