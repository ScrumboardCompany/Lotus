#pragma once

#ifndef _CLASSSTATEMENT_
#define _CLASSSTATEMENT_

#include "parser/statement/statement.h"
#include "structures/classStructures.h"

namespace lotus {

	class Classes;
	class Functions;
	class Function;

	class ClassStatement : public IStatement {
		String name;
		RawFields_t fields;
		Methods_t methods;
		std::vector<String> parents;

	public:

		ClassStatement(const String& name, RawFields_t& fields, const Methods_t& methods, const std::vector<String>& parents);
		void execute(Module& module) override;
	};

}

#endif // _CLASSSTATEMENT_