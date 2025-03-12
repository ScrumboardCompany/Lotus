#include "parser/expression/intExpression.h"
#include "parser/value/intValue.h"

using namespace lotus;

lotus::IntExpression::IntExpression(Int value) : value(value) {}

Value lotus::IntExpression::eval(Module&) {
	return INT(value);
}
