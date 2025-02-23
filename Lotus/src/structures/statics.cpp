#include "structures/statics.h"
#include "utils/lotusError.h"

using namespace lotus;

void lotus::Statics::forceSet(const String& name, const Static& value) {
	statics[name] = value;
}

void lotus::Statics::forceSet(const char* name, const Static& value) {
	forceSet(STRING_VAR_LITERAL(name), value);
}

void lotus::Statics::declare(const String& name, const Static& value) {
	if (isExists(name)) {
		throw LotusException(STRING_LITERAL("Static \"") + name + STRING_LITERAL("\" already exists"));
	}

	statics.emplace(name, value);
}

void lotus::Statics::declare(const char* name, const Static& value) {
	declare(STRING_VAR_LITERAL(name), value);
}

void lotus::Statics::set(const String& name, const Static& value) {
	if (isExists(name)) {
		statics[name] = value;
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined static \"") + name + STRING_LITERAL("\""));
	}
}

void lotus::Statics::set(const char* name, const Static& value) {
	set(STRING_VAR_LITERAL(name), value);
}

Static& lotus::Statics::get(const String& name) {
	if (isExists(name)) {
		return statics[name];
	}

	throw LotusException(STRING_LITERAL("Undefined static \"") + name + STRING_LITERAL("\""));
}

Static& lotus::Statics::get(const char* name) {
	return get(STRING_VAR_LITERAL(name));
}

bool lotus::Statics::isExists(const String& name) {
	return statics.find(name) != statics.end();
}

bool lotus::Statics::isExists(const char* name) {
	return isExists(STRING_VAR_LITERAL(name));
}