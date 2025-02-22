#include "parser/expression/indexExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::IndexExpression::IndexExpression(const Expression& expression, const Expression& index, Variables& variables) : expression(expression), index(index), variables(variables) {}

Value lotus::IndexExpression::eval() {
	return expression->eval()->getOfIndex(index->eval(), variables);
}
