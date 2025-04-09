#include "structures/classes.h"
#include "utils/lotusError.h"

using namespace lotus;

void lotus::Classes::forceSet(const String& name, const Ptr<Class>& value) {
	classes[name] = value;
	classes[name]->setName(name);
}

void lotus::Classes::forceSet(const char* name, const Ptr<Class>& value) {
	forceSet(STRING_VAR_LITERAL(name), value);
}

void lotus::Classes::declare(const String& name, const Ptr<Class>& value) {
	if (isExists(name)) {
		throw LotusException(STRING_LITERAL("Class \"") + name + STRING_LITERAL("\" already exists"));
	}

	forceSet(name, value);
}

void lotus::Classes::declare(const char* name, const Ptr<Class>& value) {
	declare(STRING_VAR_LITERAL(name), value);
}

void lotus::Classes::set(const String& name, const Ptr<Class>& value) {
	if (isExists(name)) {
		forceSet(name, value);
	}
	else {
		throw LotusException(STRING_LITERAL("Undefined class \"") + name + STRING_LITERAL("\""));
	}
}

void lotus::Classes::set(const char* name, const Ptr<Class>& value) {
	set(STRING_VAR_LITERAL(name), value);
}

Ptr<Class> lotus::Classes::get(const String& name) {
	if (isExists(name)) {
		return classes[name];
	}

	throw LotusException(STRING_LITERAL("Undefined class \"") + name + STRING_LITERAL("\""));
}

Ptr<Class> lotus::Classes::get(const char* name) {
	return get(STRING_VAR_LITERAL(name));
}

bool lotus::Classes::isExists(const String& name) {
	return classes.find(name) != classes.end();
}

bool lotus::Classes::isExists(const char* name) {
	return isExists(STRING_VAR_LITERAL(name));
}

void lotus::Classes::registerClass(const String& name, Module& module) {
	if (isExists(name)) {
		classes[name]->registerClass(module);
		return;
	}

	throw LotusException(STRING_LITERAL("Undefined class \"") + name + STRING_LITERAL("\""));
}

void lotus::Classes::registerClass(const char* name, Module& module) {
	registerClass(STRING_VAR_LITERAL(name), module);
}