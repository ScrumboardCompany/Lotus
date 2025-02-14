#pragma once

#ifndef _DEFSTATEMENT_
#define _DEFSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class Functions;
	class Variables;

	class DefStatement : public IStatement {
		String name;
		Functions& functions;
		Variables& variables;
		std::vector<String> args;

		Statement body;

	public:

		DefStatement(const String& name, Functions& functions, Variables& variables, const Statement& body, std::vector<String> args);
		void execute() override;
	};

}

#endif // _DEFSTATEMENT_