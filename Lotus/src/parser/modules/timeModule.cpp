#include "parser/parser.h"
#include "parser/value/intValue.h"
#include "parser/value/boolValue.h"
#include "parser/value/stringValue.h"
#include "utils/utils.h"
#include "utils/lotusError.h"
#include <thread>

using namespace lotus;

void lotus::Parser::loadTimeModule() {
    static Module Time;

    // Declare enum for time units
    Enum TimeUnitEnum;
    TimeUnitEnum.addElement("Second", UNDEFINED(), Time);
    TimeUnitEnum.addElement("Minute", UNDEFINED(), Time);
    TimeUnitEnum.addElement("Hour", UNDEFINED(), Time);
    TimeUnitEnum.addElement("Day", UNDEFINED(), Time);
    TimeUnitEnum.addElement("Month", UNDEFINED(), Time);
    TimeUnitEnum.addElement("Year", UNDEFINED(), Time);
    Time.ENUM("TimeUnit", TimeUnitEnum);

    Class DateClass;

    // Fields
    DateClass.addField("sec", FIELD(AccessModifierType::PRIVATE, INT(0)));
    DateClass.addField("min", FIELD(AccessModifierType::PRIVATE, INT(0)));
    DateClass.addField("hour", FIELD(AccessModifierType::PRIVATE, INT(0)));
    DateClass.addField("day", FIELD(AccessModifierType::PRIVATE, INT(0)));
    DateClass.addField("month", FIELD(AccessModifierType::PRIVATE, INT(0)));
    DateClass.addField("year", FIELD(AccessModifierType::PRIVATE, INT(0)));
    DateClass.addField("day_of_year", FIELD(AccessModifierType::PRIVATE, INT(0)));
    DateClass.addField("day_of_week", FIELD(AccessModifierType::PRIVATE, INT(0)));
    DateClass.addField("isdst", FIELD(AccessModifierType::PRIVATE, BOOL(false)));

    // Default ctor
    DateClass.addMethod("Date", METHOD(AccessModifierType::PUBLIC, [](Module& module) {}));

    // Ctor with paramaters
    DateClass.addMethod("Date", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value& this_time = module.GET("this");

        if (!module.GET("sec")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("sec")->getType(), module);
        if (!module.GET("min")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("min")->getType(), module);
        if (!module.GET("hour")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("hour")->getType(), module);
        if (!module.GET("day")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("day")->getType(), module);
        if (!module.GET("month")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("month")->getType(), module);
        if (!module.GET("year")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("year")->getType(), module);
        if (!module.GET("isdst")->instanceOf("bool"))
            throwTypeError(STRING_LITERAL("bool"), module.GET("isdst")->getType(), module);

        Int sec = module.GET("sec")->asInt(module);
        Int min = module.GET("min")->asInt(module);
        Int hour = module.GET("hour")->asInt(module);
        Int day = module.GET("day")->asInt(module);
        Int month = module.GET("month")->asInt(module);
        Int year = module.GET("year")->asInt(module);
        Int isdst = module.GET("isdst")->asInt(module);

        if (day != 0 && month != 0 && year != 0) {
            if (!isValidDate(day, month, year)) {
                module.THROW(STRING("Invalid date"));
            }
            auto days = evalDayOfYearAndDayOfWeek(day, month, year);
            this_time->getField("day_of_year") = INT(days.first);
            this_time->getField("day_of_week") = INT(days.second);
        }
        else {
            this_time->getField("day_of_year") = INT(0);
            this_time->getField("day_of_week") = INT(0);
        }

        this_time->getField("sec") = INT(sec);
        this_time->getField("min") = INT(min);
        this_time->getField("hour") = INT(hour);
        this_time->getField("day") = INT(day);
        this_time->getField("month") = INT(month);
        this_time->getField("year") = INT(year);
        this_time->getField("isdst") = INT(isdst);

        int64_t total_seconds = getTotalSeconds(this_time, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (day != 0 && month != 0 && year != 0);
        auto [n_sec, n_min, n_hour, n_day, n_month, n_year] = fromTotalSeconds(total_seconds, absolute);
        this_time->getField("sec") = INT(n_sec);
        this_time->getField("min") = INT(n_min);
        this_time->getField("hour") = INT(n_hour);
        this_time->getField("day") = INT(n_day);
        this_time->getField("month") = INT(n_month);
        this_time->getField("year") = INT(n_year);
        if (absolute) {
            auto days = evalDayOfYearAndDayOfWeek(n_day, n_month, n_year);
            this_time->getField("day_of_year") = INT(days.first);
            this_time->getField("day_of_week") = INT(days.second);
        }
        }, "sec", "min", "hour", "day", "month", "year", "isdst"));

    // Operator overload +
    DateClass.addMethod("__add__", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        if (!module.GET("time")->instanceOf("Date"))
            throwTypeError(STRING_LITERAL("Date"), module.GET("time")->getType(), module);
        Value this_time = module.GET("this");
        Value add_time = module.GET("time");
        int64_t total_seconds = getTotalSeconds(this_time, module) + getTotalSeconds(add_time, module);
        bool absolute = (module.GET("this")->getField("day")->asInt(module) != 0 &&
            module.GET("this")->getField("month")->asInt(module) != 0 &&
            module.GET("this")->getField("year")->asInt(module) != 0);
        auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds, absolute);
        RETURN_VALUE(module.CALL("Date", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), BOOL(0)));
        }, "time"));

    // Operator overload -
    DateClass.addMethod("__substract__", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        if (!module.GET("time")->instanceOf("Date"))
            throwTypeError(STRING_LITERAL("Date"), module.GET("time")->getType(), module);
        Value this_time = module.GET("this");
        Value sub_time = module.GET("time");
        int64_t total_seconds = getTotalSeconds(this_time, module) - getTotalSeconds(sub_time, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (module.GET("this")->getField("day")->asInt(module) != 0 &&
            module.GET("this")->getField("month")->asInt(module) != 0 &&
            module.GET("this")->getField("year")->asInt(module) != 0);
        auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds, absolute);
        RETURN_VALUE(module.CALL("Date", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), BOOL(0)));
        }, "time"));

    // __asString__
    DateClass.addMethod("__asString__", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
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

    // Getters
    DateClass.addMethod("getSec", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        RETURN_VALUE(module.GET("this")->getField("sec"));
        }));
    DateClass.addMethod("getMin", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        RETURN_VALUE(module.GET("this")->getField("min"));
        }));
    DateClass.addMethod("getHour", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        RETURN_VALUE(module.GET("this")->getField("hour"));
        }));
    DateClass.addMethod("getDay", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        RETURN_VALUE(module.GET("this")->getField("day"));
        }));
    DateClass.addMethod("getWeekDay", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        RETURN_VALUE(INT(evalDayOfYearAndDayOfWeek(
            this_time->getField("day")->asInt(module),
            this_time->getField("month")->asInt(module),
            this_time->getField("year")->asInt(module)).second));
        }));
    DateClass.addMethod("getYearDay", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        RETURN_VALUE(INT(evalDayOfYearAndDayOfWeek(
            this_time->getField("day")->asInt(module),
            this_time->getField("month")->asInt(module),
            this_time->getField("year")->asInt(module)).first));
        }));
    DateClass.addMethod("getMonth", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        RETURN_VALUE(module.GET("this")->getField("month"));
        }));
    DateClass.addMethod("getYear", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        RETURN_VALUE(module.GET("this")->getField("year"));
        }));
    DateClass.addMethod("getIsDst", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        RETURN_VALUE(module.GET("this")->getField("isdst"));
        }));

    // Setters

    DateClass.addMethod("setSec", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        if (!module.GET("value")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("value")->getType(), module);
        Int newVal = module.GET("value")->asInt(module);
        this_time->getField("sec") = INT(newVal);
        int64_t total_seconds = getTotalSeconds(this_time, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [s, m, h, d, mon, y] = fromTotalSeconds(total_seconds, absolute);
        this_time->getField("sec") = INT(s);
        this_time->getField("min") = INT(m);
        this_time->getField("hour") = INT(h);
        this_time->getField("day") = INT(d);
        this_time->getField("month") = INT(mon);
        this_time->getField("year") = INT(y);
        if (absolute) {
            auto days = evalDayOfYearAndDayOfWeek(d, mon, y);
            this_time->getField("day_of_year") = INT(days.first);
            this_time->getField("day_of_week") = INT(days.second);
        }
        else {
            this_time->getField("day_of_year") = INT(0);
            this_time->getField("day_of_week") = INT(0);
        }
        }, "value"));

    DateClass.addMethod("setMin", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        if (!module.GET("value")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("value")->getType(), module);
        Int newVal = module.GET("value")->asInt(module);
        this_time->getField("min") = INT(newVal);
        int64_t total_seconds = getTotalSeconds(this_time, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [s, m, h, d, mon, y] = fromTotalSeconds(total_seconds, absolute);
        this_time->getField("sec") = INT(s);
        this_time->getField("min") = INT(m);
        this_time->getField("hour") = INT(h);
        this_time->getField("day") = INT(d);
        this_time->getField("month") = INT(mon);
        this_time->getField("year") = INT(y);
        if (absolute) {
            auto days = evalDayOfYearAndDayOfWeek(d, mon, y);
            this_time->getField("day_of_year") = INT(days.first);
            this_time->getField("day_of_week") = INT(days.second);
        }
        else {
            this_time->getField("day_of_year") = INT(0);
            this_time->getField("day_of_week") = INT(0);
        }
        }, "value"));

    DateClass.addMethod("setHour", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        if (!module.GET("value")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("value")->getType(), module);
        Int newVal = module.GET("value")->asInt(module);
        this_time->getField("hour") = INT(newVal);
        int64_t total_seconds = getTotalSeconds(this_time, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [s, m, h, d, mon, y] = fromTotalSeconds(total_seconds, absolute);
        this_time->getField("sec") = INT(s);
        this_time->getField("min") = INT(m);
        this_time->getField("hour") = INT(h);
        this_time->getField("day") = INT(d);
        this_time->getField("month") = INT(mon);
        this_time->getField("year") = INT(y);
        if (absolute) {
            auto days = evalDayOfYearAndDayOfWeek(d, mon, y);
            this_time->getField("day_of_year") = INT(days.first);
            this_time->getField("day_of_week") = INT(days.second);
        }
        else {
            this_time->getField("day_of_year") = INT(0);
            this_time->getField("day_of_week") = INT(0);
        }
        }, "value"));

    DateClass.addMethod("setDay", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        if (!module.GET("value")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("value")->getType(), module);
        Int newVal = module.GET("value")->asInt(module);
        this_time->getField("day") = INT(newVal);
        int64_t total_seconds = getTotalSeconds(this_time, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [s, m, h, d, mon, y] = fromTotalSeconds(total_seconds, absolute);
        this_time->getField("sec") = INT(s);
        this_time->getField("min") = INT(m);
        this_time->getField("hour") = INT(h);
        this_time->getField("day") = INT(d);
        this_time->getField("month") = INT(mon);
        this_time->getField("year") = INT(y);
        if (absolute) {
            auto days = evalDayOfYearAndDayOfWeek(d, mon, y);
            this_time->getField("day_of_year") = INT(days.first);
            this_time->getField("day_of_week") = INT(days.second);
        }
        else {
            this_time->getField("day_of_year") = INT(0);
            this_time->getField("day_of_week") = INT(0);
        }
        }, "value"));

    DateClass.addMethod("setMonth", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        if (!module.GET("value")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("value")->getType(), module);
        Int newVal = module.GET("value")->asInt(module);
        this_time->getField("month") = INT(newVal);
        int64_t total_seconds = getTotalSeconds(this_time, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [s, m, h, d, mon, y] = fromTotalSeconds(total_seconds, absolute);
        this_time->getField("sec") = INT(s);
        this_time->getField("min") = INT(m);
        this_time->getField("hour") = INT(h);
        this_time->getField("day") = INT(d);
        this_time->getField("month") = INT(mon);
        this_time->getField("year") = INT(y);
        if (absolute) {
            auto days = evalDayOfYearAndDayOfWeek(d, mon, y);
            this_time->getField("day_of_year") = INT(days.first);
            this_time->getField("day_of_week") = INT(days.second);
        }
        else {
            this_time->getField("day_of_year") = INT(0);
            this_time->getField("day_of_week") = INT(0);
        }
        }, "value"));

    DateClass.addMethod("setYear", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        if (!module.GET("value")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("value")->getType(), module);
        Int newVal = module.GET("value")->asInt(module);
        this_time->getField("year") = INT(newVal);
        int64_t total_seconds = getTotalSeconds(this_time, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [s, m, h, d, mon, y] = fromTotalSeconds(total_seconds, absolute);
        this_time->getField("sec") = INT(s);
        this_time->getField("min") = INT(m);
        this_time->getField("hour") = INT(h);
        this_time->getField("day") = INT(d);
        this_time->getField("month") = INT(mon);
        this_time->getField("year") = INT(y);
        if (absolute) {
            auto days = evalDayOfYearAndDayOfWeek(d, mon, y);
            this_time->getField("day_of_year") = INT(days.first);
            this_time->getField("day_of_week") = INT(days.second);
        }
        else {
            this_time->getField("day_of_year") = INT(0);
            this_time->getField("day_of_week") = INT(0);
        }
        }, "value"));

    DateClass.addMethod("setIsDst", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        Value this_time = module.GET("this");
        if (!module.GET("value")->instanceOf("bool"))
            throwTypeError(STRING_LITERAL("bool"), module.GET("value")->getType(), module);
        Int newVal = module.GET("value")->asBool(module);
        this_time->getField("isdst") = BOOL(newVal);
        }, "value"));

    // --- Methods later and ago ---
    // later(other): shifts time forward by a value specified by another Date object
    DateClass.addMethod("later", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        if (!module.GET("other")->instanceOf("Date"))
            throwTypeError(STRING_LITERAL("Date"), module.GET("other")->getType(), module);
        Value this_time = module.GET("this");
        Value other = module.GET("other");
        int64_t total_seconds = getTotalSeconds(this_time, module) + getTotalSeconds(other, module);
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds, absolute);
        RETURN_VALUE(module.CALL("Date", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), BOOL(0)));
        }, "other"));

    // later(amount, unit) : shifts time forward by a given number of time units
    DateClass.addMethod("later", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        if (!module.GET("amount")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("amount")->getType(), module);
        if (!module.GET("unit")->instanceOf("TimeUnit"))
            throwTypeError(STRING_LITERAL("TimeUnit"), module.GET("unit")->getType(), module);

        Value this_time = module.GET("this");
        Int amount = module.GET("amount")->asInt(module);
        Value unit = module.GET("unit");
        Int add_seconds = 0;
        if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Second"), module)->asBool(module)) {
            add_seconds = amount;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Minute"), module)->asBool(module)) {
            add_seconds = amount * 60;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Hour"), module)->asBool(module)) {
            add_seconds = amount * 3600;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Day"), module)->asBool(module)) {
            add_seconds = amount * 86400;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Month"), module)->asBool(module)) {
            add_seconds = amount * 30 * 86400;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Year"), module)->asBool(module)) {
            add_seconds = amount * 365 * 86400;
        }
        int64_t total_seconds = getTotalSeconds(this_time, module) + add_seconds;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds, absolute);
        RETURN_VALUE(module.CALL("Date", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), BOOL(0)));
        }, "amount", "unit"));

    // ago(other) : rewind time back to the value specified by another Date object
    DateClass.addMethod("ago", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        if (!module.GET("other")->instanceOf("Date"))
            throwTypeError(STRING_LITERAL("Date"), module.GET("other")->getType(), module);
        Value this_time = module.GET("this");
        Value other = module.GET("other");
        int64_t total_seconds = getTotalSeconds(this_time, module) - getTotalSeconds(other, module);
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds, absolute);
        RETURN_VALUE(module.CALL("Date", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), BOOL(0)));
        }, "other"));

    // ago(amount, unit) : rewind time back by the given amount of time units
    DateClass.addMethod("ago", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        if (!module.GET("amount")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("amount")->getType(), module);
        if (!module.GET("unit")->instanceOf("TimeUnit"))
            throwTypeError(STRING_LITERAL("TimeUnit"), module.GET("unit")->getType(), module);
        Value this_time = module.GET("this");
        Int amount = module.GET("amount")->asInt(module);
        Value unit = module.GET("unit");
        Int sub_seconds = 0;
        if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Second"), module)->asBool(module)) {
            sub_seconds = amount;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Minute"), module)->asBool(module)) {
            sub_seconds = amount * 60;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Hour"), module)->asBool(module)) {
            sub_seconds = amount * 3600;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Day"), module)->asBool(module)) {
            sub_seconds = amount * 86400;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Month"), module)->asBool(module)) {
            sub_seconds = amount * 30 * 86400;
        }
        else if (unit->equality(module.ENUM_ELEMENT("TimeUnit", "Year"), module)->asBool(module)) {
            sub_seconds = amount * 365 * 86400;
        }
        int64_t total_seconds = getTotalSeconds(this_time, module) - sub_seconds;
        if (total_seconds < 0) total_seconds = 0;
        bool absolute = (this_time->getField("day")->asInt(module) != 0 &&
            this_time->getField("month")->asInt(module) != 0 &&
            this_time->getField("year")->asInt(module) != 0);
        auto [sec, min, hour, day, month, year] = fromTotalSeconds(total_seconds, absolute);
        RETURN_VALUE(module.CALL("Date", INT(sec), INT(min), INT(hour), INT(day), INT(month), INT(year), BOOL(0)));
        }, "amount", "unit"));

    // Register class Date with name "Date"
    Time.CLASS("Date", DateClass);

    // Static methods: define DateStatic with a now method
    Static DateStatic;
    DateStatic.addMethod("now", METHOD(AccessModifierType::PUBLIC, [](Module& module) {
        std::tm end_time;
        lotus::nowTime(&end_time);
        RETURN_VALUE(module.CALL("Date",
            INT(end_time.tm_sec),
            INT(end_time.tm_min),
            INT(end_time.tm_hour),
            INT(end_time.tm_mday),
            INT(end_time.tm_mon),
            INT(end_time.tm_year),
            BOOL(end_time.tm_isdst)
        ));
        }));
    Time.STATIC("Date", DateStatic);

    // Functions: sleep
    Time.DEF("sleep", [](Module& module) {
        if (!module.GET("duration")->instanceOf("int"))
            throwTypeError(STRING_LITERAL("int"), module.GET("duration")->getType(), module);
        std::this_thread::sleep_for(std::chrono::milliseconds(module.GET("duration")->asInt(module)));
        }, "duration");

    modules.emplace(STRING_LITERAL("Time"), Time);
}