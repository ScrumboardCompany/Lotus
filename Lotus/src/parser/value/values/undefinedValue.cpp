#include "parser/value/undefinedValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"

using namespace lotus;

lotus::UndefinedValue::UndefinedValue() {
    type = STRING_LITERAL("undefined");
}

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

Value lotus::UndefinedValue::sizeInRam() {
    return INT(sizeof(UndefinedValue));
}