#include "structures/functions.h"
#include "utils/lotusError.h"

using namespace lotus;

void Functions::forceSet(const String& name, const Function& value) {
	for (auto& function : functions[name]) {
		if (function.getArgsCount() == value.getArgsCount()) {
			function = value;
			return;
		}
	}
	throw LotusException(STRING_LITERAL("No function overload for \"") + std::to_wstring(value.getArgsCount()) + STRING_LITERAL(" arguments found \""));
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
		throw LotusException(STRING_LITERAL("No overload with ") + std::to_wstring(value.getArgsCount()) + STRING_LITERAL(" arguments for \"") + name + STRING_LITERAL("\""));
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
		for (auto& function : functions[name]) {
			size_t test = function.getArgsCount();
			if (function.getArgsCount() == argsCount) return function;
		}
		throw LotusException(STRING_LITERAL("No overload with ") + std::to_wstring(argsCount) + STRING_LITERAL(" arguments for \"") + name + STRING_LITERAL("\""));
	}

	throw LotusException(STRING_LITERAL("Undefined function \"") + name + STRING_LITERAL("\""));
}

Function lotus::Functions::get(const char* name, size_t argsCount) {
	return get(STRING_VAR_LITERAL(name), argsCount);
}

Value lotus::Functions::call(const String& name, const std::vector<Value>& args, Variables& variables) {
	return get(name, args.size()).call(args, variables);
}

Value lotus::Functions::call(const char* name, const std::vector<Value>& args, Variables& variables) {
	return call(STRING_VAR_LITERAL(name), args, variables);
}

bool Functions::isExists(const String& name) {
	return functions.find(name) != functions.end();
}

bool lotus::Functions::isExists(const char* name) {
	return isExists(STRING_VAR_LITERAL(name));
}
