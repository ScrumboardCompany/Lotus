#pragma once

#ifndef _CLASSSTATEMENT_
#define _CLASSSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class Functions;
	class Function;

	class ClassStatement : public IStatement {
		String name;
		StringMap<Expression> fields;
		StringMap<Function> methods;
		Functions& functions;

	public:

		ClassStatement(Functions& functions, const String& name, const StringMap<Expression>& fields, const StringMap<Function>& methods);
		void execute() override;
	};

}

#endif // _CLASSSTATEMENT_