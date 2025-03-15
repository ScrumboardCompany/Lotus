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
    //// Open the file in binary mode to check the BOM
    //std::ifstream file(filePath, std::ios::binary);
    //if (!file) {
    //    throw LotusException(STRING_LITERAL("Unable to open file: ") + filePath);
    //}

    //// Read the first few bytes to check the BOM
    //std::vector<unsigned char> bom(4, 0);
    //file.read(reinterpret_cast<char*>(bom.data()), 4);
    //file.seekg(0);  // Let's return the pointer to the beginning of the file

    //std::wstring content;

    //if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) {
    //    // File in UTF-8 with BOM
    //    file.seekg(3);  // Skipping BOM
    //    std::stringstream buffer;
    //    buffer << file.rdbuf();
    //    std::string utf8Str = buffer.str();

    //    // Convert UTF-8 to wstring
    //    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    //    content = conv.from_bytes(utf8Str);
    //}
    //else if (bom[0] == 0xFF && bom[1] == 0xFE) {
    //    // File in UTF-16 LE
    //    file.seekg(2);
    //    std::wifstream wfile(filePath, std::ios::binary);
    //    wfile.imbue(std::locale(wfile.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, std::little_endian>));
    //    std::wstringstream wbuffer;
    //    wbuffer << wfile.rdbuf();
    //    content = wbuffer.str();
    //}
    //else if (bom[0] == 0xFE && bom[1] == 0xFF) {
    //    // File in UTF-16 BE
    //    file.seekg(2);
    //    std::wifstream wfile(filePath, std::ios::binary);
    //    wfile.imbue(std::locale(wfile.getloc(), new std::codecvt_utf16<wchar_t, 0x10FFFF, std::consume_header>));
    //    std::wstringstream wbuffer;
    //    wbuffer << wfile.rdbuf();
    //    content = wbuffer.str();
    //}
    //else {
    //    // File in ANSI/Windows-1251 or UTF-8 without BOM
    //    std::stringstream buffer;
    //    buffer << file.rdbuf();
    //    std::string rawStr = buffer.str();

    //    try {
    //        std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    //        content = conv.from_bytes(rawStr);
    //    }
    //    catch (...) {
    //        // If it didn't work, read as Windows-1251
    //        std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>, wchar_t> cp1251conv(
    //            new std::codecvt_byname<wchar_t, char, std::mbstate_t>("ru_RU.1251"));
    //        content = cp1251conv.from_bytes(rawStr);
    //    }
    //}

    //return content;

    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        throw LotusException(STRING_LITERAL("Unable to open file: ") + filePath);
    }

    // Read the first 4 bytes to determine the BOM
    unsigned char bom[4] = { 0, 0, 0, 0 };
    file.read(reinterpret_cast<char*>(bom), 4);

    // Checking the BOM
    if (bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF) {
        // UTF-8 with BOM
        file.seekg(3);
    }
    else if (bom[0] == 0xFF && bom[1] == 0xFE) {
        // UTF-16 LE
        file.seekg(2);
        std::wifstream wfile(filePath, std::ios::binary);
        wfile.imbue(std::locale("en_US.UTF-16"));
        std::wstringstream wbuffer;
        wbuffer << wfile.rdbuf();
        return wbuffer.str();
    }
    else if (bom[0] == 0xFE && bom[1] == 0xFF) {
        // UTF-16 BE
        file.seekg(2);
        std::wifstream wfile(filePath, std::ios::binary);
        wfile.imbue(std::locale("en_US.UTF-16"));
        std::wstringstream wbuffer;
        wbuffer << wfile.rdbuf();
        return wbuffer.str();
    }
    else {
        // UTF-8 without BOM
        file.seekg(0);
    }

    // Reading a file into a string
    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string utf8Str = buffer.str();

    // Convert UTF-8 -> wstring
    return string_to_wstring_codecvt(utf8Str);
}

std::pair<Int, Int> lotus::evalDayOfYearAndDayOfWeek(Int day, Int month, Int year) {
    std::vector<Int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    bool is_leap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    if (is_leap) days_in_months[1] = 29;

    Int day_of_year = day;
    for (int i = 0; i < static_cast<int>(month) - 1; i++) {
        day_of_year += days_in_months[i];
    }

    // Вычисляем день недели по формуле Зеллера
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

// Если объект представляет абсолютное время (дата задана), вычисляем секунды от 1 января 1970;
// иначе – считаем относительный интервал по единицам (месяц = 30 дней, год = 365 дней).
int64_t lotus::getTotalSeconds(Value time, Module& module) {
    Int sec = time->getField("sec")->asInt(module);
    Int min = time->getField("min")->asInt(module);
    Int hour = time->getField("hour")->asInt(module);
    Int day = time->getField("day")->asInt(module);
    Int month = time->getField("month")->asInt(module);
    Int year = time->getField("year")->asInt(module);

    // Абсолютный режим: все компоненты даты заданы (не равны 0)
    if (day != 0 && month != 0 && year != 0) {
        int64_t total_days = 0;
        for (Int y = 1970; y < year; y++) {
            total_days += ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)) ? 366 : 365;
        }
        std::vector<Int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        bool is_leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
        if (is_leap) days_in_months[1] = 29;
        for (int i = 0; i < static_cast<int>(month) - 1; i++) {
            total_days += days_in_months[i];
        }
        total_days += day - 1;
        return total_days * 86400ll + hour * 3600ll + min * 60ll + sec;
    }
    else {
        // Относительный режим: учитываем все компоненты как интервалы
        return sec + min * 60ll + hour * 3600ll + day * 86400ll + month * 30 * 86400ll + year * 365 * 86400ll;
    }
}

// Новая версия fromTotalSeconds с дополнительным параметром absolute:
// Если absolute==true, начинаем с 1970 года (дни начинаются с 1), иначе – с 0.
std::tuple<Int, Int, Int, Int, Int, Int> lotus::fromTotalSeconds(int64_t total_seconds, bool absolute) {
    Int year, month, day, hour, min, sec;
    if (absolute) {
        year = 1970;
        while (true) {
            Int days_in_year = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) ? 366 : 365;
            if (total_seconds >= days_in_year * 86400ll) {
                total_seconds -= days_in_year * 86400ll;
                year++;
            }
            else {
                break;
            }
        }
        std::vector<Int> days_in_months = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        bool is_leap = ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
        if (is_leap) days_in_months[1] = 29;
        month = 1;
        for (int i = 0; i < 12; i++) {
            if (total_seconds >= days_in_months[i] * 86400ll) {
                total_seconds -= days_in_months[i] * 86400ll;
                month++;
            }
            else {
                break;
            }
        }
        // Для абсолютных дат дни начинаются с 1
        day = static_cast<Int>(total_seconds / 86400ll + 1ll);
    }
    else {
        // Относительный режим: интервал переводим в года, месяцы, дни по упрощённой схеме
        year = total_seconds / (365 * 86400ll);
        total_seconds %= (365 * 86400ll);
        month = total_seconds / (30 * 86400ll);
        total_seconds %= (30 * 86400ll);
        day = total_seconds / 86400ll; // Здесь день считается от 0
    }
    total_seconds %= 86400ll;
    hour = static_cast<Int>(total_seconds / 3600ll);
    total_seconds %= 3600ll;
    min = static_cast<Int>(total_seconds / 60ll);
    sec = static_cast<Int>(total_seconds % 60ll);
    return { sec, min, hour, day, month, year };
}

std::wstring lotus::string_to_wstring_codecvt(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.from_bytes(str);
}

std::string lotus::wstring_to_string_codecvt(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    return conv.to_bytes(wstr);
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

    _Tm->tm_year += 1900;
    _Tm->tm_mon += 1;
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

double lotus::Cstod(const String& str) {
    std::wstringstream ss(str);
    ss.imbue(std::locale("C"));
    double value;
    ss >> value;
    return value;
}

std::vector<Ptr<Parser>> Compiler::parsers = {};

Module& lotus::Compiler::compile(const String& filePath, const StringMap<bool>& flags) {
    try {
        String content = wreadContent(filePath);

        Lexer lexer(content);
        auto tokens = lexer.tokenize();

        Ptr<Parser> parser = MAKE_PTR<Parser>(tokens, filePath);
        for (const auto& [name, value] : flags) {
            parser->getModule().flags.set(name, value);
        }

        auto statements = parser->parse();

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

bool lotus::isNumber(const Value& value) {
    return (value->instanceOf("int") || value->instanceOf("float"));
}