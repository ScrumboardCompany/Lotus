#pragma once

#ifndef _STATEMENT_
#define _STATEMENT_

#include "parser/expression/expression.h"

namespace lotus {

	struct Module;

	class IStatement {
	public:
		virtual void execute(Module& module) = 0;
		virtual ~IStatement() = default;
	};

}

#endif // _STATEMENT_