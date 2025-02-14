#include "parser/expression/indexExpression.h"

using namespace lotus;

lotus::IndexExpression::IndexExpression(const Expression& expression, const Expression& index) : expression(expression), index(index) {}

Value lotus::IndexExpression::eval() {
	return expression->eval()->index(index->eval());
}
