#pragma once

#ifndef _BOOLEXPRESSION_
#define _BOOLEXPRESSION_

#include "parser/expression/expression.h"

namespace lotus {

	class BoolExpression : public IExpression {
		bool value;

	public:
		BoolExpression(bool value);

		Value eval(Module&) override;
	};
}

#endif // _BOOLEXPRESSION_
