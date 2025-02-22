#include "utils/lotusError.h"
#include "utils/lotusDefines.h"
#include "parser/value/value.h"
#include "parser/value/intValue.h"
#include "structures/variables.h"

using namespace lotus;

void lotus::throwOverloadError(const String& overload, const String& type) {
    throw LotusException(type + STRING_LITERAL(": ") + STRING_LITERAL("No overload for ") + overload);
}

void lotus::throwOverloadError(const String& overload, const String& type1, const String& type2) {
    throw LotusException(type1 + STRING_LITERAL(": ") + STRING_LITERAL("No overload for ") + overload + STRING_LITERAL(" with ") + type2);
}

void lotus::checkThrowIndexError(const Value& index, int size, Variables& variables) {
    if (index->asInt(variables) < 0 || index->asInt(variables) >= size) {
        throw LotusException(INT(index->asInt(variables))->asString(variables) + STRING_LITERAL(" is invalid index"));
    }
}