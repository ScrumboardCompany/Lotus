#include "parser/statement/structStatement.h"
#include "parser/statement/cppFunctionStatement.h"
#include "parser/value/structValue.h"
#include "structures/functions.h"

using namespace lotus;

lotus::StructStatement::StructStatement(Functions& functions, const String& name, const StringMap<Expression>& fields)
	: functions(functions), name(name), fields(fields) {
}

void lotus::StructStatement::execute() {

	Function function(MAKE_PTR <CppFunctionStatement>([&](Variables&) {
		Value value = MAKE_PTR<StructValue>();
		for (auto& field : fields) {
			value->fields.emplace(field.first, field.second ? field.second->eval() : UNDEFINED());
		}

		value->type = name;

		RETURN_VALUE(value);
		}), std::vector<String>());

	functions.declare(name, function);
}