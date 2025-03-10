#pragma once

#ifndef _ENUMSTATEMENT_
#define _ENUMSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class EnumStatement : public IStatement {
		String name;
		StringMap<Expression> elements;

	public:

		EnumStatement(const String& name, const StringMap<Expression>& elements);
		void execute(Module& module) override;
	};
}

#endif // _ENUMSTATEMENT_