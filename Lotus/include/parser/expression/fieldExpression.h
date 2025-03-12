#pragma once

#ifndef _FIELDEXPRESSION_
#define _FIELDEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class FieldExpression : public IExpression {

		Expression expr;
		String field;

		friend class SetExpression;
		friend class SwapExpression;

	public:
		FieldExpression(const Expression& expr, const String& field);

		Value eval(Module& module) override;
	};
}

#endif // _FIELDEXPRESSION_
