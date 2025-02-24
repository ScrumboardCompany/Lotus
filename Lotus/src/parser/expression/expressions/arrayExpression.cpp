#include "parser/expression/arrayExpression.h"
#include "parser/value/arrayValue.h"

using namespace lotus;

lotus::ArrayExpression::ArrayExpression(const std::vector<Expression>& elements) : elements(elements) {}

Value lotus::ArrayExpression::eval(Module& module) {
	std::vector<Value> values;
	for (auto& element : elements) {
		values.push_back(element->eval(module));
	}
	return ARRAY(values);
}
