#include "parser/value/value.h"
#include "utils/lotusError.h"

using namespace lotus;

int lotus::IValue::asInt() {
    throw LotusException("No overload for toInt");
}

double lotus::IValue::asDouble() {
    throw LotusException("No overload for toFloat");
}

bool lotus::IValue::asBool() {
    throw LotusException("No overload for toBool");
}

String lotus::IValue::asString() {
    throw LotusException("No overload for toString");
}

Value lotus::IValue::add(const Value& other) {
    throw LotusException("No overload for add");
}

Value lotus::IValue::substract(const Value& other) {
    throw LotusException("No overload for substract");
}

Value lotus::IValue::multiply(const Value& other) {
    throw LotusException("No overload for multiply");
}

Value lotus::IValue::divide(const Value& other) {
    throw LotusException("No overload for divide");
}

Value lotus::IValue::greater(const Value& other) {
    throw LotusException("No overload for greater");
}

Value lotus::IValue::less(const Value& other) {
    throw LotusException("No overload for less");
}

Value lotus::IValue::greaterEqual(const Value& other) {
    throw LotusException("No overload for greaterEqual");
}

Value lotus::IValue::lessEqual(const Value& other) {
    throw LotusException("No overload for lessEqual");
}

Value lotus::IValue::equality(const Value& other) {
    throw LotusException("No overload for equality");
}

Value lotus::IValue::inequality(const Value& other) {
    throw LotusException("No overload for inequality");
}

Value lotus::IValue::logicalOr(const Value& other) {
    throw LotusException("No overload for logicalOr");
}

Value lotus::IValue::logicalAnd(const Value& other) {
    throw LotusException("No overload for logicalAnd");
}

Value lotus::IValue::unaryPlus() {
    throw LotusException("No overload for unaryPlus");
}

Value lotus::IValue::unaryMinus() {
    throw LotusException("No overload for unaryMinus");
}

Value lotus::IValue::unaryNot() {
    throw LotusException("No overload for unaryNot");
}

