#include "parser/statement/classStatement.h"
#include "parser/statement/cppFunctionStatement.h"
#include "parser/value/classValue.h"
#include "structures/functions.h"
#include "structures/variables.h"

using namespace lotus;

lotus::ClassStatement::ClassStatement(Functions& functions, Variables& variables, const String& name, RawFields_t& fields, const Methods_t& methods, const std::vector<String>& parents)
	: functions(functions), variables(variables), name(name), fields(fields), methods(methods), parents(parents) {
}

void lotus::ClassStatement::execute() {

	if (methods.find(name) != methods.end()) {
		for (auto& method : methods[name]) {
			Function function(MAKE_PTR<CppFunctionStatement>([&]() {
				ClassValue value;
				for (auto& field : fields) {

					FieldMemberInfo memberInfo;
					memberInfo.value = field.second.first ? field.second.first->eval() : UNDEFINED();
					memberInfo.accessModifier = field.second.second.accessModifier;

					value.fields.emplace(field.first, memberInfo);
				}

				for (auto& method : methods) {
					for (size_t i = 0; i < method.second.size(); i++) {
						value.declareMethod(method.first, method.second[i]);
					}
				}
				value.type = name;

				std::vector<ClassValue> parentClasses;
				for (auto& parent : parents) {
					if (auto parentClass = std::dynamic_pointer_cast<ClassValue>(functions.call(parent, {}, variables))) {
						value.parents.push_back(*parentClass);
					}
				}

				std::vector<Value> argsValues;
				for (auto& arg : method.value.args) {
					argsValues.push_back(variables.get(arg.name));
				}
				value.callMethod(name, argsValues, variables);

				RETURN_VALUE(MAKE_PTR<ClassValue>(value));
				}), method.value.args);

			functions.declare(name, function);
		}
	}
	else {
		Function function(MAKE_PTR<CppFunctionStatement>([&]() {
			ClassValue value;
			for (auto& field : fields) {

				FieldMemberInfo memberInfo;
				memberInfo.value = field.second.first ? field.second.first->eval() : UNDEFINED();
				memberInfo.accessModifier = field.second.second.accessModifier;

				value.fields.emplace(field.first, memberInfo);
			}

			for (auto& field : value.fields) {
				if (auto fieldClass = std::dynamic_pointer_cast<ClassValue>(field.second.value)) {
					fieldClass->callMethod(fieldClass->getType(), {}, variables);
				}
			}

			for (auto& method : methods) {
				for (size_t i = 0; i < method.second.size(); i++) {
					value.declareMethod(method.first, method.second[i]);
				}
			}

			value.type = name;

			std::vector<ClassValue> parentClasses;
			for (auto& parent : parents) {
				if (auto parentClass = std::dynamic_pointer_cast<ClassValue>(functions.call(parent, {}, variables))) {
					value.parents.push_back(*parentClass);
				}
			}

			RETURN_VALUE(MAKE_PTR<ClassValue>(value));
			}), {});

		functions.declare(name, function);
	}
}