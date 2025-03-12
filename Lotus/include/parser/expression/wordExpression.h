#pragma once

#ifndef _WORDEXPRESSION_
#define _WORDEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class WordExpression : public IExpression {
		String name;

		friend class SetExpression;
		friend class CallLambdaExpression;
		friend class SwapExpression;

	public:
		WordExpression(const String& name);

		Value eval(Module& module) override;
	};
}

#endif // _WORDEXPRESSION_