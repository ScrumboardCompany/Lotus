#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"

using namespace lotus;

int lotus::UndefinedValue::asInt() {
    return -1;
}

double lotus::UndefinedValue::asDouble() {
    return -1.0;
}

String lotus::UndefinedValue::asString() {
    return STRING_LITERAL("undefined");
}

String lotus::UndefinedValue::getType() const {
    return STRING_LITERAL("undefined");
}

Value lotus::UndefinedValue::add(const Value& other) {
    throw LotusException("No overload for adding undefined");
}

Value lotus::UndefinedValue::substract(const Value& other) {
    throw LotusException("No overload for substracting undefined");
}

Value lotus::UndefinedValue::multiply(const Value& other) {
    throw LotusException("No overload for multiplicating undefined");
}

Value lotus::UndefinedValue::divide(const Value& other) {
    throw LotusException("No overload for dividing undefined");
}

Value lotus::UndefinedValue::unary_plus() {
    throw LotusException("No overload for undefined's unary plus");
}

Value lotus::UndefinedValue::unary_minus() {
    throw LotusException("No overload for undefined's unary minus");
}