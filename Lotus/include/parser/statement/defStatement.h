#pragma once

#ifndef _DEFSTATEMENT_
#define _DEFSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class Functions;

	class DefStatement : public IStatement {
		String name;
		Functions& functions;

		Statement body;

	public:

		DefStatement(const String& name, Functions& functions, const Statement& body);
		void execute() override;
	};

}

#endif // _DEFSTATEMENT_