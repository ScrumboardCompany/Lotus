#include "structures/enums.h"
#include "utils/lotusError.h"

using namespace lotus;

void lotus::Enums::forceSet(const String& name, const Enum& value) {
	enums[name] = value;
}

void lotus::Enums::forceSet(const char* name, const Enum& value) {
	forceSet(STRING_VAR_LITERAL(name), value);
}

void lotus::Enums::declare(const String& name, const Enum& value) {
	if (isExists(name)) {
		throw LotusException(STRING_LITERAL("Enum \"") + name + STRING_LITERAL("\" already exists"));
	}

	enums.emplace(name, value);
}

void lotus::Enums::declare(const char* name, const Enum& value) {
	declare(STRING_VAR_LITERAL(name), value);
}

void lotus::Enums::set(const String& name, const Enum& value) {
	if (isExists(name)) {
		enums[name] = value;
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined enum \"") + name + STRING_LITERAL("\""));
	}
}

void lotus::Enums::set(const char* name, const Enum& value) {
	set(STRING_VAR_LITERAL(name), value);
}

Enum& lotus::Enums::get(const String& name) {
	if (isExists(name)) {
		return enums[name];
	}

	throw LotusException(STRING_LITERAL("Undefined enum \"") + name + STRING_LITERAL("\""));
}

Enum& lotus::Enums::get(const char* name) {
	return get(STRING_VAR_LITERAL(name));
}

bool lotus::Enums::isExists(const String& name) {
	return enums.find(name) != enums.end();
}

bool lotus::Enums::isExists(const char* name) {
	return isExists(STRING_VAR_LITERAL(name));
}