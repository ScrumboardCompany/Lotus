#include <iostream>
#include "Lotus.h"
#include <filesystem>

using namespace lotus;

int handleArgsAndCompile(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);

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
            try {
                Compiler::compile(STRING_VAR_LITERAL(args[i].c_str()), flags);
            }
            catch (...) {
                return 1;
            }
            break;
        }
    }

    return 0;
}

int main(int argc, char* argv[]) {
    setConsoleLocale();

    //return handleArgsAndCompile(argc, argv);

    try {
        Compiler::compile(L"test.lts", {});
    }
    catch (...) {
        return 1;
    }

    return 0;
}