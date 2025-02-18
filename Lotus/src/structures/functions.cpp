#include "structures/functions.h"
#include "utils/lotusError.h"

using namespace lotus;

void Functions::forceDeclareOrSet(const String& name, const Function& value) {
	functions[name] = value;
}

void lotus::Functions::forceDeclareOrSet(const char* name, const Function& value) {
	forceDeclareOrSet(STRING_VAR_LITERAL(name), value);
}

void Functions::declare(const String& name, const Function& value) {
	if (isExists(name)) {
		throw LotusException(STRING_LITERAL("Function \"") + name + STRING_LITERAL("\" already exists"));
	}

	functions.emplace(name, value);
}

void lotus::Functions::declare(const char* name, const Function& value) {
	declare(STRING_VAR_LITERAL(name), value);
}

void Functions::set(const String& name, const Function& value) {
	if (isExists(name)) {
		functions[name] = value;
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined function \"") + name + STRING_LITERAL("\""));
	}
}

void lotus::Functions::set(const char* name, const Function& value) {
	set(STRING_VAR_LITERAL(name), value);
}

Function Functions::get(const String& name) {
	if (isExists(name)) {
		return functions[name];
	}

	throw LotusException(STRING_LITERAL("Undefined function \"") + name + STRING_LITERAL("\""));
}

Function lotus::Functions::get(const char* name) {
	return get(STRING_VAR_LITERAL(name));
}

Value lotus::Functions::call(const String& name, const std::vector<Value>& args, Variables& variables) {
	return get(name).call(args, variables);
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
