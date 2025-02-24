#include "parser/expression/intExpression.h"
#include "parser/value/intValue.h"

using namespace lotus;

lotus::IntExpression::IntExpression(int value) : value(value) {}

Value lotus::IntExpression::eval(Module&) {
	return INT(value);
}
