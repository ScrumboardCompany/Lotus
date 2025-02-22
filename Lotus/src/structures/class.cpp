#include "structures/class.h"
#include "structures/functions.h"
#include "parser/function/function.h"
#include "parser/statement/cppFunctionStatement.h"
#include "structures/classes.h"

using namespace lotus;

Function lotus::Class::makeDefaultConstructor() {
	Function defaultConstructor(MAKE_PTR<CppFunctionStatement>([&]() {
		RETURN_VALUE(MAKE_PTR<ClassValue>(value));
		}), {});

	return defaultConstructor;
}

void lotus::Class::registerClass(Functions& functions, Variables& variables) {
	String name = value.getType();
	if (value.methods.find(name) != value.methods.end()) {
		for (auto& method : value.methods[name]) {

			Function constructor(MAKE_PTR<CppFunctionStatement>([&]() {

				std::vector<Value> argsValues;
				for (auto& arg : method.value.args) {
					argsValues.push_back(variables.get(arg.name));
				}
				value.callMethod(value.getType(), argsValues, variables);

				RETURN_VALUE(MAKE_PTR<ClassValue>(value));
				}), method.value.args);

			functions.declare(name, constructor);
		}
	}
	else functions.declare(name, makeDefaultConstructor());
}

void lotus::Class::setName(const String& name) {
	value.type = name;
}

void lotus::Class::setName(const char* name) {
	setName(STRING_VAR_LITERAL(name));
}

void lotus::Class::addField(const String& name, const FieldMemberInfo& memberInfo) {
	value.declareField(name, memberInfo);
}

void lotus::Class::addMethod(const String& name, const MethodMemberInfo& memberInfo) {
	value.declareMethod(name, memberInfo);
}

void lotus::Class::addField(const char* name, const FieldMemberInfo& memberInfo) {
	addField(STRING_VAR_LITERAL(name), memberInfo);
}

void lotus::Class::addMethod(const char* name, const MethodMemberInfo& memberInfo) {
	addMethod(STRING_VAR_LITERAL(name), memberInfo);
}

Value& lotus::Class::getField(const String& name) {
	return value.getField(name);
}

Value& lotus::Class::getField(const char* name) {
	return getField(STRING_VAR_LITERAL(name));
}

Value lotus::Class::callMethod(const String& name, const std::vector<Value>& args, Variables& variables) {
	return value.callMethod(name, args, variables);
}

Value lotus::Class::callMethod(const char* name, const std::vector<Value>& args, Variables& variables) {
	return callMethod(STRING_VAR_LITERAL(name), args, variables);
}