#pragma once

#ifndef _TRYCATCHSTATEMENT_
#define _TRYCATCHSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class TryCatchStatement : public IStatement {
		Statement tryBlock;
		String name;
		Statement catchBlock;

	public:

		TryCatchStatement(const Statement& tryBlock, String name, const Statement& catchBlock);
		void execute(Module& module) override;
	};

}

#endif // _TRYCATCHSTATEMENT_