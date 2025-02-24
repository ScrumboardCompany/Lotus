#include "parser/expression/floatExpression.h"
#include "parser/value/floatValue.h"

using namespace lotus;

lotus::FloatExpression::FloatExpression(double value) : value(value) {}

Value lotus::FloatExpression::eval(Module&) {
	return FLOAT(value);
}
