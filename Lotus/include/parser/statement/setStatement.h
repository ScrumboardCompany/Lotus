#pragma once

#ifndef _SETSTATEMENT_
#define _SETSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"
#include "structures/variables.h"

namespace lotus {

	class SetStatement : public IStatement {
		String name;
		Expression expression;
		Variables& variables;
	public:

		SetStatement(const String& name, Expression expression, Variables& variables);
		void execute() override;
	};

}

#endif // _SETSTATEMENT_