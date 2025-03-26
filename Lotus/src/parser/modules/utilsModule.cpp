#include "parser/parser.h"
#include "parser/value/objectValue.h"
#include "parser/value/stringValue.h"
#include "utils/utils.h"
#include "../external/json.hpp"
#include <filesystem>
#include <fstream>

using namespace lotus;
using namespace nlohmann;

void lotus::Parser::loadUtilityModule() {
	static Module utilityModule;

    utilityModule.DEF("json", [&] {
        String path = module.GET("path")->asString(module);

        if (!std::filesystem::exists(path)) {
            module.THROW(STRING(STRING_LITERAL("File does not exist: ") + path), STRING("file_error"));
        }

        std::wifstream file(path);
        if (!file) {
            module.THROW(STRING(STRING_LITERAL("Failed to read file: ") + path), STRING("file_error"));
        }

        std::wstringstream buffer;
        buffer << file.rdbuf();
        file.close();

        json parsed_json = json::parse(buffer.str(), nullptr, false);

        if (parsed_json.is_discarded()) {
            module.THROW(STRING("Invalid JSON format"), STRING("json_error"));
        }

        StringMap<Value> obj;
        for (auto& [key, value] : parsed_json.items()) {
            obj.emplace(string_to_wstring_codecvt(key.c_str()), STRING(string_to_wstring_codecvt(value.dump().c_str())));
        }

        RETURN_VALUE(OBJECT(obj));
        }, "path");

    modules.emplace(STRING_LITERAL("Utility"), utilityModule);
}