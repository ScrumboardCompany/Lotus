#include "parser/value/value.h"
#include "utils/lotusError.h"

using namespace lotus;

int lotus::IValue::asInt() {
    throwOverloadError(STRING_LITERAL("asInt"), getType());
}

double lotus::IValue::asDouble() {
    throwOverloadError(STRING_LITERAL("asFloat"), getType());
}

bool lotus::IValue::asBool() {
    throwOverloadError(STRING_LITERAL("asBool"), getType());
}

String lotus::IValue::asString() {
    throwOverloadError(STRING_LITERAL("asString"), getType());
}

Value lotus::IValue::add(const Value& other) {
    throwOverloadError(STRING_LITERAL("add"), getType());
}

Value lotus::IValue::substract(const Value& other) {
    throwOverloadError(STRING_LITERAL("substract"), getType());
}

Value lotus::IValue::multiply(const Value& other) {
    throwOverloadError(STRING_LITERAL("multiply"), getType());
}

Value lotus::IValue::divide(const Value& other) {
    throwOverloadError(STRING_LITERAL("divide"), getType());
}

Value lotus::IValue::greater(const Value& other) {
    throwOverloadError(STRING_LITERAL("greater"), getType());
}

Value lotus::IValue::less(const Value& other) {
    throwOverloadError(STRING_LITERAL("less"), getType());
}

Value lotus::IValue::greaterEqual(const Value& other) {
    throwOverloadError(STRING_LITERAL("greaterEqual"), getType());
}

Value lotus::IValue::lessEqual(const Value& other) {
    throwOverloadError(STRING_LITERAL("lessEqual"), getType());
}

Value lotus::IValue::equality(const Value& other) {
    throwOverloadError(STRING_LITERAL("equality"), getType());
}

Value lotus::IValue::inequality(const Value& other) {
    throwOverloadError(STRING_LITERAL("inequality"), getType());
}

Value lotus::IValue::logicalOr(const Value& other) {
    throwOverloadError(STRING_LITERAL("logicalOr"), getType());
}

Value lotus::IValue::logicalAnd(const Value& other) {
    throwOverloadError(STRING_LITERAL("logicalAnd"), getType());
}

Value lotus::IValue::unaryPlus() {
    throwOverloadError(STRING_LITERAL("unaryPlus"), getType());
}

Value lotus::IValue::unaryMinus() {
    throwOverloadError(STRING_LITERAL("unaryMinus"), getType());
}

Value lotus::IValue::unaryNot() {
    throwOverloadError(STRING_LITERAL("unaryNot"), getType());
}

Value& lotus::IValue::index(const Value& index) {
    throwOverloadError(STRING_LITERAL("index"), getType());
}

Value lotus::IValue::size() {
    throwOverloadError(STRING_LITERAL("size"), getType());
}