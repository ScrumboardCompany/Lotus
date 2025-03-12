#include "structures/variables.h"
#include "utils/lotusError.h"

using namespace lotus;

void Variables::forceSet(const String& name, const Value& value) {
	if (name == STRING_LITERAL("__file__") || name == STRING_LITERAL("__path__") || name == STRING_LITERAL("__time__") || name == STRING_LITERAL("__version__")) {
		if (scopes.empty()) {
			if (variables.find(name) == variables.end()) {
				variables[name] = value;
			}
		}
		else {
			if (scopes.back().find(name) == scopes.back().end()) {
				scopes.back()[name] = value;
			}
		}
	}
	else {
		if (scopes.empty()) {
			variables[name] = value;
		}
		else {
			scopes.back()[name] = value;
		}
	}
}

void Variables::forceSet(const char* name, const Value& value) {
	forceSet(STRING_VAR_LITERAL(name), value);
}

void Variables::declare(const String& name, const Value& value) {
	if (scopes.back().count(name) > 0) {
		throw LotusException(STRING_LITERAL("Variable \"") + name + STRING_LITERAL("\" already exists in this scope"));
	}

	scopes.back()[name] = value;
}

void Variables::declare(const char* name, const Value& value) {
	declare(STRING_VAR_LITERAL(name), value);
}

void Variables::set(const String& name, const Value& value) {
	for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
		if (it->count(name) > 0) {
			(*it)[name] = value;
			return;
		}
	}

	if (variables.count(name) > 0) {
		variables[name] = value;
		return;
	}

	throw LotusException(STRING_LITERAL("Undefined variable \"") + name + STRING_LITERAL("\""));
}

void Variables::set(const char* name, const Value& value) {
	set(STRING_VAR_LITERAL(name), value);
}

Value& Variables::get(const String& name) {
	for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
		if (it->count(name) > 0) {
			return (*it)[name];
		}
	}

	if (variables.count(name) > 0) {
		return variables[name];
	}

	throw LotusException(STRING_LITERAL("Undefined variable \"") + name + STRING_LITERAL("\""));
}

Value& Variables::get(const char* name) {
	return get(STRING_VAR_LITERAL(name));
}

bool Variables::isExists(const String& name) const {
	for (auto it = scopes.rbegin(); it != scopes.rend(); ++it) {
		if (it->count(name) > 0) {
			return true;
		}
	}

	return variables.count(name) > 0;
}

bool Variables::isExists(const char* name) const {
	return isExists(STRING_VAR_LITERAL(name));
}

void Variables::enterScope() {
	scopes.emplace_back(); 
}

void Variables::exitScope() {
	if (scopes.size() > 1) { 
		scopes.pop_back();
	}
	else {
		throw LotusException(STRING_LITERAL("Cannot exit global scope"));
	}
}

size_t lotus::Variables::scopesCount() const {
	return scopes.size();
}
