#include "utils/utils.h"
#include "parser/expression/expression.h"
#include "parser/value/value.h"
#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include <fstream>
#include <sstream>

using namespace lotus;

Value lotus::callAllExpressionsAndReturnLastValue(const std::vector<Expression>& expressions, Module& module) {
    if (expressions.empty()) return UNDEFINED();
    Value lastExpression;
    for (auto& expr : expressions) {
        lastExpression = expr->eval(module);
    }
    return lastExpression;
}

std::wstring lotus::wreadContent(const std::wstring& filePath) {
    std::wifstream file(filePath);
    file.imbue(std::locale(""));

    if (!file) {
        throw LotusException(STRING_LITERAL("Error: unable to open file: ") + filePath);
    }

    std::wstringstream buffer;
    buffer << file.rdbuf();

    std::wstring content = buffer.str();

    return content;
}

std::pair<Int, Int> lotus::evalDayOfYearAndDayOfWeek(Int day, Int month, Int year) {
    std::vector<Int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    Int day_of_year = day;
    for (int i = 0; i < static_cast<int>(month) - 1; i++) {
        day_of_year += days_in_months[i];
    }

    Int y = (month < 3) ? year - 1 : year;
    Int m = (month < 3) ? month + 12 : month;
    Int K = y % 100;
    Int J = y / 100;

    Int day_of_week = (day + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + (5 * J)) % 7;
    day_of_week = (day_of_week + 6) % 7;

    return std::make_pair(day_of_year, day_of_week);
}

bool lotus::isValidDate(Int day, Int month, Int year) {
    if (month < 1 || month > 12 || day < 1) return false;

    std::vector<Int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    return day <= days_in_months[static_cast<int>(month) - 1];
}

int64_t lotus::getTotalSeconds(Value time, Module& module) {
    Int sec = time->getField("sec")->asInt(module);
    Int min = time->getField("min")->asInt(module);
    Int hour = time->getField("hour")->asInt(module);
    Int day = time->getField("day")->asInt(module);
    Int month = time->getField("month")->asInt(module);
    Int year = time->getField("year")->asInt(module);

    std::vector<Int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    Int total_days = (year - 1970) * 365 + (year - 1969) / 4 - (year - 1901) / 100 + (year - 1601) / 400;
    for (int i = 0; i < static_cast<int>(month) - 1; i++) {
        total_days += days_in_months[i];
    }
    total_days += day - 1;

    return total_days * 86400ll + hour * 3600ll + min * 60ll + sec;
}

std::tuple<Int, Int, Int, Int, Int, Int> lotus::fromTotalSeconds(int64_t total_seconds) {
    Int year = 0;
    while (true) {
        Int days_in_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 366 : 365;
        if (total_seconds >= days_in_year * 86400) {
            total_seconds -= days_in_year * 86400;
            year++;
        }
        else {
            break;
        }
    }

    std::vector<Int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    Int month = 1;
    for (int i = 0; i < 12; i++) {
        if (total_seconds >= days_in_months[i] * 86400) {
            total_seconds -= days_in_months[i] * 86400;
            month++;
        }
        else {
            break;
        }
    }

    Int day = static_cast<Int>(total_seconds / 86400ll + 1ll);
    total_seconds %= 86400ll;
    Int hour = static_cast<Int>(total_seconds / 3600ll);
    total_seconds %= 3600ll;
    Int min = static_cast<Int>(total_seconds / 60ll);
    Int sec = static_cast<Int>(total_seconds % 60ll);

    return { sec, min, hour, day, month, year };
}

std::string lotus::wstring_to_string(const std::wstring& wstr) {
    std::string str;
    str.reserve(wstr.size());
    for (wchar_t wc : wstr) {
        if (wc <= 0x7F) {
            str.push_back(static_cast<char>(wc));
        }
        else {
            str.push_back('?');
        }
    }
    return str;
}

bool lotus::isNumber(const Value& value) {
    return (value->instanceOf("int") || value->instanceOf("float"));
}