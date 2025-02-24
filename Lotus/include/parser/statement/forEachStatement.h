#pragma once

#ifndef _FOREACHSTATEMENT_
#define _FOREACHSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class Variables;

	class ForEachStatement : public IStatement {
		Expression expression;
		String name;
		Statement body;

	public:

		ForEachStatement(const Expression& expression, const String& name, const Statement& body);
		void execute(Module& module) override;
	};

}

#endif // _FOREACHSTATEMENT_