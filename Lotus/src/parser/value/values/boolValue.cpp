#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/module.h"

using namespace lotus;

BoolValue::BoolValue(bool value) : value(value) {
    type = STRING_LITERAL("bool");
}

int lotus::BoolValue::asInt(Module& module) {
    return static_cast<int>(value);
}

double lotus::BoolValue::asDouble(Module& module) {
    return static_cast<double>(value);
}

bool lotus::BoolValue::asBool(Module& module) {
    return value;
}

String lotus::BoolValue::asString(Module& module) {
    return value ? STRING_LITERAL("true") : STRING_LITERAL("false");
}

Value lotus::BoolValue::add(const Value& other, Module& module) {
    return INT(asInt(module))->add(other, module);
}

Value lotus::BoolValue::substract(const Value& other, Module& module) {
    return INT(asInt(module))->substract(other, module);
}

Value lotus::BoolValue::multiply(const Value& other, Module& module) {
    return INT(asInt(module))->multiply(other, module);
}

Value lotus::BoolValue::divide(const Value& other, Module& module) {
    return INT(asInt(module))->divide(other, module);
}

Value lotus::BoolValue::power(const Value& other, Module& module) {
    return INT(asInt(module))->power(other, module);
}

Value lotus::BoolValue::divideModule(const Value& other, Module& module) {
    return INT(asInt(module))->divideModule(other, module);
}

Value lotus::BoolValue::bitwiseAnd(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) & other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseAnd"), getType(), other->getType());
}

Value lotus::BoolValue::bitwiseOr(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) | other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseOr"), getType(), other->getType());
}

Value lotus::BoolValue::bitwiseXor(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) ^ other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseXor"), getType(), other->getType());
}

Value lotus::BoolValue::bitwiseNot(Module& module) {
    return BOOL(~static_cast<int>(value));
}

Value lotus::BoolValue::bitwiseLeftShift(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) << other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseLeftShift"), getType(), other->getType());
}

Value lotus::BoolValue::bitwiseRightShift(const Value& other, Module& module) {
    if (other->getType() == STRING_LITERAL("int") || other->getType() == STRING_LITERAL("bool")) return INT(static_cast<int>(value) >> other->asInt(module));
    throwOverloadError(STRING_LITERAL("bitwiseRightShift"), getType(), other->getType());
}


Value lotus::BoolValue::greater(const Value& other, Module& module) {
    return INT(asInt(module))->greater(other, module);
}

Value lotus::BoolValue::less(const Value& other, Module& module) {
    return INT(asInt(module))->less(other, module);
}

Value lotus::BoolValue::greaterEqual(const Value& other, Module& module) {
    return INT(asInt(module))->greaterEqual(other, module);
}

Value lotus::BoolValue::lessEqual(const Value& other, Module& module) {
    return INT(asInt(module))->lessEqual(other, module);
}

Value lotus::BoolValue::equality(const Value& other, Module& module) {
    return INT(asInt(module))->equality(other, module);
}

Value lotus::BoolValue::inequality(const Value& other, Module& module) {
    return INT(asInt(module))->inequality(other, module);
}

Value lotus::BoolValue::logicalOr(const Value& other, Module& module) {
    return INT(asInt(module))->logicalOr(other, module);
}

Value lotus::BoolValue::logicalAnd(const Value& other, Module& module) {
    return INT(asInt(module))->logicalAnd(other, module);
}

Value lotus::BoolValue::unaryPlus(Module& module) {
    return INT(asInt(module))->unaryPlus(module);
}

Value lotus::BoolValue::unaryMinus(Module& module) {
    return INT(asInt(module))->unaryMinus(module);
}

Value lotus::BoolValue::unaryNot(Module& module) {
    return BOOL(!value);
}

Value lotus::BoolValue::sizeInRam() {
    return INT(static_cast<int>(sizeof(BoolValue)));
}