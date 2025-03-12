#include "parser/parser.h"
#include "parser/value/intValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/stringValue.h"
#include "utils/utils.h"
#include "utils/lotusError.h"
#include <thread>

using namespace lotus;

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
		Value& this_time = module.GET("this");

		if (!module.GET("sec")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("sec")->getType(), module);
		if (!module.GET("min")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("min")->getType(), module);
		if (!module.GET("hour")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("hour")->getType(), module);
		if (!module.GET("day")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("day")->getType(), module);
		if (!module.GET("month")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("month")->getType(), module);
		if (!module.GET("year")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("year")->getType(), module);
		if (!module.GET("isdst")->instanceOf("bool")) throwTypeError(STRING_LITERAL("bool"), module.GET("isdst")->getType(), module);

		Int sec = module.GET("sec")->asInt(module);
		Int min = module.GET("min")->asInt(module);
		Int hour = module.GET("hour")->asInt(module);
		Int day = module.GET("day")->asInt(module);
		Int month = module.GET("month")->asInt(module);
		Int year = module.GET("year")->asInt(module);
		Int isdst = module.GET("isdst")->asInt(module);

		if (!isValidDate(day, month, year)) {
			module.THROW(STRING("Invalid date"));
		}

		auto days = evalDayOfYearAndDayOfWeek(day, month, year);

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
		if (!module.GET("time")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("time")->getType(), module);

		Value this_time = module.GET("this");
		Value add_time = module.GET("time");

		int64_t total_seconds = getTotalSeconds(this_time, module) + getTotalSeconds(add_time, module);

		auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds);
		RETURN_VALUE(module.CALL("Time", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), INT(0)));
		}, "time"));

	TimeClass.addMethod("__substract__", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("time")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("time")->getType(), module);

		Value this_time = module.GET("this");
		Value sub_time = module.GET("time");

		int64_t total_seconds = getTotalSeconds(this_time, module) - getTotalSeconds(sub_time, module);

		if (total_seconds < 0) {
			total_seconds = 0;
		}

		auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds);
		RETURN_VALUE(module.CALL("Time", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), INT(0)));
		}, "time"));

	TimeClass.addMethod("__asString__", METHOD(AccessModifierType::PUBLIC, [&] {
		Value this_time = module.GET("this");

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

	Time.CLASS("Time", TimeClass, module, true);

	Static TimeStatic;

	TimeStatic.addMethod("sleep", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("duration")->instanceOf("int")) throwTypeError(STRING_LITERAL("int"), module.GET("duration")->getType(), module);
		std::this_thread::sleep_for(std::chrono::milliseconds(module.GET("duration")->asInt(module)));
		}, "duration"));

	TimeStatic.addMethod("now", METHOD(AccessModifierType::PUBLIC, [&] {

		auto now = std::chrono::system_clock::now();
		std::time_t now_time = std::chrono::system_clock::to_time_t(now);

		std::tm end_time;

#ifdef _WIN32
		localtime_s(&end_time, &now_time);
#else
		localtime_r(&now_time, &end_time);
#endif

		RETURN_VALUE(module.CALL("Time",
			INT(end_time.tm_sec),
			INT(end_time.tm_min),
			INT(end_time.tm_hour),
			INT(end_time.tm_mday),
			INT(end_time.tm_mon + 1),
			INT(end_time.tm_year + 1900),
			INT(end_time.tm_isdst)
		));
		}));

	Time.STATIC("Time", TimeStatic);
	modules.emplace(STRING_LITERAL("Time"), Time);
}