#include "parser/value/value.h"
#include "utils/lotusError.h"
#include "structures/variables.h"
#include "parser/function/function.h"
#include "parser/value/classValue.h"

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

Value lotus::IValue::power(const Value& other) {
    throwOverloadError(STRING_LITERAL("power"), getType());
}

Value lotus::IValue::divideModule(const Value& other) {
    throwOverloadError(STRING_LITERAL("divideModule"), getType());
}

Value lotus::IValue::bitwiseAnd(const Value& other) {
    throwOverloadError(STRING_LITERAL("bitwiseAnd"), getType());
}

Value lotus::IValue::bitwiseOr(const Value& other) {
    throwOverloadError(STRING_LITERAL("bitwiseOr"), getType());
}

Value lotus::IValue::bitwiseXor(const Value& other) {
    throwOverloadError(STRING_LITERAL("bitwiseXor"), getType());
}

Value lotus::IValue::bitwiseNot() {
    throwOverloadError(STRING_LITERAL("bitwiseNot"), getType());
}

Value lotus::IValue::bitwiseLeftShift(const Value& other) {
    throwOverloadError(STRING_LITERAL("bitwiseLeftShift"), getType());
}

Value lotus::IValue::bitwiseRightShift(const Value& other) {
    throwOverloadError(STRING_LITERAL("bitwiseRightShift"), getType());
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

Value lotus::IValue::addSet(const Value& other) {
    throwOverloadError(STRING_LITERAL("addSet"), getType());
}

Value lotus::IValue::substractSet(const Value& other) {
    throwOverloadError(STRING_LITERAL("v"), getType());
}

Value lotus::IValue::multiplySet(const Value& other) {
    throwOverloadError(STRING_LITERAL("multiplySet"), getType());
}

Value lotus::IValue::divideSet(const Value& other) {
    throwOverloadError(STRING_LITERAL("divideSet"), getType());
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

Value lotus::IValue::prefixIncrement() {
    throwOverloadError(STRING_LITERAL("prefixIncrement"), getType());
}

Value lotus::IValue::postfixIncrement() {
    throwOverloadError(STRING_LITERAL("postfixIncrement"), getType());
}

Value lotus::IValue::prefixDecrement() {
    throwOverloadError(STRING_LITERAL("prefixDecrement"), getType());
}

Value lotus::IValue::postfixDecrement() {
    throwOverloadError(STRING_LITERAL("postfixDecrement"), getType());
}

void lotus::IValue::foreach(const String& name, const Statement& body, Variables& variables) {
    throwOverloadError(STRING_LITERAL("foreach"), getType());
}

Value& lotus::IValue::index(const Value& index) {
    throwOverloadError(STRING_LITERAL("index"), getType());
}

Value lotus::IValue::size() {
    throwOverloadError(STRING_LITERAL("size"), getType());
}
