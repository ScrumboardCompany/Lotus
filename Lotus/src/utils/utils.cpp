#include "utils/utils.h"
#include "parser/expression/expresion.h"
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
        throw LotusException(STRING_LITERAL("Unable to open file: ") + filePath);
    }

    std::wstringstream buffer;
    buffer << file.rdbuf();

    std::wstring content = buffer.str();

    return content;
}

std::pair<int, int> lotus::evalDayOfYearAndDayOfWeek(int sec, int min, int hour, int day, int month, int year) {
    std::vector<int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    int day_of_year = day;
    for (int i = 0; i < month - 1; i++) {
        day_of_year += days_in_months[i];
    }

    int y = (month < 3) ? year - 1 : year;
    int m = (month < 3) ? month + 12 : month;
    int K = y % 100;
    int J = y / 100;

    int day_of_week = (day + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + (5 * J)) % 7;
    day_of_week = (day_of_week + 6) % 7;

    return std::make_pair(day_of_year, day_of_week);
}

errno_t lotus::localtime(tm* _Tm, const time_t* _Time) {
#ifdef _WIN32
    return localtime_s(_Tm, _Time);
#else
    return localtime_r(_Time, _Tm);
#endif
}

bool lotus::isValidDate(int day, int month, int year) {
    if (month < 1 || month > 12 || day < 1) return false;

    std::vector<int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    return day <= days_in_months[month - 1];
}

int64_t lotus::getTotalSeconds(Value time, Module& module) {
    int sec = time->getField("sec")->asInt(module);
    int min = time->getField("min")->asInt(module);
    int hour = time->getField("hour")->asInt(module);
    int day = time->getField("day")->asInt(module);
    int month = time->getField("month")->asInt(module);
    int year = time->getField("year")->asInt(module);

    std::vector<int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    int total_days = (year - 1970) * 365 + (year - 1969) / 4 - (year - 1901) / 100 + (year - 1601) / 400;
    for (int i = 0; i < month - 1; i++) {
        total_days += days_in_months[i];
    }
    total_days += day - 1;

    return total_days * 86400ll + hour * 3600ll + min * 60ll + sec;
}

std::tuple<int, int, int, int, int, int> lotus::fromTotalSeconds(int64_t total_seconds) {
    int year = 0;
    while (true) {
        int days_in_year = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0) ? 366 : 365;
        if (total_seconds >= days_in_year * 86400) {
            total_seconds -= days_in_year * 86400;
            year++;
        }
        else {
            break;
        }
    }

    std::vector<int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    int month = 1;
    for (int i = 0; i < 12; i++) {
        if (total_seconds >= days_in_months[i] * 86400) {
            total_seconds -= days_in_months[i] * 86400;
            month++;
        }
        else {
            break;
        }
    }

    int day = static_cast<int>(total_seconds / 86400ll + 1ll);
    total_seconds %= 86400ll;
    int hour = static_cast<int>(total_seconds / 3600ll);
    total_seconds %= 3600ll;
    int min = static_cast<int>(total_seconds / 60ll);
    int sec = static_cast<int>(total_seconds % 60ll);

    return { sec, min, hour, day, month, year };
}
