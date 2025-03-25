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

Int lotus::BoolValue::asInt(Module&) {
    return static_cast<Int>(value);
}

double lotus::BoolValue::asDouble(Module&) {
    return static_cast<double>(value);
}

bool lotus::BoolValue::asBool(Module&) {
    return value;
}

String lotus::BoolValue::asString(Module&) {
    return value ? STRING_LITERAL("true") : STRING_LITERAL("false");
}


Value lotus::BoolValue::equality(const Value& other, Module& module) {
    if (!other->instanceOf("bool")) throwTypeError(STRING_LITERAL("bool"), other->getType(), module);
    return BOOL(asBool(module))->equality(other, module);
}

Value lotus::BoolValue::inequality(const Value& other, Module& module) {
    if (!other->instanceOf("bool")) throwTypeError(STRING_LITERAL("bool"), other->getType(), module);
    return BOOL(asBool(module))->inequality(other, module);
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

Value lotus::BoolValue::unaryNot(Module&) {
    return BOOL(!value);
}

Value lotus::BoolValue::sizeInRam() {
    return INT(static_cast<Int>(sizeof(*this)));
}

Value lotus::BOOL(bool value) {
    return MAKE_PTR<BoolValue>(value);
}