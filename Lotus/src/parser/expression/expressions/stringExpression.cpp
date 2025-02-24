#include "parser/expression/stringExpression.h"
#include "parser/value/stringValue.h"

using namespace lotus;

lotus::StringExpression::StringExpression(const String& value) : value(value) {}

Value lotus::StringExpression::eval(Module&) {
	return STRING(value);
}