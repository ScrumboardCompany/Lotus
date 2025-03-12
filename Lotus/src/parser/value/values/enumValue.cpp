#include "parser/value/enumValue.h"
#include "utils/lotusError.h"
#include "parser/value/intValue.h"
#include "parser/value/boolValue.h"


using namespace lotus;

Value lotus::EnumValue::checkIsEnumAndCompare(const Value& other, Module& module, const std::function<Value(EnumValue, Module&)>& operation) {
	if (!other->instanceOf(getType())) throw LotusException(STRING_LITERAL("Cannot compare different enums"));

	if (auto enumValue = std::dynamic_pointer_cast<EnumValue>(other)) {
		return operation(*enumValue, module);
	}
	throw LotusException(STRING_LITERAL("Cannot compare enum and not enum"));
}

lotus::EnumValue::EnumValue(const Value& value, const String& type) : value(value) {
	this->type = type;
}

Int lotus::EnumValue::asInt(Module& module) {
	if (value->instanceOf("int")) {
		return value->asInt(module);
	}
	throw LotusException(STRING_LITERAL("Element type isn`t int"));
}

String lotus::EnumValue::asString(Module& module) {
	if (value->instanceOf("string")) {
		return value->asString(module);
	}
	throw LotusException(STRING_LITERAL("Element type isn`t string"));
}

Value lotus::EnumValue::greater(const Value& other, Module& module) {
	return checkIsEnumAndCompare(other, module, [this](EnumValue enumValue, Module& module) -> Value {
		return value->greater(enumValue.value, module);
		});
}

Value lotus::EnumValue::less(const Value& other, Module& module) {
	return checkIsEnumAndCompare(other, module, [this](EnumValue enumValue, Module& module) -> Value {
		return value->less(enumValue.value, module);
		});
}

Value lotus::EnumValue::greaterEqual(const Value& other, Module& module) {
	return checkIsEnumAndCompare(other, module, [this](EnumValue enumValue, Module& module) -> Value {
		return value->greaterEqual(enumValue.value, module);
		});
}

Value lotus::EnumValue::lessEqual(const Value& other, Module& module) {
	return checkIsEnumAndCompare(other, module, [this](EnumValue enumValue, Module& module) -> Value {
		return value->lessEqual(enumValue.value, module);
		});
}

Value lotus::EnumValue::equality(const Value& other, Module& module) {
	return checkIsEnumAndCompare(other, module, [this](EnumValue enumValue, Module& module) -> Value {
		return value->equality(enumValue.value, module);
		});
}

Value lotus::EnumValue::inequality(const Value& other, Module& module) {
	return checkIsEnumAndCompare(other, module, [this](EnumValue enumValue, Module& module) -> Value {
		return value->inequality(enumValue.value, module);
		});
}

Value lotus::EnumValue::logicalOr(const Value& other, Module& module) {
	return checkIsEnumAndCompare(other, module, [this](EnumValue enumValue, Module& module) -> Value {
		return value->logicalOr(enumValue.value, module);
		});
}

Value lotus::EnumValue::logicalAnd(const Value& other, Module& module) {
	return checkIsEnumAndCompare(other, module, [this](EnumValue enumValue, Module& module) -> Value {
		return value->logicalAnd(enumValue.value, module);
		});
}

Value lotus::EnumValue::sizeInRam() {
	return INT(static_cast<Int>(sizeof(*this)));
}