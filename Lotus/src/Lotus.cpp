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

int main() {
    try {
        lotus::String content = lotus::wreadContent(L"test.lts");

        lotus::Lexer lexer(content);
        auto tokens = lexer.tokenize();

        /*for (auto& token : tokens) {
            std::wcout << token.type_to_string().c_str() << "[" << token.text << "] ";
        }*/
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