#include "parser/expression/lambdaExpression.h"
#include "utils/utils.h"
#include "structures/variables.h"
#include "parser/function/function.h"
#include "parser/value/lambdaValue.h"

using namespace lotus;

lotus::LambdaExpression::LambdaExpression(Variables& variables, const Function& function)
	: variables(variables), function(function) {
}

Value lotus::LambdaExpression::eval() {
	return MAKE_PTR<LambdaValue>(function, variables);
}