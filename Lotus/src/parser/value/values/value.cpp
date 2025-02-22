#include "parser/value/value.h"
#include "utils/lotusError.h"
#include "structures/variables.h"
#include "parser/function/function.h"
#include "parser/value/classValue.h"

using namespace lotus;

int lotus::IValue::asInt(Variables& variables) {
    throwOverloadError(STRING_LITERAL("asInt"), getType());
}

double lotus::IValue::asDouble(Variables& variables) {
    throwOverloadError(STRING_LITERAL("asFloat"), getType());
}

bool lotus::IValue::asBool(Variables& variables) {
    throwOverloadError(STRING_LITERAL("asBool"), getType());
}

String lotus::IValue::asString(Variables& variables) {
    throwOverloadError(STRING_LITERAL("asString"), getType());
}

String lotus::IValue::getType() const {
    return type;
}

Value& lotus::IValue::getField(const String& name) {
    throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Field \"") + name + STRING_LITERAL("\" does not exist"));
}

Value lotus::IValue::callMethod(const String& name, const std::vector<Value>& args, Variables& variables) {
    throw LotusException(getType() + STRING_LITERAL(": ") + STRING_LITERAL("Method \"") + name + STRING_LITERAL("\" does not exist"));
}

Value lotus::IValue::call(const std::vector<Value>& args, Variables& variables) {
    throwOverloadError(STRING_LITERAL("call"), getType());
}

Value lotus::IValue::add(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("add"), getType());
}

Value lotus::IValue::substract(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("substract"), getType());
}

Value lotus::IValue::multiply(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("multiply"), getType());
}

Value lotus::IValue::divide(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("divide"), getType());
}

Value lotus::IValue::power(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("power"), getType());
}

Value lotus::IValue::divideModule(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("divideModule"), getType());
}

Value lotus::IValue::bitwiseAnd(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseAnd"), getType());
}

Value lotus::IValue::bitwiseOr(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseOr"), getType());
}

Value lotus::IValue::bitwiseXor(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseXor"), getType());
}

Value lotus::IValue::bitwiseNot(Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseNot"), getType());
}

Value lotus::IValue::bitwiseLeftShift(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseLeftShift"), getType());
}

Value lotus::IValue::bitwiseRightShift(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseRightShift"), getType());
}

Value lotus::IValue::greater(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("greater"), getType());
}

Value lotus::IValue::less(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("less"), getType());
}

Value lotus::IValue::greaterEqual(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("greaterEqual"), getType());
}

Value lotus::IValue::lessEqual(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("lessEqual"), getType());
}

Value lotus::IValue::equality(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("equality"), getType());
}

Value lotus::IValue::inequality(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("inequality"), getType());
}

Value lotus::IValue::logicalOr(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("logicalOr"), getType());
}

Value lotus::IValue::logicalAnd(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("logicalAnd"), getType());
}

Value lotus::IValue::addSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("addSet"), getType());
}

Value lotus::IValue::substractSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("v"), getType());
}

Value lotus::IValue::multiplySet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("multiplySet"), getType());
}

Value lotus::IValue::divideSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("divideSet"), getType());
}

Value lotus::IValue::powerSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("powerSet"), getType());
}

Value lotus::IValue::divideModuleSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("divideModuleSet"), getType());
}

Value lotus::IValue::bitwiseAndSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseAndSet"), getType());
}

Value lotus::IValue::bitwiseOrSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseOrSet"), getType());
}

Value lotus::IValue::bitwiseXorSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseXorSet"), getType());
}

Value lotus::IValue::bitwiseNotSet(Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseNotSet"), getType());
}

Value lotus::IValue::bitwiseLeftShiftSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseLeftShiftSet"), getType());
}

Value lotus::IValue::bitwiseRightShiftSet(const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("bitwiseRightShiftSet"), getType());
}

Value lotus::IValue::unaryPlus(Variables& variables) {
    throwOverloadError(STRING_LITERAL("unaryPlus"), getType());
}

Value lotus::IValue::unaryMinus(Variables& variables) {
    throwOverloadError(STRING_LITERAL("unaryMinus"), getType());
}

Value lotus::IValue::unaryNot(Variables& variables) {
    throwOverloadError(STRING_LITERAL("unaryNot"), getType());
}

Value lotus::IValue::prefixIncrement(Variables& variables) {
    throwOverloadError(STRING_LITERAL("prefixIncrement"), getType());
}

Value lotus::IValue::postfixIncrement(Variables& variables) {
    throwOverloadError(STRING_LITERAL("postfixIncrement"), getType());
}

Value lotus::IValue::prefixDecrement(Variables& variables) {
    throwOverloadError(STRING_LITERAL("prefixDecrement"), getType());
}

Value lotus::IValue::postfixDecrement(Variables& variables) {
    throwOverloadError(STRING_LITERAL("postfixDecrement"), getType());
}

void lotus::IValue::foreach(const String& name, const Statement& body, Variables& variables) {
    throwOverloadError(STRING_LITERAL("foreach"), getType());
}

Value lotus::IValue::getOfIndex(const Value& index, Variables& variables) {
    throwOverloadError(STRING_LITERAL("getOfIndex"), getType());
}

Value lotus::IValue::setOfIndex(const Value& index, const Value& other, Variables& variables) {
    throwOverloadError(STRING_LITERAL("setOfIndex"), getType());
}

Value lotus::IValue::size(Variables& variables) {
    throwOverloadError(STRING_LITERAL("size"), getType());
}
