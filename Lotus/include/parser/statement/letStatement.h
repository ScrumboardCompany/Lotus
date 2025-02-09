#pragma once

#ifndef _LETSTATEMENT_
#define _LETSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"
#include "structures/variables.h"

namespace lotus {

	class LetStatement : public IStatement {
		String name;
		Expression expression;
		Variables& variables;
	public:

		LetStatement(const String& name, Expression expression, Variables& variables);
		void execute() override;
	};

}

#endif // _LETSTATEMENT_