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

Int lotus::StringValue::asInt(Module&) {
    return std::stoll(value);
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
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("add"), getType(), other->getType());
    return STRING(value + other->asString(module));
}

Value lotus::StringValue::multiply(const Value& other, Module& module) {
    if (!other->instanceOf("string") && !other->instanceOf("int")) throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
    if (other->getType() == STRING_LITERAL("int")) {
        String result;
        for (Int i = 0; i < other->asInt(module); i++) {
            result += value;
        }
        return STRING(result);
    }
    throwOverloadError(STRING_LITERAL("multiply"), getType(), other->getType());
}

Value lotus::StringValue::greater(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("greater"), getType(), other->getType());
    return BOOL(value > other->asString(module));
}

Value lotus::StringValue::less(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("less"), getType(), other->getType());
    return BOOL(value < other->asString(module));
}

Value lotus::StringValue::greaterEqual(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("greaterEqual"), getType(), other->getType());
    return BOOL(value >= other->asString(module));
}

Value lotus::StringValue::lessEqual(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("lessEqual"), getType(), other->getType());
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
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("addSet"), getType(), other->getType());
    value = add(other, module)->asString(module);
    return STRING(value);
}

Value lotus::StringValue::multiplySet(const Value& other, Module& module) {
    if (!other->instanceOf("string")) throwOverloadError(STRING_LITERAL("multiplySet"), getType(), other->getType());
    value = multiply(other, module)->asString(module);
    return STRING(value);
}

Value lotus::StringValue::getOfIndex(const Value& index, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, value.size(), module);
        return STRING(String(1, value[static_cast<int>(index->asInt(module))]));
    }
    throwOverloadError(STRING_LITERAL("getOfIndex"), getType(), index->getType());
}

Value lotus::StringValue::setOfIndex(const Value& index, const Value& other, Module& module) {
    if (index->getType() == STRING_LITERAL("int")) {
        checkThrowIndexError(index, value.size(), module);
        String otherAsString = other->asString(module);
        if (otherAsString.empty()) {
            value[static_cast<int>(index->asInt(module))] = '\0';
        } else {
            value[static_cast<int>(index->asInt(module))] = otherAsString[0];
        }
        return STRING(String(1, value[static_cast<int>(index->asInt(module))]));
    }
    throwOverloadError(STRING_LITERAL("setOfIndex"), getType(), index->getType());
}

Value lotus::StringValue::size(Module&) {
    return INT(static_cast<Int>(value.size()));
}

Value lotus::StringValue::sizeInRam() {
    return INT(static_cast<Int>(sizeof(*this)));
}