#include "structures/static.h"
#include "utils/lotusError.h"

using namespace lotus;

void lotus::Static::addField(const String& name, const FieldMemberInfo& memberInfo) {
	value.declareField(name, memberInfo);
}

void lotus::Static::addMethod(const String& name, const MethodMemberInfo& memberInfo) {
	value.declareMethod(name, memberInfo);
}

void lotus::Static::addField(const char* name, const FieldMemberInfo& memberInfo) {
	addField(STRING_VAR_LITERAL(name), memberInfo);
}

void lotus::Static::addMethod(const char* name, const MethodMemberInfo& memberInfo) {
	addMethod(STRING_VAR_LITERAL(name), memberInfo);
}

Value& lotus::Static::getField(const String& name) {
	return value.getField(name);
}

Value& lotus::Static::getField(const char* name) {
	return getField(STRING_VAR_LITERAL(name));
}

Value lotus::Static::callMethod(const String& name, const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs) {
	return value.callMethod(name, args, module, specifiedArgs);
}

Value lotus::Static::callMethod(const char* name, const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs) {
	return callMethod(STRING_VAR_LITERAL(name), args, module, specifiedArgs);
}
