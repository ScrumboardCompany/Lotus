#pragma once

#ifndef _CLASSSTATEMENT_
#define _CLASSSTATEMENT_

#include "parser/statement/statement.h"
#include "structures/classStructures.h"

namespace lotus {

	class Functions;
	class Function;

	class ClassStatement : public IStatement {
		String name;
		RawFields_t fields;
		Methods_t methods;
		Functions& functions;
		Variables& variables;

	public:

		ClassStatement(Functions& functions, Variables& variables, const String& name, RawFields_t& fields, const Methods_t& methods);
		void execute() override;
	};

}

#endif // _CLASSSTATEMENT_