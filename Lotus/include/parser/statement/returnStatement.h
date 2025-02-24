#pragma once

#ifndef _RETURNSTATEMENT_
#define _RETURNSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class ReturnStatement : public IStatement {
		Expression expr;

	public:

		ReturnStatement(const Expression& expr);

		void execute(Module& module) override;
	};

}

#endif // _RETURNSTATEMENT_