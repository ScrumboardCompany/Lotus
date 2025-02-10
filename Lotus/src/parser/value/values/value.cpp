#include "parser/value/value.h"
#include "utils/lotusError.h"

using namespace lotus;

int lotus::IValue::asInt() {
    throwOverloadError(STRING_LITERAL("asInt"), getType());
    return 0;
}

double lotus::IValue::asDouble() {
    throwOverloadError(STRING_LITERAL("asFloat"), getType());
    return 0.0;
}

bool lotus::IValue::asBool() {
    throwOverloadError(STRING_LITERAL("asBool"), getType());
    return false;
}

String lotus::IValue::asString() {
    throwOverloadError(STRING_LITERAL("asString"), getType());
    return String();
}

Value lotus::IValue::add(const Value& other) {
    throwOverloadError(STRING_LITERAL("add"), getType());
    return Value();
}

Value lotus::IValue::substract(const Value& other) {
    throwOverloadError(STRING_LITERAL("substract"), getType());
    return Value();
}

Value lotus::IValue::multiply(const Value& other) {
    throwOverloadError(STRING_LITERAL("multiply"), getType());
    return Value();
}

Value lotus::IValue::divide(const Value& other) {
    throwOverloadError(STRING_LITERAL("divide"), getType());
    return Value();
}

Value lotus::IValue::greater(const Value& other) {
    throwOverloadError(STRING_LITERAL("greater"), getType());
    return Value();
}

Value lotus::IValue::less(const Value& other) {
    throwOverloadError(STRING_LITERAL("less"), getType());
    return Value();
}

Value lotus::IValue::greaterEqual(const Value& other) {
    throwOverloadError(STRING_LITERAL("greaterEqual"), getType());
    return Value();
}

Value lotus::IValue::lessEqual(const Value& other) {
    throwOverloadError(STRING_LITERAL("lessEqual"), getType());
    return Value();
}

Value lotus::IValue::equality(const Value& other) {
    throwOverloadError(STRING_LITERAL("equality"), getType());
    return Value();
}

Value lotus::IValue::inequality(const Value& other) {
    throwOverloadError(STRING_LITERAL("inequality"), getType());
    return Value();
}

Value lotus::IValue::logicalOr(const Value& other) {
    throwOverloadError(STRING_LITERAL("logicalOr"), getType());
    return Value();
}

Value lotus::IValue::logicalAnd(const Value& other) {
    throwOverloadError(STRING_LITERAL("logicalAnd"), getType());
    return Value();
}

Value lotus::IValue::unaryPlus() {
    throwOverloadError(STRING_LITERAL("unaryPlus"), getType());
    return Value();
}

Value lotus::IValue::unaryMinus() {
    throwOverloadError(STRING_LITERAL("unaryMinus"), getType());
    return Value();
}

Value lotus::IValue::unaryNot() {
    throwOverloadError(STRING_LITERAL("unaryNot"), getType());
    return Value();
}

Value lotus::IValue::index(const Value& index) {
    throwOverloadError(STRING_LITERAL("index"), getType());
    return Value();
}