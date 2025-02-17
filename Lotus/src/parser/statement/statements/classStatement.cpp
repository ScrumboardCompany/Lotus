#include "parser/statement/classStatement.h"
#include "parser/statement/cppFunctionStatement.h"
#include "parser/value/classValue.h"
#include "structures/functions.h"

using namespace lotus;

lotus::ClassStatement::ClassStatement(Functions& functions, const String& name, RawFields_t& fields, const Methods_t& methods)
	: functions(functions), name(name), fields(fields), methods(methods) {
}

void lotus::ClassStatement::execute() {

	Function function(MAKE_PTR<CppFunctionStatement>([&](Variables&) {
		ClassValue value;
		for (auto& field : fields) {

			FieldMemberInfo memberInfo;
			memberInfo.value = field.second.first ? field.second.first->eval() : UNDEFINED();
			memberInfo.accessModifier = field.second.second.accessModifier;

			value.fields.emplace(field.first, memberInfo);
		}

		value.methods = methods;
		value.type = name;

		RETURN_VALUE(MAKE_PTR<ClassValue>(value));
		}), std::vector<String>());

	functions.declare(name, function);
}