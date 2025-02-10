#include "utils/lotusError.h"
#include "utils/lotusDefines.h"

using namespace lotus;

void lotus::throwOverloadError(const String& overload, const String& type) {
    throw LotusException(type + STRING_LITERAL(": ") + STRING_LITERAL("No overload for ") + overload);
}

void lotus::throwOverloadError(const String& overload, const String& type1, const String& type2) {
    throw LotusException(type1 + STRING_LITERAL(": ") + STRING_LITERAL("No overload for") + overload + STRING_LITERAL(" with ") + type2);
}