#include "structures/class.h"
#include "structures/functions.h"
#include "parser/function/function.h"
#include "parser/statement/cppFunctionStatement.h"
#include "structures/module.h"

using namespace lotus;

Function lotus::Class::makeDefaultConstructor() {
	Function defaultConstructor(MAKE_PTR<CppFunctionStatement>([&]() {
		RETURN_VALUE(MAKE_PTR<ClassValue>(value));
		}), {});

	return defaultConstructor;
}

void lotus::Class::setName(const String& name) {
	value.type = name;
}

void lotus::Class::setName(const char* name) {
	setName(STRING_VAR_LITERAL(name));
}

void lotus::Class::registerClass(Module& module) {
	String name = value.getType();
	if (value.methods.find(name) != value.methods.end()) {
		for (auto& method : value.methods[name]) {

			Function constructor(MAKE_PTR<CppFunctionStatement>([&]() {

				std::vector<Value> argsValues;
				for (auto& arg : method.value.args) {
					argsValues.push_back(module.variables.get(arg.name));
				}
				value.callMethod(value.getType(), argsValues, module);

				RETURN_VALUE(MAKE_PTR<ClassValue>(value));
				}), method.value.args);

			module.functions.forceSet(name, constructor);
		}
	}
	else module.functions.forceSet(name, makeDefaultConstructor());
}