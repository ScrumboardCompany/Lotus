#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/value/value.h"
#include "utils/lotusError.h"
#include "parser/expression/expresion.h"
#include "parser/statement/statement.h"

int main() {
    try {
        std::wifstream file(L"test.lts"); 
        file.imbue(std::locale(""));     

        if (!file) {
            std::wcerr << L"Unable to open file" << std::endl;
            return 1;
        }

        std::wstringstream buffer;
        buffer << file.rdbuf();

        std::wstring content = buffer.str();

        lotus::Lexer lexer(content);
        auto tokens = lexer.tokenize();

        /*for (auto& token : tokens) {
            std::wcout << token.type_to_string().c_str() << "[" << token.text << "] ";
        }*/
        lotus::Parser parser(tokens);

        auto parseds = parser.parse();

        for (auto& parsed : parseds) {
            parsed->execute();
        }
    }
    catch (const lotus::LotusException& e) {
        std::wcout << e.wwhat();
    }
    catch (const std::exception& e) {
        std::cout << e.what();
    }

    return 0;
}