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
        throw LotusException(STRING_LITERAL("Unable to open file"));
    }

    std::wstringstream buffer;
    buffer << file.rdbuf();

    std::wstring content = buffer.str();

    return content;
}