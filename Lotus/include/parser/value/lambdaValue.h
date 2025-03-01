#pragma once

#ifndef _LAMBDAVALUE_
#define _LAMBDAVALUE_

#include "parser/value/value.h"
#include "parser/function/function.h"

namespace lotus {

	class Variables;

	class LambdaValue : public IValue {
		Function function;

		friend class FunctionExpression;
		friend class CallLambdaExpression;

	public:

		LambdaValue(const Function& function);

		size_t getArgsCount() const;

		Value call(const std::vector<Value>& args, Module& module, const StringMap<Value>& specifiedArgs = {}) override;

		Value sizeInRam() override;
	};

}

#endif // _LAMBDAVALUE_