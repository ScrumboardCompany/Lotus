#include "parser/expression/fieldExpression.h"
#include "structures/variables.h"

using namespace lotus;

lotus::FieldExpression::FieldExpression(const Expression& expr, const String& field)
	: expr(expr), field(field) {
}

Value lotus::FieldExpression::eval() {
	return expr->eval()->getField(field);
}