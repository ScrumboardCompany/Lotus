#include "parser/value/lambdaValue.h"
#include "utils/lotusError.h"
#include "parser/function/function.h"
#include "structures/variables.h"
#include "parser/value/intValue.h"
#include "structures/module.h"

using namespace lotus;

lotus::LambdaValue::LambdaValue(const Function& function) : function(function) {
	type = STRING_LITERAL("lambda");
}

size_t LambdaValue::getArgsCount() const {
	return function.getArgsCount();
}

Value lotus::LambdaValue::call(const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs) {
	return function.call(args, specifiedArgs, module);
}

Value lotus::LambdaValue::sizeInRam() {
	return INT(static_cast<Int>(sizeof(*this)));
}