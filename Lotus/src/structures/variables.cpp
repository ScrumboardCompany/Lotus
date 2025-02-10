#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

void Variables::declare(const String& name, const Value& value) {
	if (isExists(name)) {
		throw LotusException(STRING_LITERAL("Variable already exists"));
	}

	variables.emplace(name, value);
}

void Variables::set(const String& name, const Value& value) {
	if (isExists(name)) {
		variables[name] = value;
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined variable \"") + name + STRING_LITERAL("\""));
	}
}

Value lotus::Variables::get(const String& name) {
	if (isExists(name)) {
		return variables[name];
	}

	throw LotusException(STRING_LITERAL("Undefined variable \"") + name + STRING_LITERAL("\""));
}

bool lotus::Variables::isExists(const String& name) {
	return variables.find(name) != variables.end();
}
