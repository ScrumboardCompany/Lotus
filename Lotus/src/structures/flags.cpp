#include "structures/flags.h"
#include "utils/lotusError.h"

using namespace lotus;

void lotus::Flags::set(const String& key, bool value) {
	if (isExistsWithError(key)) {
		flags[key] = value;
	}
}

bool lotus::Flags::isExistsWithError(const String& key) const {
	if (flags.find(key) != flags.end()) return true;

	throw LotusException(STRING_LITERAL("Flag \"") + key + STRING_LITERAL("\" doesn't exist"));
}
