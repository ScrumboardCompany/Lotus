#include "parser/value/lambdaValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/variables.h"
#include "parser/value/intValue.h"

using namespace lotus;

lotus::LambdaValue::LambdaValue(const Function& function, Variables& variables) : function(function), variables(variables) {
	type = STRING_LITERAL("lambda");
}

size_t LambdaValue::getArgsCount() const {
	return function.getArgsCount();
}

Value lotus::LambdaValue::call(const std::vector<Value>& args, Variables& variables) {
	return function.call(args, variables);
}

Value lotus::LambdaValue::sizeInRam() {
	return INT(sizeof(LambdaValue));
}