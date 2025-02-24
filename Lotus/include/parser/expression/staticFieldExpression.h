#pragma once

#ifndef _STATICFIELDEXPRESSION_
#define _STATICFIELDEXPRESSION_

#include "parser/expression/expresion.h"

namespace lotus {

	class Statics;

	class StaticFieldExpression : public IExpression {

		String staticName;
		String field;

		friend class SetExpression;

	public:
		StaticFieldExpression(const String& staticName, const String& field);

		Value eval(Module& module) override;
	};
}

#endif // _STATICFIELDEXPRESSION_
