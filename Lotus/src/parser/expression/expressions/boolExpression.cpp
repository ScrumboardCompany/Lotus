#include "parser/expression/boolExpression.h"
#include "parser/value/boolValue.h"

using namespace lotus;

lotus::BoolExpression::BoolExpression(bool value) : value(value) {}

Value lotus::BoolExpression::eval() {
	return BOOL(value);
}
