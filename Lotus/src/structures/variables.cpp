#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

void Variables::forceDeclareOrSet(const String& name, const Value& value) {
	variables[name] = value;
}

void lotus::Variables::forceDeclareOrSet(const char* name, const Value& value) {
	forceDeclareOrSet(STRING_VAR_LITERAL(name), value);
}

void Variables::declare(const String& name, const Value& value) {
	if (isExists(name)) {
		throw LotusException(STRING_LITERAL("Variable \"") + name + STRING_LITERAL("\" already exists"));
	}

	variables.emplace(name, value);
}

void lotus::Variables::declare(const char* name, const Value& value) {
	declare(STRING_VAR_LITERAL(name), value);
}

void Variables::set(const String& name, const Value& value) {
	if (isExists(name)) {
		variables[name] = value;
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined variable \"") + name + STRING_LITERAL("\""));
	}
}

void lotus::Variables::set(const char* name, const Value& value) {
	set(STRING_VAR_LITERAL(name), value);
}

Value& lotus::Variables::get(const String& name) {
	if (isExists(name)) {
		return variables[name];
	}

	throw LotusException(STRING_LITERAL("Undefined variable \"") + name + STRING_LITERAL("\""));
}

Value& lotus::Variables::get(const char* name) {
	return get(STRING_VAR_LITERAL(name));
}

bool lotus::Variables::isExists(const String& name) {
	return variables.find(name) != variables.end();
}

bool lotus::Variables::isExists(const char* name) {
	return isExists(STRING_VAR_LITERAL(name));
}

void lotus::Variables::saveState() {
	savedStates.push(variables);
}

void lotus::Variables::restoreState() {
	if (!savedStates.empty()) {
		variables = savedStates.top();
		savedStates.pop();
	}
	else {
		throw LotusException(STRING_LITERAL("No saved state to restore"));
	}
}