#include "structures/static.h"
#include "utils/lotusError.h"

using namespace lotus;

void lotus::Static::addField(const String& name, const FieldMemberInfo& memberInfo) {
	fields.emplace(name, memberInfo);
}

void lotus::Static::addMethod(const String& name, const MethodMemberInfo& memberInfo) {
	if (methods.find(name) != methods.end()) {
		for (auto& method : methods[name]) {
			if (method.value.getArgsCount() == memberInfo.value.getArgsCount()) throw LotusException(STRING_LITERAL("Method \"") + name + STRING_LITERAL("\" with ") + std::to_wstring(memberInfo.value.getArgsCount()) + STRING_LITERAL(" arguments already exists"));
		}

		methods[name].push_back(memberInfo);
	}
	else methods.emplace(name, std::vector<MethodMemberInfo>{memberInfo});
}

void lotus::Static::addField(const char* name, const FieldMemberInfo& memberInfo) {
	addField(STRING_VAR_LITERAL(name), memberInfo);
}

void lotus::Static::addMethod(const char* name, const MethodMemberInfo& memberInfo) {
	addMethod(STRING_VAR_LITERAL(name), memberInfo);
}

Value& lotus::Static::getField(const String& name) {
	if (fields.find(name) == fields.end()) throw LotusException(STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" doesn`t exist"));
	
	if (fields[name].accessModifier == AccessModifierType::PRIVATE) {
		throw LotusException(STRING_LITERAL("Request to private field: \"") + name + STRING_LITERAL("\""));
	}

	return fields[name].value;
}

Value& lotus::Static::getField(const char* name) {
	return getField(STRING_VAR_LITERAL(name));
}

Value lotus::Static::callMethod(const String& name, const std::vector<Value>& args, Variables& variables) {
	if (methods.find(name) == methods.end()) throw LotusException(STRING_LITERAL("Method \"") + name + STRING_LITERAL("\" doesn`t exist"));

	bool hasOverload = false;

	for (auto& method : methods[name]) {
		if (method.value.getArgsCount() == args.size()) {
			hasOverload = true;
			if (method.accessModifier == AccessModifierType::PRIVATE) {
				throw LotusException(STRING_LITERAL("Request to private method: \"") + name + STRING_LITERAL("\""));
			}
		}
	}

	if (!hasOverload) throw LotusException(STRING_LITERAL("No overload with ") + std::to_wstring(args.size()) + STRING_LITERAL(" arguments for \"") + name + STRING_LITERAL("\""));

	Value returnValue = nullptr;

	for (auto& method : methods[name]) {
		if (method.value.getArgsCount() == args.size()) {
			returnValue = method.value.call(args, variables);
		}
	}

	return returnValue;
}

Value lotus::Static::callMethod(const char* name, const std::vector<Value>& args, Variables& variables) {
	return callMethod(STRING_VAR_LITERAL(name), args, variables);
}
