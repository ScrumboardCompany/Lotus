#pragma once

#ifndef _STATICSTATEMENT_
#define _STATICSTATEMENT_

#include "parser/statement/statement.h"

namespace lotus {

	class Statics;

	class StaticStatement : public IStatement {
		String name;
		RawFields_t fields;
		Methods_t methods;

	public:

		StaticStatement(const String& name, RawFields_t& fields, const Methods_t& methods);
		void execute(Module& module) override;
	};

}

#endif // _STATICSTATEMENT_