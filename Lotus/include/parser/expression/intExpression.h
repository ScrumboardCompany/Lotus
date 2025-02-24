#pragma once

#ifndef _INTEXPRESSION_
#define _INTEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class IntExpression : public IExpression {
		int value;

	public:
		IntExpression(int value);

		Value eval(Module&) override;
	};
}

#endif // _INTEXPRESSION_
