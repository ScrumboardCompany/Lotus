#include "parser/value/undefinedValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"

using namespace lotus;

int lotus::UndefinedValue::asInt() {
    return -1;
}

double lotus::UndefinedValue::asDouble() {
    return -1.0;
}

bool lotus::UndefinedValue::asBool() {
    return false;
}

String lotus::UndefinedValue::asString() {
    return STRING_LITERAL("undefined");
}

String lotus::UndefinedValue::getType() const {
    return STRING_LITERAL("undefined");
}