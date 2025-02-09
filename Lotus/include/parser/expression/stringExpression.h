#pragma once

#ifndef _STRINGEXPRESSION_
#define _STRINGEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class StringExpression : public IExpression {
		String value;

	public:
		StringExpression(const String& value);

		Value eval() override;
	};
}

#endif // _STRINGEXPRESSION_
