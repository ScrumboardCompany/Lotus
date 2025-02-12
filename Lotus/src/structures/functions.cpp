#include "structures/functions.h"
#include "utils/lotusError.h"

using namespace lotus;

void Functions::forceDeclareOrSet(const String& name, const Function& value) {
	functions[name] = value;
}

void Functions::declare(const String& name, const Function& value) {
	if (isExists(name)) {
		throw LotusException(STRING_LITERAL("Variable already exists"));
	}

	functions.emplace(name, value);
}

void Functions::set(const String& name, const Function& value) {
	if (isExists(name)) {
		functions[name] = value;
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined variable \"") + name + STRING_LITERAL("\""));
	}
}

Function Functions::get(const String& name) {
	if (isExists(name)) {
		return functions[name];
	}

	throw LotusException(STRING_LITERAL("Undefined variable \"") + name + STRING_LITERAL("\""));
}

bool Functions::isExists(const String& name) {
	return functions.find(name) != functions.end();
}