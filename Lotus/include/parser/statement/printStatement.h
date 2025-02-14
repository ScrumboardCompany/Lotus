#pragma once

#ifndef _PRINTSTATEMENT_
#define _PRINTSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class PrintStatement : public IStatement {
		Expression arg;
	public:

		PrintStatement(const Expression& arg);
		void execute() override;
	};

}

#endif // _PRINTSTATEMENT_