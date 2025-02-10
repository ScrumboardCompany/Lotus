#include "parser/expression/arrayExpression.h"
#include "parser/value/arrayValue.h"

using namespace lotus;

lotus::ArrayExpression::ArrayExpression(std::vector<Expression> elements) : elements(elements) {}

Value lotus::ArrayExpression::eval() {
	std::vector<Value> values;
	for (auto& element : elements) {
		values.push_back(element->eval());
	}
	return ARRAY(values);
}
