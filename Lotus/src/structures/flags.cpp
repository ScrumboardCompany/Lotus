#include "structures/flags.h"
#include "utils/lotusError.h"

using namespace lotus;

void lotus::Flags::set(const String& key, bool value) {
	if (isExistsWithError(key)) {
		flags[key].value = value;
	}
}

void lotus::Flags::setDefault(const String& key) {
	if (isExistsWithError(key)) {
		flags[key].value = flags[key].defaultValue;
	}
}

bool lotus::Flags::get(const String& key) const {
	if (isExistsWithError(key)) {
		return flags.at(key).value;
	}
	return false;
}

bool lotus::Flags::getDefault(const String& key) const {
	if (isExistsWithError(key)) {
		return flags.at(key).defaultValue;
	}
	return false;
}

bool lotus::Flags::isExistsWithError(const String& key) const {
	if (flags.find(key) != flags.end()) return true;

	throw LotusException(STRING_LITERAL("Flag \"") + key + STRING_LITERAL("\" doesn't exist"));
}
