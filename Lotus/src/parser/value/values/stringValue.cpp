#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/intValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/module.h"

using namespace lotus;

lotus::StringValue::StringValue(const char* value) : StringValue(STRING_VAR_LITERAL(value)) {}

StringValue::StringValue(const String& value) : value(value) {
    type = STRING_LITERAL("string");
}

int lotus::StringValue::asInt(Module&) {
    return std::stoi(value);
}

double lotus::StringValue::asDouble(Module&) {
    return std::stod(value);
}

bool lotus::StringValue::asBool(Module&) {
    return value.length() != 0;
}

String lotus::StringValue::asString(Module&) {
    return value;
}

Value lotus::StringValue::add(const Value& other, Module& module) {
    return STRING(value + other->asString(module));
}

Value lotus::StringValue::multiply(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int")) {
        String result;
        for (int i = 0; i < other->asInt(module); i++) {
            result += value;
        }
        return STRING(result);
    }
    throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
}

Value lotus::StringValue::greater(const Value& other, Module& module) {
    return BOOL(value > other->asString(module));
}

Value lotus::StringValue::less(const Value& other, Module& module) {
    return BOOL(value < other->asString(module));
}

Value lotus::StringValue::greaterEqual(const Value& other, Module& module) {
    return BOOL(value >= other->asString(module));
}

Value lotus::StringValue::lessEqual(const Value& other, Module& module) {
    return BOOL(value <= other->asString(module));
}

Value lotus::StringValue::equality(const Value& other, Module& module) {
    return BOOL(value == other->asString(module));
}

Value lotus::StringValue::inequality(const Value& other, Module& module) {
    return BOOL(value != other->asString(module));
}

Value lotus::StringValue::logicalOr(const Value& other, Module& module) {
    return BOOL(asBool(module) || other->asBool(module));
}

Value lotus::StringValue::logicalAnd(const Value& other, Module& module) {
    return BOOL(asBool(module) && other->asBool(module));
}

Value lotus::StringValue::addSet(const Value& other, Module& module) {
    value = add(other, module)->asString(module);
    return STRING(value);
}

Value lotus::StringValue::multiplySet(const Value& other, Module& module) {
    value = multiply(other, module)->asString(module);
    return STRING(value);
}

Value lotus::StringValue::getOfIndex(const Value& index, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, value.size(), module);
        return STRING(String(1, value[index->asInt(module)]));
    }
    throwOverloadError(STRING_LITERAL("getOfIndex"), getType(), index->getType());
}

Value lotus::StringValue::setOfIndex(const Value& index, const Value& other, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, value.size(), module);
        String otherAsString = other->asString(module);
        if (otherAsString.empty()) {
            value[index->asInt(module)] = '\0';
        } else {
            value[index->asInt(module)] = otherAsString[0];
        }
        return STRING(String(1, value[index->asInt(module)]));
    }
    throwOverloadError(STRING_LITERAL("setOfIndex"), getType(), index->getType());
}

Value lotus::StringValue::size(Module&) {
    return INT(static_cast<int>(value.size()));
}

Value lotus::StringValue::sizeInRam() {
    return INT(static_cast<int>(sizeof(*this)));
}