#include "parser/value/undefinedValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"

using namespace lotus;

lotus::UndefinedValue::UndefinedValue() {
    type = STRING_LITERAL("undefined");
}

int lotus::UndefinedValue::asInt(Variables& variables) {
    return -1;
}

double lotus::UndefinedValue::asDouble(Variables& variables) {
    return -1.0;
}

bool lotus::UndefinedValue::asBool(Variables& variables) {
    return false;
}

String lotus::UndefinedValue::asString(Variables& variables) {
    return STRING_LITERAL("undefined");
}

Value lotus::UndefinedValue::sizeInRam() {
    return INT(sizeof(UndefinedValue));
}