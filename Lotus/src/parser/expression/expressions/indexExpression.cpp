#include "parser/expression/indexExpression.h"

using namespace lotus;

lotus::IndexExpression::IndexExpression(Expression expression, Expression index) : expression(expression), index(index) {}

Value lotus::IndexExpression::eval() {
	return expression->eval()->index(index->eval());
}
