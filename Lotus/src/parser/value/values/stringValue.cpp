#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"

using namespace lotus;

StringValue::StringValue(const String& value) : value(value) {
    type = STRING_LITERAL("string");
}

int lotus::StringValue::asInt(Variables& variables) {
    return std::stoi(value);
}

double lotus::StringValue::asDouble(Variables& variables) {
    return std::stod(value);
}

bool lotus::StringValue::asBool(Variables& variables) {
    return value.length() != 0;
}

String lotus::StringValue::asString(Variables& variables) {
    return value;
}

Value lotus::StringValue::add(const Value& other, Variables& variables) {
    return STRING(value + other->asString(variables));
}

Value lotus::StringValue::multiply(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int")) {
        String result;
        for (int i = 0; i < other->asInt(variables); i++) {
            result += value;
        }
        return STRING(result);
    }
    throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
}

Value lotus::StringValue::greater(const Value& other, Variables& variables) {
    return BOOL(value > other->asString(variables));
}

Value lotus::StringValue::less(const Value& other, Variables& variables) {
    return BOOL(value < other->asString(variables));
}

Value lotus::StringValue::greaterEqual(const Value& other, Variables& variables) {
    return BOOL(value >= other->asString(variables));
}

Value lotus::StringValue::lessEqual(const Value& other, Variables& variables) {
    return BOOL(value <= other->asString(variables));
}

Value lotus::StringValue::equality(const Value& other, Variables& variables) {
    return BOOL(value == other->asString(variables));
}

Value lotus::StringValue::inequality(const Value& other, Variables& variables) {
    return BOOL(value != other->asString(variables));
}

Value lotus::StringValue::logicalOr(const Value& other, Variables& variables) {
    return BOOL(asBool(variables) || other->asBool(variables));
}

Value lotus::StringValue::logicalAnd(const Value& other, Variables& variables) {
    return BOOL(asBool(variables) && other->asBool(variables));
}

Value lotus::StringValue::addSet(const Value& other, Variables& variables) {
    value = add(other, variables)->asString(variables);
    return STRING(value);
}

Value lotus::StringValue::multiplySet(const Value& other, Variables& variables) {
    value = multiply(other, variables)->asString(variables);
    return STRING(value);
}

Value lotus::StringValue::getOfIndex(const Value& index, Variables& variables) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, value.size(), variables);
        return STRING(String(1, value[index->asInt(variables)]));
    }
    throwOverloadError(STRING_LITERAL("getOfIndex"), getType(), index->getType());
}

Value lotus::StringValue::setOfIndex(const Value& index, const Value& other, Variables& variables) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, value.size(), variables);
        String otherAsString = other->asString(variables);
        if (otherAsString.empty()) {
            value[index->asInt(variables)] = '\0';
        } else {
            value[index->asInt(variables)] = otherAsString[0];
        }
        return STRING(String(1, value[index->asInt(variables)]));
    }
    throwOverloadError(STRING_LITERAL("setOfIndex"), getType(), index->getType());
}

Value lotus::StringValue::size(Variables& variables) {
    return INT(value.size());
}

Value lotus::StringValue::sizeInRam() {
    return INT(sizeof(StringValue));
}