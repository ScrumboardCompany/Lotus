#pragma once

#ifndef _DEFSTATEMENT_
#define _DEFSTATEMENT_

#include "parser/statement/statement.h"
#include "parser/function/function.h"

namespace lotus {

	class DefStatement : public IStatement {
		String name;
		Function function;

	public:

		DefStatement(const String& name, const Function& function);
		void execute(Module& module) override;
	};

}

#endif // _DEFSTATEMENT_