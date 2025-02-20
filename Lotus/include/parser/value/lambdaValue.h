#pragma once

#ifndef _LAMBDAVALUE_
#define _LAMBDAVALUE_

#include "parser/value/value.h"
#include "parser/function/function.h"

namespace lotus {

	class Variables;

	class LambdaValue : public IValue {
		Function function;
		Variables variables;

	public:

		LambdaValue(const Function& function, Variables& variables);

		size_t getArgsCount() const;

		Value call(const std::vector<Value>& args, Variables& variables) override;

		Value sizeInRam() override;
	};

}

#endif // _LAMBDAVALUE_