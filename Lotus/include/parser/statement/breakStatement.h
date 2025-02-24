#pragma once

#ifndef _BREAKSTATEMENT_
#define _BREAKSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class BreakStatement : public IStatement {

	public:

		BreakStatement();
		void execute(Module&) override;
	};

}

#endif // _BREAKSTATEMENT_