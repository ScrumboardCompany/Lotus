#include "utils/lotusError.h"
#include "utils/lotusDefines.h"
#include "parser/value/value.h"
#include "parser/value/intValue.h"
#include "structures/module.h"
#include "parser/value/stringValue.h"
#include "utils/utils.h"

using namespace lotus;

void lotus::throwOverloadError(const String& overload, const String& type) {
    throw LotusException(type + STRING_LITERAL(": No overload for ") + overload);
}

void lotus::throwOverloadError(const String& overload, const String& type1, const String& type2) {
    throw LotusException(type1 + STRING_LITERAL(": No overload for ") + overload + STRING_LITERAL(" with ") + type2);
}

void lotus::throwTypeError(const String& type1, const String& type2, Module& module) {
    module.THROW(STRING(STRING_LITERAL("Expected ") + type1 + STRING_LITERAL(" instead of ") + type2), STRING("type_error"));
}

void lotus::throwTypeError(const String& type1, const String& type2, const String& type3, Module& module) {
    module.THROW(STRING(STRING_LITERAL("Expected ") + type1 + STRING_LITERAL(" or ") + type2 + STRING_LITERAL(" instead of ") + type3), STRING("type_error"));
}

void lotus::checkThrowIndexError(const Value& index, size_t size, Module& module) {
    if (index->asInt(module) < 0ll || static_cast<size_t>(index->asInt(module)) >= size) {
        module.THROW(STRING(INT(index->asInt(module))->asString(module) + STRING_LITERAL(" is invalid index")));
    }
}