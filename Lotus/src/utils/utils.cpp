#include "utils/utils.h"
#include "parser/expression/expression.h"
#include "parser/value/value.h"
#include "parser/value/undefinedValue.h"
#include "utils/lotusError.h"
#include "parser/parser.h"
#include "lexer/lexer.h"
#include <fstream>
#include <sstream>
#include <chrono>
#include <iostream>
#include <locale>
#include <codecvt>
#include "parser/expression/letExpression.h"
#include "parser/expression/floatExpression.h"
#include "parser/expression/stringExpression.h"
#include "parser/statement/expressionStatement.h"
#include <filesystem>
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"

#pragma warning( disable : 4996 )

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
    // Open the file in binary mode to check the BOM
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw LotusException(STRING_LITERAL("Unable to open file: ") + filePath);
    }

    // Read the first few bytes to check the BOM
    std::vector<unsigned char> bom(4, 0);
    file.read(reinterpret_cast<char*>(bom.data()), 4);
    file.seekg(0);  // Let's return the pointer to the beginning of the file

    std::wstring content;

    if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) {
        // File in UTF-8 with BOM
        file.seekg(3);  // Skipping BOM
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string utf8Str = buffer.str();

        // Convert UTF-8 to wstring
        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
        content = conv.from_bytes(utf8Str);
    }
    else if (bom[0] == 0xFF && bom[1] == 0xFE) {
        // File in UTF-16 LE
        file.seekg(2);
        std::wifstream wfile(filePath, std::ios::binary);
        wfile.imbue(std::locale(wfile.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, std::little_endian>));
        std::wstringstream wbuffer;
        wbuffer << wfile.rdbuf();
        content = wbuffer.str();
    }
    else if (bom[0] == 0xFE && bom[1] == 0xFF) {
        // File in UTF-16 BE
        file.seekg(2);
        std::wifstream wfile(filePath, std::ios::binary);
        wfile.imbue(std::locale(wfile.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, std::consume_header>));
        std::wstringstream wbuffer;
        wbuffer << wfile.rdbuf();
        content = wbuffer.str();
    }
    else {
        // File in ANSI/Windows-1251 or UTF-8 without BOM
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string rawStr = buffer.str();

        try {
            std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
            content = conv.from_bytes(rawStr);
        }
        catch (...) {
            // If it didn't work, read as Windows-1251
            std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>, wchar_t> cp1251conv(
                new std::codecvt_byname<wchar_t, char, std::mbstate_t>("ru_RU.1251"));
            content = cp1251conv.from_bytes(rawStr);
        }
    }

    return content;
}

std::pair<int, int> lotus::evalDayOfYearAndDayOfWeek(int day, int month, int year) {
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

void lotus::nowTime(tm* _Tm) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

#ifdef _WIN32
    localtime_s(_Tm, &now_time);
#else
    localtime_r(&now_time, _Tm);
#endif
}

String lotus::nowTimeInString() {
    tm time;
    nowTime(&time);

    String result;

    result += std::to_wstring(time.tm_mday);
    result += STRING_LITERAL("/");
    result += std::to_wstring(time.tm_mon);
    result += STRING_LITERAL("/");
    result += std::to_wstring(time.tm_year);
    result += STRING_LITERAL(" ");

    result += std::to_wstring(time.tm_hour);
    result += STRING_LITERAL(":");
    result += std::to_wstring(time.tm_min);
    result += STRING_LITERAL(":");
    result += std::to_wstring(time.tm_sec);

    return result;
}

std::vector<Ptr<Parser>> Compiler::parsers = {};

Module& lotus::Compiler::compile(const String& filePath, const StringMap<bool>& flags) {
    try {
        String content = wreadContent(filePath);

        Lexer lexer(content);
        auto tokens = lexer.tokenize();

        Ptr<Parser> parser = MAKE_PTR<Parser>(tokens);
        for (const auto& [name, value] : flags) {
            parser->getModule().flags.set(name, value);
        }

        auto statements = parser->parse();

        statements.insert(statements.begin(), MAKE_PTR<ExpressionStatement>(
            MAKE_PTR<LetExpression>(STRING_LITERAL("__file__"),
                MAKE_PTR<StringExpression>(std::filesystem::path(filePath).filename().wstring())
            )));

        statements.insert(statements.begin(), MAKE_PTR<ExpressionStatement>(
            MAKE_PTR<LetExpression>(STRING_LITERAL("__path__"),
                MAKE_PTR<StringExpression>(std::filesystem::absolute(filePath).wstring())
            )));

        statements.insert(statements.begin(), MAKE_PTR<ExpressionStatement>(
            MAKE_PTR<LetExpression>(STRING_LITERAL("__time__"),
                MAKE_PTR<StringExpression>(nowTimeInString())
            )));

        statements.insert(statements.begin(), MAKE_PTR<ExpressionStatement>(
            MAKE_PTR<LetExpression>(STRING_LITERAL("__version__"),
                MAKE_PTR<FloatExpression>(LOTUS_VERSION)
            )));

        Module& module = parser->getModule();
        for (auto& statement : statements) {
            if (statement) {
                statement->execute(module);
            }
        }

        parsers.push_back(parser);

        return module;
    }
    catch (const LotusException& e) {
        std::wcout << std::endl;
        
        std::wcout << e.wwhat();
        if (e.line() != SIZE_MAX) {
            std::cout << " on line: " << e.line() << std::endl;
        }
        else {
            std::cout << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cout << std::endl << e.what() << std::endl;
    }
    catch (const ContinueStatement&) {
        std::cout << std::endl << "No continue processing found" << std::endl;
    }
    catch (const BreakStatement&) {
        std::cout << std::endl << "No break processing found" << std::endl;
    }
    catch (const Value&) {
        std::cout << std::endl << "No return processing found" << std::endl;
    }
    catch (const ThrowValue&) {
        std::cout << std::endl << "No exception processing found" << std::endl;
    }
    catch (...) {
        std::cout << std::endl << "Unhandled exception" << std::endl;
    }
    throw -1;
}