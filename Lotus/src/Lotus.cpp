#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/value/value.h"
#include "utils/lotusError.h"
#include "parser/expression/expresion.h"

void testExpression(const lotus::String expr, double expected) {
    lotus::Lexer lexer(expr);
    auto tokens = lexer.tokenize();
    lotus::Parser parser(tokens);

    try {
        auto result = parser.parse();
        double value = result->eval()->asDouble();

        std::wcout << "Expression: " << expr.c_str() << "\n";
        std::wcout << "Result: " << value << "\n";
        std::wcout << "Expected: " << expected << "\n";
        std::wcout << (value == expected ? "Passed" : "Failed") << "\n\n";
    }
    catch (const lotus::LotusException& ex) {
        std::cout << "Error: " << ex.what() << "\n";
    }
}

int main() {
    testExpression(STRING_LITERAL("7 + (3 * 2) - (8 / 4)"), 12);

    return 0;
}