#include "parser/parser.h"
#include "parser/value/stringValue.h"
#include "parser/value/boolValue.h"
#include "utils/utils.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <array>

using namespace lotus;

void lotus::Parser::loadOsModule() {
	static Module Os;
	Os.DEF("platform", [&] {
#if defined(_WIN32)
		RETURN_VALUE(STRING("windows", module));
#elif defined(__APPLE__) && defined(__MACH__)
		RETURN_VALUE(STRING("macos", module));
#elif defined(__linux__)
		RETURN_VALUE(STRING("linux", module));
#elif defined(__unix__)
		RETURN_VALUE(STRING("unix", module));
#elif defined(__FreeBSD__)
		RETURN_VALUE(STRING("freebsd", module));
#elif defined(__OpenBSD__)
		RETURN_VALUE(STRING("openbsd", module));
#elif defined(__NetBSD__)
		RETURN_VALUE(STRING("netbsd", module));
#elif defined(__ANDROID__)
		RETURN_VALUE(STRING("android", module));
#elif defined(__CYGWIN__)
		RETURN_VALUE(STRING("cygwin", module));
#elif defined(_POSIX_VERSION)
		RETURN_VALUE(STRING("posix", module));
#elif defined(__HAIKU__)
		RETURN_VALUE(STRING("haiku", module));
#elif defined(__sun) && defined(__SVR4)
		RETURN_VALUE(STRING("solaris", module));
#elif defined(__QNX__)
		RETURN_VALUE(STRING("qnx", module));
#elif defined(__VXWORKS__)
		RETURN_VALUE(STRING("vxworks", module));
#elif defined(__riscos__)
		RETURN_VALUE(STRING("riscos", module));
#elif defined(__EMSCRIPTEN__)
		RETURN_VALUE(STRING("emscripten", module));
#else
		RETURN_VALUE(STRING("unknown", module));
#endif
		});

	Class FileClass;
	Static FileStatic;

	FileClass.addField("_path", FIELD(AccessModifierType::PRIVATE, STRING()));

	FileClass.addMethod("File", METHOD(AccessModifierType::PUBLIC, [&] {}));

	FileClass.addMethod("File", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("path")->instanceOf("string")) module.THROW(STRING("Incorrect type", module), STRING("type_error", module));
		Value& this_file = module.GET("this");

		this_file->getField("_path") = module.GET("path");
		}, "path"));

	FileClass.addMethod("path", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");

		RETURN_VALUE(this_file->getField("_path"));
		}));

	FileClass.addMethod("fullPath", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");

		RETURN_VALUE(STRING(std::filesystem::absolute(this_file->getField("_path")->asString(module)).wstring(), module));
		}));

	FileClass.addMethod("fullName", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");
		String path = this_file->getField("_path")->asString(module);

		std::filesystem::path file_path(path);

		RETURN_VALUE(STRING(file_path.filename().wstring(), module));
		}));

	FileClass.addMethod("name", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");
		String path = this_file->getField("_path")->asString(module);

		std::filesystem::path file_path(path);

		RETURN_VALUE(STRING(file_path.stem().wstring(), module));
		}));

	FileClass.addMethod("extension", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");
		String path = this_file->getField("_path")->asString(module);

		std::filesystem::path file_path(path);

		RETURN_VALUE(STRING(file_path.extension().wstring(), module));
		}));

	FileClass.addMethod("setPath", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("path")->instanceOf("string")) module.THROW(STRING("Incorrect type", module), STRING("type_error", module));
		Value& this_file = module.GET("this");

		this_file->getField("_path") = module.GET("path");
		}, "path"));

	FileClass.addMethod("remove", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");
		String path = this_file->getField("_path")->asString(module);

		if (!std::filesystem::exists(path)) {
			module.THROW(STRING(STRING_LITERAL("File does not exist: ") + path, module), STRING("file_error", module));
		}

		std::error_code ec;
		std::filesystem::remove(path, ec);
		if (ec) {
			module.THROW(STRING(STRING_LITERAL("Failed to delete file: ") + path, module), STRING("file_error", module));
		}
		}));

	FileClass.addMethod("write", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");
		String path = this_file->getField("_path")->asString(module);
		String content = module.GET("content")->asString(module);

		if (!std::filesystem::exists(path)) {
			module.THROW(STRING(STRING_LITERAL("File does not exist: ") + path, module), STRING("file_error", module));
		}

		std::wofstream file(path, std::ios::out | std::ios::trunc);
		if (!file) {
			module.THROW(STRING(STRING_LITERAL("Failed to write file: ") + path, module), STRING("file_error", module));
		}
		file << content;
		}, "content"));

	FileClass.addMethod("read", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");
		String path = this_file->getField("_path")->asString(module);

		if (!std::filesystem::exists(path)) {
			module.THROW(STRING(STRING_LITERAL("File does not exist: ") + path, module), STRING("file_error", module));
		}

		std::wifstream file(path);
		if (!file) {
			module.THROW(STRING(STRING_LITERAL("Failed to read file: ") + path, module), STRING("file_error", module));
		}

		std::wstringstream buffer;
		buffer << file.rdbuf();
		file.close();
		RETURN_VALUE(STRING(buffer.str(), module));
		}));

	FileClass.addMethod("append", METHOD(AccessModifierType::PUBLIC, [&] {
		Value& this_file = module.GET("this");
		String path = this_file->getField("_path")->asString(module);
		String content = module.GET("content")->asString(module);

		if (!std::filesystem::exists(path)) {
			module.THROW(STRING(STRING_LITERAL("File does not exist: ") + path, module), STRING("file_error", module));
		}

		std::wofstream file(path, std::ios::out | std::ios::app);
		if (!file) {
			module.THROW(STRING(STRING_LITERAL("Failed to append file: ") + path, module), STRING("file_error", module));
		}
		file << content;
		}, "content"));

	FileClass.addMethod("rename", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("new_path")->instanceOf("string")) module.THROW(STRING("Incorrect type", module), STRING("type_error", module));
		Value& this_file = module.GET("this");
		String old_path = this_file->getField("_path")->asString(module);
		String new_path = module.GET("new_path")->asString(module);

		if (!std::filesystem::exists(old_path)) {
			module.THROW(STRING(STRING_LITERAL("File does not exist: ") + old_path, module), STRING("file_error", module));
		}

		std::filesystem::path src(old_path);
		std::filesystem::path dst(new_path);

		std::error_code ec;
		std::filesystem::rename(src, dst, ec);
		if (ec) {
			module.THROW(STRING(STRING_LITERAL("Failed to rename file: ") + old_path + STRING_LITERAL(" to ") + new_path, module), STRING("file_error", module));
		}

		this_file->getField("_path") = STRING(new_path, module);
		}, "new_path"));

	FileStatic.addMethod("create", METHOD(AccessModifierType::PUBLIC, [&] {

		if (!module.GET("path")->instanceOf("string")) module.THROW(STRING("Incorrect type", module), STRING("type_error", module));

		String path = module.GET("path")->asString(module);

		std::filesystem::path file_path(path);

		std::ofstream file(file_path, std::ios::out | std::ios::trunc);
		if (!file) {
			module.THROW(STRING(STRING_LITERAL("Failed to create file: ") + path, module), STRING("file_error", module));
		}

		RETURN_VALUE(STRING(std::filesystem::absolute(path).wstring(), module));
		}, "path"));

	FileStatic.addMethod("exists", METHOD(AccessModifierType::PUBLIC, [&] {
		if (!module.GET("path")->instanceOf("string")) module.THROW(STRING("Incorrect type", module), STRING("type_error", module));
		RETURN_VALUE(BOOL(std::filesystem::exists(std::filesystem::path(module.GET("path")->asString(module)))));
		}, "path"));

	Os.DEF("execute", [&] {
		String command = module.GET("command")->asString(module);
		std::array<Char, 128> buffer;
		String result;

#ifdef _WIN32
		FILE* pipe = _wpopen(command.c_str(), L"r");
#else
		FILE* pipe = popen(wstring_to_string(command).c_str(), "r");
#endif

		if (!pipe) {
			module.THROW(STRING(STRING_LITERAL("Failed to run command: ") + command, module), STRING("execute_error", module));
		}
		while (fgetws(buffer.data(), (Int)buffer.size(), pipe) != nullptr) {
			result += buffer.data();
		}

#ifdef _WIN32
		_pclose(pipe);
#else
		pclose(pipe);
#endif

		RETURN_VALUE(STRING(result, module));
		}, "command");

	Os.CLASS("File", FileClass, module);
	Os.STATIC("File", FileStatic);

	modules.emplace(STRING_LITERAL("Os"), Os);
}