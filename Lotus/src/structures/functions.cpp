#include "structures/functions.h"
#include "utils/lotusError.h"

using namespace lotus;

void Functions::forceSet(const String& name, const Function& value) {
	functions[name].push_back(value);
}

void lotus::Functions::forceSet(const char* name, const Function& value) {
	forceSet(STRING_VAR_LITERAL(name), value);
}

void Functions::declare(const String& name, const Function& value) {
	if (isExists(name)) {

		for (auto& function : functions[name]) {
			if (function.getArgsCount() == value.getArgsCount()) throw LotusException(STRING_LITERAL("Function \"") + name + STRING_LITERAL("\" with ") + std::to_wstring(value.getArgsCount()) + STRING_LITERAL(" arguments already exists"));
		}

		functions[name].push_back(value);
	}
	else {
		functions.emplace(name, std::vector<Function>{value});
	}
}

void lotus::Functions::declare(const char* name, const Function& value) {
	declare(STRING_VAR_LITERAL(name), value);
}

void Functions::set(const String& name, const Function& value) {
	if (isExists(name)) {
		for (auto& function : functions[name]) {
			if (function.getArgsCount() == value.getArgsCount()) {
				function = value;
				return;
			}
		}
		throw LotusException(STRING_LITERAL("Undefined function \"") + name + STRING_LITERAL("\" with ") + std::to_wstring(value.getArgsCount()) + STRING_LITERAL(" arguments"));
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined function \"") + name + STRING_LITERAL("\""));
	}
}

void lotus::Functions::set(const char* name, const Function& value) {
	set(STRING_VAR_LITERAL(name), value);
}

Function Functions::get(const String& name, size_t argsCount) {

	if (isExists(name)) {

		Ptr<Function> variadic = nullptr;
		for (auto& function : functions[name]) {
			if (function.hasVariadic() && argsCount >= function.getArgsCount() - 1) variadic = MAKE_PTR<Function>(function);
			if (function.getArgsCount() == argsCount) return function;
		}

		if (variadic) {
			return *variadic;
		}
		throw LotusException(STRING_LITERAL("Undefined function \"") + name + STRING_LITERAL("\" with ") + std::to_wstring(argsCount) + STRING_LITERAL(" arguments"));
	}

	throw LotusException(STRING_LITERAL("Undefined function \"") + name + STRING_LITERAL("\""));
}

Function lotus::Functions::get(const char* name, size_t argsCount) {
	return get(STRING_VAR_LITERAL(name), argsCount);
}

Value lotus::Functions::call(const String& name, const std::vector<Value>& args, Module& module) {
	return get(name, args.size()).call(args, module);
}

Value lotus::Functions::call(const char* name, const std::vector<Value>& args, Module& module) {
	return call(STRING_VAR_LITERAL(name), args, module);
}

bool Functions::isExists(const String& name) {
	return functions.find(name) != functions.end();
}

bool lotus::Functions::isExists(const char* name) {
	return isExists(STRING_VAR_LITERAL(name));
}
