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
