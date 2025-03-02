#include "parser/parser.h"
#include "parser/value/stringValue.h"
#include "parser/value/intValue.h"
#include "parser/value/floatValue.h"
#include "parser/value/boolValue.h"
#include "utils/lotusError.h"
#include "structures/module.h"
#include <iostream>
#include <thread>
#include <string>
#include <locale>
#include <codecvt>
#include "utils/utils.h"
#include <chrono>
#include "parser/value/objectValue.h"

void lotus::Parser::loadModules() {

	module.DEF("throw", [&] {
		THROW_EMPTY(module);
		});

	module.DEF("throw", [&] {
		THROW(module, module.GET("msg"));
		}, "msg");

	module.DEF("throw", [&] {
		THROW_WITH_TYPE(module, module.GET("msg"), module.GET("type"));
		}, "msg", "type");

	module.DEF("print", [&] {
		Value args = module.variables.get("args");
		for (int i = 0, size = args->size(module)->asInt(module); i < size; i++) {
			std::wcout << args->getOfIndex(INT(i), module)->asString(module);
		}
		}, "args...");

	module.DEF("println", [&] {
		Value args = module.variables.get("args");
		for (int i = 0, size = args->size(module)->asInt(module); i < size; i++) {
			std::wcout << args->getOfIndex(INT(i), module)->asString(module) << std::endl;
		}
		}, "args...");

	module.DEF("input", [&] {
		String input;
		std::wcin >> input;
		RETURN_VALUE(STRING(input));
		});

	module.DEF("typeof", [&] {
		RETURN_VALUE(STRING(module.variables.get("arg")->getType()));
		}, "arg");

	module.DEF("size", [&] {
		RETURN_VALUE(module.variables.get("arg")->size(module));
		}, "arg");

	module.DEF("sizeof", [&] {
		RETURN_VALUE(module.variables.get("arg")->sizeInRam());
		}, "arg");

	module.DEF("int", [&] {
		RETURN_VALUE(INT(module.variables.get("arg")->asInt(module)));
		}, "arg");

	module.DEF("float", [&] {
		RETURN_VALUE(FLOAT(module.variables.get("arg")->asDouble(module)));
		}, "arg");

	module.DEF("string", [&] {
		RETURN_VALUE(STRING(module.variables.get("arg")->asString(module)));
		}, "arg");

	module.DEF("bool", [&] {
		RETURN_VALUE(BOOL(module.variables.get("arg")->asBool(module)));
		}, "arg");

	Class exceptionClass;

	exceptionClass.addField("__msg", FIELD(AccessModifierType::PRIVATE, STRING("")));
	exceptionClass.addField("__type", FIELD(AccessModifierType::PRIVATE, STRING("error")));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [&] {}));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [&] {
		module.GET("this")->getField("__msg") = module.GET("msg");
		}, "msg"));

	exceptionClass.addMethod("exception", METHOD(AccessModifierType::PUBLIC, [&] {
		module.GET("this")->getField("__msg") = module.GET("msg");
		module.GET("this")->getField("__type") = module.GET("type");
		}, "msg", "type"));

	exceptionClass.addMethod("message", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.variables.get("this")->getField("__msg"));
		}));

	exceptionClass.addMethod("type", METHOD(AccessModifierType::PUBLIC, [&] {
		RETURN_VALUE(module.variables.get("this")->getField("__type"));
		}));

	module.CLASS("exception", exceptionClass);

	loadMathModule();
	loadTimeModule();
}

void lotus::Parser::loadMathModule() {
	Module Math;
	Static MathStatic;

	MathStatic.addField("PI", FieldMemberInfo(FLOAT(3.14342354), AccessModifierType::PUBLIC));
	MathStatic.addField("E", FieldMemberInfo(FLOAT(2.7182818284), AccessModifierType::PUBLIC));

	MathStatic.addMethod("absolute", MethodMemberInfo(MAKE_CPP_FUNCTION([&] {
		if (module.variables.get("arg")->getType() == STRING_LITERAL("int")) RETURN_VALUE(INT(std::abs(module.variables.get("arg")->asInt(module))));
		RETURN_VALUE(FLOAT(std::abs(module.variables.get("arg")->asDouble(module))));
		}, "arg"), AccessModifierType::PUBLIC));

	MathStatic.addMethod("round", MethodMemberInfo(MAKE_CPP_FUNCTION([&] {
		RETURN_VALUE(INT(module.variables.get("arg")->asInt(module)));
		}, "arg"), AccessModifierType::PUBLIC));

	MathStatic.addMethod("min", MethodMemberInfo(MAKE_CPP_FUNCTION([&] {
		RETURN_VALUE(FLOAT(std::min(module.variables.get("arg1")->asDouble(module), module.variables.get("arg2")->asDouble(module))));
		}, "arg1", "arg2"), AccessModifierType::PUBLIC));

	MathStatic.addMethod("max", MethodMemberInfo(MAKE_CPP_FUNCTION([&] {
		RETURN_VALUE(FLOAT(std::max(module.variables.get("arg1")->asDouble(module), module.variables.get("arg2")->asDouble(module))));
		}, "arg1", "arg2"), AccessModifierType::PUBLIC));

	MathStatic.addMethod("sqrt", MethodMemberInfo(MAKE_CPP_FUNCTION([&] {
		RETURN_VALUE(FLOAT(std::sqrt(module.variables.get("arg")->asDouble(module))));
		}, "arg"), AccessModifierType::PUBLIC));

	Math.STATIC("Math", MathStatic);
	modules.emplace(STRING_LITERAL("Math"), Math);
}

void lotus::Parser::loadTimeModule() {
	Module Time;
	Class TimeClass;

	TimeClass.addField("sec", FIELD(AccessModifierType::PUBLIC, INT(0)));
	TimeClass.addField("min", FIELD(AccessModifierType::PUBLIC, INT(0)));
	TimeClass.addField("hour", FIELD(AccessModifierType::PUBLIC, INT(0)));
	TimeClass.addField("day", FIELD(AccessModifierType::PUBLIC, INT(0)));
	TimeClass.addField("month", FIELD(AccessModifierType::PUBLIC, INT(0)));
	TimeClass.addField("year", FIELD(AccessModifierType::PUBLIC, INT(0)));
	TimeClass.addField("day_of_year", FIELD(AccessModifierType::PUBLIC, INT(0)));
	TimeClass.addField("day_of_week", FIELD(AccessModifierType::PUBLIC, INT(0)));
	TimeClass.addField("isdst", FIELD(AccessModifierType::PUBLIC, BOOL(false)));

	// default ctor
	TimeClass.addMethod("Time", METHOD(AccessModifierType::PUBLIC, [&] {}));

	// ctor with specified time
	TimeClass.addMethod("Time", METHOD(AccessModifierType::PUBLIC, [&] {
	Value& this_time = module.variables.get("this");

	int sec = module.variables.get("sec")->asInt(module);
	int min = module.variables.get("min")->asInt(module);
	int hour = module.variables.get("hour")->asInt(module);
	int day = module.variables.get("day")->asInt(module);
	int month = module.variables.get("month")->asInt(module);
	int year = module.variables.get("year")->asInt(module);
	int isdst = module.variables.get("isdst")->asInt(module);

	if (!isValidDate(day, month, year)) {
		throw std::runtime_error("Invalid date");
	}
	
	auto days = evalDayOfYearAndDayOfWeek(sec, min, hour, day, month, year);

	this_time->getField("sec") = INT(sec);
	this_time->getField("min") = INT(min);
	this_time->getField("hour") = INT(hour);
	this_time->getField("day") = INT(day);
	this_time->getField("month") = INT(month);
	this_time->getField("year") = INT(year);
	this_time->getField("day_of_year") = INT(days.first);
	this_time->getField("day_of_week") = INT(days.second);
	this_time->getField("isdst") = INT(isdst);
		}, "sec", "min", "hour", "day", "month", "year", "isdst"));

	TimeClass.addMethod("__add__", METHOD(AccessModifierType::PUBLIC, [&] {
	Value this_time = module.variables.get("this");
	Value add_time = module.variables.get("time");

	int64_t total_seconds = getTotalSeconds(this_time, module) + getTotalSeconds(add_time, module);

	auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds);
	RETURN_VALUE(module.CALL("Time", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), INT(0)));
			}, "time"));

	TimeClass.addMethod("__substract__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value this_time = module.variables.get("this");
		Value sub_time = module.variables.get("time");

		int64_t total_seconds = getTotalSeconds(this_time, module) - getTotalSeconds(sub_time, module);

		if (total_seconds < 0) {
			total_seconds = 0;
		}

		auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds);
		RETURN_VALUE(module.CALL("Time", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), INT(0)));
		}, "time"));

	TimeClass.addMethod("__asString__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value this_time = module.variables.get("this");

		String result;
		
		result += this_time->getField("day")->asString(module);
		result += STRING_LITERAL("/");
		result += this_time->getField("month")->asString(module);
		result += STRING_LITERAL("/");
		result += this_time->getField("year")->asString(module);
		result += STRING_LITERAL(" ");

		result += this_time->getField("hour")->asString(module);
		result += STRING_LITERAL(":");
		result += this_time->getField("min")->asString(module);
		result += STRING_LITERAL(":");
		result += this_time->getField("sec")->asString(module);

		RETURN_VALUE(STRING(result));
		}));

	Time.CLASS("Time", TimeClass);

	Static TimeStatic;

	TimeStatic.addMethod("sleep", MethodMemberInfo(MAKE_CPP_FUNCTION([&] {
		std::this_thread::sleep_for(std::chrono::milliseconds(module.variables.get("duration")->asInt(module)));
		}, "duration"), AccessModifierType::PUBLIC));

	TimeStatic.addMethod("now", MethodMemberInfo(MAKE_CPP_FUNCTION([&] {

		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		std::tm end_time;

		lotus::localtime(&end_time, &now_time);

		RETURN_VALUE(module.CALL("Time",
			INT(end_time.tm_sec),
			INT(end_time.tm_min),
			INT(end_time.tm_hour),
			INT(end_time.tm_mday),
			INT(end_time.tm_mon + 1),
			INT(end_time.tm_year + 1900),
			INT(end_time.tm_isdst)
			));
		}), AccessModifierType::PUBLIC));

	Time.STATIC("Time", TimeStatic);
	modules.emplace(STRING_LITERAL("Time"), Time);
}