#include "parser/statement/classStatement.h"
#include "parser/statement/cppFunctionStatement.h"
#include "parser/value/classValue.h"
#include "structures/functions.h"

using namespace lotus;

lotus::ClassStatement::ClassStatement(Functions& functions, const String& name, const StringMap<Expression>& fields, const StringMap<Function>& methods)
	: functions(functions), name(name), fields(fields), methods(methods) {
}

void lotus::ClassStatement::execute() {

	Function function(MAKE_PTR<CppFunctionStatement>([&](Variables&) {
		ClassValue value;
		for (auto& field : fields) {
			value.fields.emplace(field.first, field.second ? field.second->eval() : UNDEFINED());
		}

		value.methods = methods;
		value.type = name;

		RETURN_VALUE(MAKE_PTR<ClassValue>(value));
		}), std::vector<String>());

	functions.declare(name, function);
}