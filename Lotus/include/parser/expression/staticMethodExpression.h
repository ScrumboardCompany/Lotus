#pragma once

#ifndef _STATICMETHODEXPRESSION_
#define _STATICMETHODEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Variables;
	class Statics;

	class StaticMethodExpression : public IExpression {

		String staticName;
		String method;
		std::vector<Expression> args;

	public:
		StaticMethodExpression(const String& staticName, const String& method, const std::vector<Expression>& args);

		Value eval(Module& module) override;
	};
}

#endif // _STATICMETHODEXPRESSION_
