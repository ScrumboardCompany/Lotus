#pragma once

#ifndef _STATICFIELDEXPRESSION_
#define _STATICFIELDEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class Statics;

	class StaticFieldOrEnumExpression : public IExpression {

		String staticName;
		String field;

		friend class SetExpression;
		friend class SwapExpression;

	public:
		StaticFieldOrEnumExpression(const String& staticName, const String& field);

		Value eval(Module& module) override;
	};
}

#endif // _STATICFIELDEXPRESSION_
