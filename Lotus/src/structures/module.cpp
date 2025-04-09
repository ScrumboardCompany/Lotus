#include "structures/module.h"
#include "utils/utils.h"
#include "parser/value/stringValue.h"

using namespace lotus;

FieldMemberInfo lotus::FIELD(const AccessModifierType& accessModifier, const Value& value) {
	return FieldMemberInfo(value, accessModifier);
}

void lotus::Module::LET(const String& name, const Value& value) {
	variables.declare(name, value);
}

void lotus::Module::LET(const char* name, const Value& value) {
	LET(STRING_VAR_LITERAL(name), value);
}

void lotus::Module::SET(const String& name, const Value& value) {
	variables.set(name, value);
}

void lotus::Module::SET(const char* name, const Value& value) {
	SET(STRING_VAR_LITERAL(name), value);
}

Value& lotus::Module::GET(const String& name) {
	return variables.get(name);
}

Value& lotus::Module::GET(const char* name) {
	return GET(STRING_VAR_LITERAL(name));
}

Value& lotus::Module::STATIC_FIELD(const String& name, const String& element) {
	return statics.get(name).getField(element);
}

Value& lotus::Module::STATIC_FIELD(const char* name, const String& element) {
	return STATIC_FIELD(STRING_VAR_LITERAL(name), element);
}

Value& lotus::Module::STATIC_FIELD(const char* name, const char* element) {
	return STATIC_FIELD(STRING_VAR_LITERAL(name), STRING_VAR_LITERAL(element));
}

Value lotus::Module::STATIC_METHOD_WITH_SPECIFIED_ARGS(const String& name, const String& element,
	const std::vector<Value>& args, const StringMap<Value>& specifiedArgs) {
	return statics.get(name).callMethod(element, args, *this, specifiedArgs);
}

Value lotus::Module::STATIC_METHOD_WITH_SPECIFIED_ARGS(const char* name, const String& element,
	const std::vector<Value>& args, const StringMap<Value>& specifiedArgs) {
	return STATIC_METHOD_WITH_SPECIFIED_ARGS(STRING_VAR_LITERAL(name), element, args, specifiedArgs);
}

Value lotus::Module::STATIC_METHOD_WITH_SPECIFIED_ARGS(const char* name, const char* element,
	const std::vector<Value>& args, const StringMap<Value>& specifiedArgs) {
	return STATIC_METHOD_WITH_SPECIFIED_ARGS(STRING_VAR_LITERAL(name), STRING_VAR_LITERAL(element), args, specifiedArgs);
}

Value lotus::Module::ENUM_ELEMENT(const String& name, const String& element) {
	return MAKE_PTR<EnumValue>(enums.get(name).getElement(element), name);
}

Value lotus::Module::ENUM_ELEMENT(const char* name, const String& element) {
	return ENUM_ELEMENT(STRING_VAR_LITERAL(name), element);
}

Value lotus::Module::ENUM_ELEMENT(const char* name, const char* element) {
	return ENUM_ELEMENT(STRING_VAR_LITERAL(name), STRING_VAR_LITERAL(element));
}

void lotus::Module::STATIC(const String& name, const Static& value) {
	statics.declare(name, value);
}

void lotus::Module::STATIC(const char* name, const Static& value) {
	STATIC(STRING_VAR_LITERAL(name), value);
}

void lotus::Module::CLASS(const String& name, const Class& value) {
	classes.declare(name, MAKE_PTR<Class>(value));
	classes.registerClass(name, *this);
}

void lotus::Module::CLASS(const char* name, const Class& value) {
	CLASS(STRING_VAR_LITERAL(name), value);
}

void lotus::Module::ENUM(const String& name, const Enum& value) {
	enums.declare(name, value);
}

void lotus::Module::ENUM(const char* name, const Enum& value) {
	ENUM(STRING_VAR_LITERAL(name), value);
}

void lotus::Module::THROW() {
	throw ThrowValue(CALL("exception"));
}

void lotus::Module::THROW(const Value& msg) {
	throw ThrowValue(CALL("exception", msg));
}

void lotus::Module::THROW(const Value& msg, const Value& type) {
	throw ThrowValue(CALL("exception", msg, type));
}