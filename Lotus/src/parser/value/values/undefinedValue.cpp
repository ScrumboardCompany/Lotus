#include "parser/value/undefinedValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"

using namespace lotus;

lotus::UndefinedValue::UndefinedValue() {
    type = STRING_LITERAL("undefined");
}

Int lotus::UndefinedValue::asInt(Module&) {
    return -1;
}

double lotus::UndefinedValue::asDouble(Module&) {
    return -1.0;
}

bool lotus::UndefinedValue::asBool(Module&) {
    return false;
}

String lotus::UndefinedValue::asString(Module&) {
    return STRING_LITERAL("undefined");
}

Value lotus::UndefinedValue::sizeInRam() {
    return INT(static_cast<Int>(sizeof(*this)));
}

Value lotus::UNDEFINED() {
    return MAKE_PTR<UndefinedValue>();
}