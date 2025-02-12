#pragma once

#ifndef _RETURNSTATEMENT_
#define _RETURNSTATEMENT_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"
#include "parser/statement/statement.h"

namespace lotus {

	class ReturnStatement : public IStatement {
		Expression expr;

	public:

		ReturnStatement(const Expression& expr);
		void execute() override;
	};

}

#endif // _RETURNSTATEMENT_