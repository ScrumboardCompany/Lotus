#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"

using namespace lotus;

StringValue::StringValue(const String& value) : value(value) {}

int lotus::StringValue::asInt() {
    return std::stoi(value);
}

double lotus::StringValue::asDouble() {
    return std::stod(value);
}

bool lotus::StringValue::asBool() {
    return value.length() != 0;
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

Value lotus::StringValue::greater(const Value& other) {
    return BOOL(value > other->asString());
}

Value lotus::StringValue::less(const Value& other) {
    return BOOL(value < other->asString());
}

Value lotus::StringValue::greaterEqual(const Value& other) {
    return BOOL(value >= other->asString());
}

Value lotus::StringValue::lessEqual(const Value& other) {
    return BOOL(value <= other->asString());
}

Value lotus::StringValue::equality(const Value& other) {
    return BOOL(value == other->asString());
}

Value lotus::StringValue::inequality(const Value& other) {
    return BOOL(value != other->asString());
}

Value lotus::StringValue::logicalOr(const Value& other) {
    return BOOL(asBool() || other->asBool());
}

Value lotus::StringValue::logicalAnd(const Value& other) {
    return BOOL(asBool() && other->asBool());
}