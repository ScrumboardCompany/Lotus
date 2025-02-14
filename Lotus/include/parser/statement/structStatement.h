#pragma once

#ifndef _STRUCTSTATEMENT_
#define _STRUCTSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class Functions;

	class StructStatement : public IStatement {
		String name;
		StringMap<Expression> fields;
		Functions& functions;

	public:

		StructStatement(Functions& functions, const String& name, const StringMap<Expression>& fields);
		void execute() override;
	};

}

#endif // _STRUCTSTATEMENT_