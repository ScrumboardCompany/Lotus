#include "parser/expression/ternaryExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::TernaryExpression::TernaryExpression(const Expression& condition, const Expression& expr1, const Expression& expr2, Variables& variables)
	: condition(condition), expr1(expr1), expr2(expr2), variables(variables) {
}

Value lotus::TernaryExpression::eval() {
	return condition->eval()->asBool(variables) ? expr1->eval() : expr2->eval();
}
