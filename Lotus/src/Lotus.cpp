#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "parser/value/value.h"
#include "utils/lotusError.h"
#include "parser/expression/expresion.h"
#include "parser/statement/statement.h"
#include "parser/statement/continueStatement.h"
#include "parser/statement/breakStatement.h"
#include "utils/utils.h"

int main(int argc, char* argv[]) {
    try {
        lotus::String content;
        if (argc < 2) {
            //std::cerr << "Must specify a file to compile" << std::endl;
            //return 1;
            content = lotus::wreadContent(L"test.lts");
        }
        else {
            content = lotus::wreadContent(STRING_VAR_LITERAL(argv[1]));
        }

        lotus::Lexer lexer(content);
        auto tokens = lexer.tokenize();

        lotus::Parser parser(tokens);

        auto statements = parser.parse();

        for (auto& statement : statements) {
            if (statement) {
                statement->execute(parser.getModule());
            }
        }
    }
    catch (const lotus::LotusException& e) {
        std::wcout << std::endl << e.wwhat() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << std::endl << e.what() << std::endl;
    }
    catch (const lotus::ContinueStatement&) {
        std::cout << std::endl << "No continue processing found" << std::endl;
    }
    catch (const lotus::BreakStatement&) {
        std::cout << std::endl << "No break processing found" << std::endl;
    }
    catch (const lotus::Value&) {
        std::cout << std::endl << "No return processing found" << std::endl;
    }
    catch (const lotus::ThrowValue&) {
        std::cout << std::endl << "No exception processing found" << std::endl;
    }
    catch (...) {
        std::cout << std::endl << "Unhandled exception" << std::endl;
    }

    return 0;
}