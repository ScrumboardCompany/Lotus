#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"

using namespace lotus;

BoolValue::BoolValue(bool value) : value(value) {
    type = STRING_LITERAL("bool");
}

int lotus::BoolValue::asInt(Variables& variables) {
    return static_cast<int>(value);
}

double lotus::BoolValue::asDouble(Variables& variables) {
    return static_cast<double>(value);
}

bool lotus::BoolValue::asBool(Variables& variables) {
    return value;
}

String lotus::BoolValue::asString(Variables& variables) {
    return value ? STRING_LITERAL("true") : STRING_LITERAL("false");
}

Value lotus::BoolValue::add(const Value& other, Variables& variables) {
    return INT(asInt(variables))->add(other, variables);
}

Value lotus::BoolValue::substract(const Value& other, Variables& variables) {
    return INT(asInt(variables))->substract(other, variables);
}

Value lotus::BoolValue::multiply(const Value& other, Variables& variables) {
    return INT(asInt(variables))->multiply(other, variables);
}

Value lotus::BoolValue::divide(const Value& other, Variables& variables) {
    return INT(asInt(variables))->divide(other, variables);
}

Value lotus::BoolValue::power(const Value& other, Variables& variables) {
    return INT(asInt(variables))->power(other, variables);
}

Value lotus::BoolValue::divideModule(const Value& other, Variables& variables) {
    return INT(asInt(variables))->divideModule(other, variables);
}

Value lotus::BoolValue::bitwiseAnd(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) & other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseAnd"), getType(), other->getType());
}

Value lotus::BoolValue::bitwiseOr(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) | other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseOr"), getType(), other->getType());
}

Value lotus::BoolValue::bitwiseXor(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) ^ other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseXor"), getType(), other->getType());
}

Value lotus::BoolValue::bitwiseNot(Variables& variables) {
    return BOOL(~static_cast<int>(value));
}

Value lotus::BoolValue::bitwiseLeftShift(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) << other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseLeftShift"), getType(), other->getType());
}

Value lotus::BoolValue::bitwiseRightShift(const Value& other, Variables& variables) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) >> other->asInt(variables));
    throwOverloadError(STRING_LITERAL("bitwiseRightShift"), getType(), other->getType());
}


Value lotus::BoolValue::greater(const Value& other, Variables& variables) {
    return BOOL(asInt(variables))->greater(other, variables);
}

Value lotus::BoolValue::less(const Value& other, Variables& variables) {
    return BOOL(asInt(variables))->less(other, variables);
}

Value lotus::BoolValue::greaterEqual(const Value& other, Variables& variables) {
    return BOOL(asInt(variables))->greaterEqual(other, variables);
}

Value lotus::BoolValue::lessEqual(const Value& other, Variables& variables) {
    return BOOL(asInt(variables))->lessEqual(other, variables);
}

Value lotus::BoolValue::equality(const Value& other, Variables& variables) {
    return BOOL(asInt(variables))->equality(other, variables);
}

Value lotus::BoolValue::inequality(const Value& other, Variables& variables) {
    return BOOL(asInt(variables))->inequality(other, variables);
}

Value lotus::BoolValue::logicalOr(const Value& other, Variables& variables) {
    return BOOL(asInt(variables))->logicalOr(other, variables);
}

Value lotus::BoolValue::logicalAnd(const Value& other, Variables& variables) {
    return BOOL(asInt(variables))->logicalAnd(other, variables);
}

Value lotus::BoolValue::unaryPlus(Variables& variables) {
    return INT(asInt(variables))->unaryPlus(variables);
}

Value lotus::BoolValue::unaryMinus(Variables& variables) {
    return INT(asInt(variables))->unaryMinus(variables);
}

Value lotus::BoolValue::unaryNot(Variables& variables) {
    return BOOL(!value);
}

Value lotus::BoolValue::sizeInRam() {
    return INT(sizeof(BoolValue));
}