#include "parser/expression/undefinedExpression.h"
#include "parser/value/undefinedValue.h"

using namespace lotus;

Value lotus::UndefinedExpression::eval() {
	return UNDEFINED();
}
