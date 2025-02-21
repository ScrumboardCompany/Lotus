#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/intValue.h"
#include "parser/value/stringCharReference.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"

using namespace lotus;

StringValue::StringValue(const String& value) : value(value) {
    type = STRING_LITERAL("string");
}

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

Value lotus::StringValue::add(const Value& other) {
    return STRING(value + other->asString());
}

Value lotus::StringValue::multiply(const Value& other) {
    if (other->getType() == STRING_LITERAL("int")) {
        String result;
        for (int i = 0; i < other->asInt(); i++) {
            result += value;
        }
        return STRING(result);
    }
    throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
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

Value lotus::StringValue::addSet(const Value& other) {
    value = add(other)->asString();
    return STRING(value);
}

Value lotus::StringValue::multiplySet(const Value& other) {
    value = multiply(other)->asString();
    return STRING(value);
}

Value& lotus::StringValue::index(const Value& index) {
    checkThrowIndexError(index, value.size());
    tempRef = MAKE_PTR<StringCharReference>(*this, index->asInt());
    return tempRef;
}

Value lotus::StringValue::size() {
    return INT(value.size());
}

Value lotus::StringValue::sizeInRam() {
    return INT(sizeof(StringValue));
}