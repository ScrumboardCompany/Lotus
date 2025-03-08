#pragma once

#ifndef _MODULE_
#define _MODULE_

#include "structures/variables.h"
#include "structures/functions.h"
#include "structures/statics.h"
#include "structures/classes.h"
#include "structures/flags.h"
#include "parser/statement/cppFunctionStatement.h"

//#define LET(name, value) variables.declare(STRING_LITERAL(name), value)
//#define SET(name, value) variables.set(STRING_LITERAL(name), value)
//#define GET(name) variables.get(STRING_LITERAL(name))
//#define DEF(name, body, ...) functions.declare(STRING_LITERAL(name), MAKE_CPP_FUNCTION(body, __VA_ARGS__))
//#define CALL(module, name, ...) functions.call(name, {__VA_ARGS__}, module)
//#define CALL_SPECIFY(module, name, args, specifiedArgs) functions.call(name, args, specifiedArgs, module)
//#define STATIC(name, value) statics.declare(STRING_LITERAL(name), value)
//#define CLASS(module, name, value) classes.declare(name, MAKE_PTR<Class>(value))
//#define METHOD(accessModifier, body, ...) MethodMemberInfo(MAKE_CPP_FUNCTION(body, __VA_ARGS__), accessModifier)
//#define FIELD(accessModifier, value) FieldMemberInfo(value, accessModifier)

namespace lotus {

	template <typename... Args>
	Function MAKE_CPP_FUNCTION(std::function<void()> body, Args&&... args) {
		return Function(
			MAKE_PTR<CppFunctionStatement>(body),
			{ std::forward<Args>(args)... },
			int()
		);
	}

	template <typename... Args>
	MethodMemberInfo METHOD(const AccessModifierType& accessModifier, std::function<void()> body, Args&&... args) {
		return MethodMemberInfo(MAKE_CPP_FUNCTION(body, std::forward<Args>(args)...), accessModifier);
	}

	FieldMemberInfo FIELD(const AccessModifierType& accessModifier, const Value& value);

	struct Module {
		Variables variables;
		Functions functions;
		Statics statics;
		Classes classes;
		Flags flags;

		void LET(const String& name, const Value& value);

		void LET(const char* name, const Value& value);

		void SET(const String& name, const Value& value);

		void SET(const char* name, const Value& value);

		Value& GET(const String& name);

		Value& GET(const char* name);

		template <typename... Args>
		void DEF(const String& name, std::function<void()> body, Args&&... args) {
			functions.declare(name, MAKE_CPP_FUNCTION(body, std::forward<Args>(args)...));
		}

		template <typename... Args>
		void DEF(const char* name, std::function<void()> body, Args&&... args) {
			DEF(STRING_VAR_LITERAL(name), body, std::forward<Args>(args)...);
		}

		template <typename... Args>
		auto CALL(const String& name, Args&&... args) {
			return functions.call(name, { std::forward<Args>(args)... }, *this);
		}

		template <typename... Args>
		auto CALL(const char* name, Args&&... args) {
			return CALL(STRING_VAR_LITERAL(name), std::forward<Args>(args)...);
		}

		auto CALL(const String& name, const std::vector<Value>& args, const StringMap<Value>& specifiedArgs) {
			return functions.call(name, args, specifiedArgs, *this);
		}

		auto CALL(const char* name, const std::vector<Value>& args, const StringMap<Value>& specifiedArgs) {
			return CALL(STRING_VAR_LITERAL(name), args, specifiedArgs);
		}

		void STATIC(const String& name, const Static& value);

		void STATIC(const char* name, const Static& value);

		void CLASS(const String& name, const Class& value, bool doRegister = false);

		void CLASS(const char* name, const Class& value, bool doRegister = false);

		[[noreturn]] void THROW();

		[[noreturn]] void THROW(const Value& msg);

		[[noreturn]] void THROW(const Value& msg, const Value& type);

	};

}

#endif // _MODULE_