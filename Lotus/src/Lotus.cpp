#include <iostream>
#include "Lotus.h"

using namespace lotus;

void compile(const String& filePath, const StringMap<bool>& flags) {
    try {
        String content = wreadContent(filePath);

        Lexer lexer(content);
        auto tokens = lexer.tokenize();

        Parser parser(tokens);
        for (const auto& [name, value] : flags) {
            parser.getModule().flags.set(name, value);
        }

        auto statements = parser.parse();

        Module& module = parser.getModule();
        for (auto& statement : statements) {
            if (statement) {
                statement->execute(module);
            }
        }
    }
    catch (const LotusException& e) {
        std::wcout << std::endl << e.wwhat() << std::endl;
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
}

int main(int argc, char* argv[]) {

    /*std::vector<std::string> args(argv + 1, argv + argc);

    StringMap<bool> flags;
    Map<std::string, bool> boolValues = { {"true", true}, {"false", false} };

    for (size_t i = 0; i < args.size(); i++) {
        if (args[i] == "--help" || args[i] == "-h") {
            std::cout << 
                "--help, -h - outputs all CLI flags\n"
                "--version, -v - outputs lotus version\n"
                "--flag [name] [value] - set flag value before interpretation\n";
                "--flag-config [cfgFilePath] - specify flags config";
            break;
        }
        else if (args[i] == "--version" || args[i] == "-v") {
            std::cout << LOTUS_VERSION;
            break;
        }
        else if (args[i] == "--flag") {
            if (i + 2 >= args.size()) {
                std::cerr << "Error: expected flag name and value\n";
                return 1;
            }

            String flagName = STRING_VAR_LITERAL(args[++i].c_str());
            std::string stringValue = args[++i];

            auto it = boolValues.find(stringValue);
            if (it == boolValues.end()) {
                std::cerr << "Error: expected 'true' or 'false' for flag value, got '" << stringValue << "'\n";
                return 1;
            }

            flags.emplace(flagName, it->second);
        }
        else if (args[i] == "--flag-config") {
            if (i + 1 >= args.size()) {
                std::cerr << "Error: expected flag config path\n";
                return 1;
            }

            FlagConfigParser flagConfigParser(Lexer(wreadContent(STRING_VAR_LITERAL(args[++i].c_str()))).tokenize());
            flagConfigParser.parse();

            flags = flagConfigParser.getFlags();
        }
        else {
            compile(STRING_VAR_LITERAL(args[i].c_str()), flags);
            break;
        }
    }*/

    compile(L"test.lts", {});

    return 0;
}