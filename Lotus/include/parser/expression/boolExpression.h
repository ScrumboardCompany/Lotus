#pragma once

#ifndef _BOOLEXPRESSION_
#define _BOOLEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class BoolExpression : public IExpression {
		bool value;

	public:
		BoolExpression(bool value);

		Value eval() override;
	};
}

#endif // _BOOLEXPRESSION_
