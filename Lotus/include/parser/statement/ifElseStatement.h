#pragma once

#ifndef _IFELSESTATEMENT_
#define _IFELSESTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class Variables;

	class IfElseStatement : public IStatement {
		std::vector<Expression> conditionPart;
		Statement ifBody;
		Statement elseBody;
		Variables& variables;

	public:

		IfElseStatement(std::vector<Expression> conditionPart, Statement ifBody, Statement elseBody, Variables& variables);
		void execute() override;
	};

}

#endif // _IFELSESTATEMENT_