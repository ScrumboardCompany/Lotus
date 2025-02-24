#include "parser/expression/indexExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::IndexExpression::IndexExpression(const Expression& expression, const Expression& index)
	: expression(expression), index(index) {}

Value lotus::IndexExpression::eval(Module& module) {
	return expression->eval(module)->getOfIndex(index->eval(module), module);
}
