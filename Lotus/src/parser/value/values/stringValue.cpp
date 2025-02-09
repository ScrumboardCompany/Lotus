#include "parser/value/stringValue.h"
#include "utils/lotusError.h"

using namespace lotus;

StringValue::StringValue(const String& value) : value(value) {}

int lotus::StringValue::asInt() {
    return std::stoi(value);
}

double lotus::StringValue::asDouble() {
    return std::stod(value);
}

String lotus::StringValue::asString() {
    return value;
}

String lotus::StringValue::getType() const {
    return STRING_LITERAL("string");
}

Value lotus::StringValue::add(const Value& other) {
    if (other->getType() == STRING_LITERAL("string")) return STRING(value + other->asString());
    throw LotusException("Unable to concatenate string");
}

Value lotus::StringValue::substract(const Value& other) {
    throw LotusException("Unable to substract string");
}

Value lotus::StringValue::multiply(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) {
        String result;
        for (int i = 0; i < other->asInt(); i++) {
            result += value;
        }
        return STRING(result);
    }
    throw LotusException("Unable to multuply string");
}

Value lotus::StringValue::divide(const Value& other) {
    throw LotusException("Unable to divide string");
}

Value lotus::StringValue::unary_plus() {
    throw LotusException("Unable to find unary plus overload for string");
}

Value lotus::StringValue::unary_minus() {
    throw LotusException("Unable to find unary minus overload for string");
}

