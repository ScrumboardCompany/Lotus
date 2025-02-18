#pragma once

#ifndef _STATICSTATEMENT_
#define _STATICSTATEMENT_

#include "parser/statement/statement.h"
#include "structures/classStructures.h"

namespace lotus {

	class Statics;

	class StaticStatement : public IStatement {
		String name;
		RawFields_t fields;
		Methods_t methods;
		Statics& statics;

	public:

		StaticStatement(Statics& statics, const String& name, RawFields_t& fields, const Methods_t& methods);
		void execute() override;
	};

}

#endif // _STATICSTATEMENT_