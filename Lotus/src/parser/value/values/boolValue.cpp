#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"

using namespace lotus;

BoolValue::BoolValue(bool value) : value(value) {
    type = STRING_LITERAL("bool");
}

int lotus::BoolValue::asInt() {
    return static_cast<int>(value);
}

double lotus::BoolValue::asDouble() {
    return static_cast<double>(value);
}

bool lotus::BoolValue::asBool() {
    return value;
}

String lotus::BoolValue::asString() {
    return value ? STRING_LITERAL("true") : STRING_LITERAL("false");
}

Value lotus::BoolValue::add(const Value& other) {
    return INT(asInt())->add(other);
}

Value lotus::BoolValue::substract(const Value& other) {
    return INT(asInt())->substract(other);
}

Value lotus::BoolValue::multiply(const Value& other) {
    return INT(asInt())->multiply(other);
}

Value lotus::BoolValue::divide(const Value& other) {
    return INT(asInt())->divide(other);
}

Value lotus::BoolValue::greater(const Value& other) {
    return INT(asInt())->greater(other);
}

Value lotus::BoolValue::less(const Value& other) {
    return INT(asInt())->less(other);
}

Value lotus::BoolValue::greaterEqual(const Value& other) {
    return INT(asInt())->greaterEqual(other);
}

Value lotus::BoolValue::lessEqual(const Value& other) {
    return INT(asInt())->lessEqual(other);
}

Value lotus::BoolValue::equality(const Value& other) {
    return INT(asInt())->equality(other);
}

Value lotus::BoolValue::inequality(const Value& other) {
    return INT(asInt())->inequality(other);
}

Value lotus::BoolValue::logicalOr(const Value& other) {
    return INT(asInt())->logicalOr(other);
}

Value lotus::BoolValue::logicalAnd(const Value& other) {
    return INT(asInt())->logicalAnd(other);
}

Value lotus::BoolValue::unaryPlus() {
    return INT(asInt())->unaryPlus();
}

Value lotus::BoolValue::unaryMinus() {
    return INT(asInt())->unaryMinus();
}

Value lotus::BoolValue::unaryNot() {
    return BOOL(!value);
}

Value lotus::BoolValue::sizeInRam() {
    return INT(sizeof(BoolValue));
}