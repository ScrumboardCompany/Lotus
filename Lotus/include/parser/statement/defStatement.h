#pragma once

#ifndef _DEFSTATEMENT_
#define _DEFSTATEMENT_

#include "parser/statement/statement.h"
#include "parser/function/function.h"

namespace lotus {

	class Functions;
	class Variables;

	class DefStatement : public IStatement {
		String name;
		Functions& functions;
		Variables& variables;
		Function function;

	public:

		DefStatement(const String& name, Functions& functions, Variables& variables, const Function& function);
		void execute() override;
	};

}

#endif // _DEFSTATEMENT_