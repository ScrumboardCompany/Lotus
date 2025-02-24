#include "parser/expression/ternaryExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::TernaryExpression::TernaryExpression(const Expression& condition, const Expression& expr1, const Expression& expr2)
	: condition(condition), expr1(expr1), expr2(expr2) {
}

Value lotus::TernaryExpression::eval(Module& module) {
	return condition->eval(module)->asBool(module) ? expr1->eval(module) : expr2->eval(module);
}
