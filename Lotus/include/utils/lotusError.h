#pragma once

#ifndef _LOTUSERROR_
#define _LOTUSERROR_

#include "utils/lotusTypes.h"

namespace lotus {

	struct Module;

	class LotusException {

		String msg;
		size_t _line;

	public:
		LotusException() = default;
		LotusException(const LotusException&) = default;
		LotusException(LotusException&&) = default;

		explicit LotusException(const String& msg, size_t line = SIZE_MAX) : msg(msg), _line(line) {}

		const String& wwhat() const noexcept {
			return msg;
		}

		size_t line() const {
			return _line;
		}
	};

	[[noreturn]] void throwOverloadError(const String& overload, const String& type);

	[[noreturn]] void throwOverloadError(const String& overload, const String& type1, const String& type2);

	void throwTypeError(const String& type1, const String& type2, Module& module);

	void throwTypeError(const String& type1, const String& type2, const String& type3, Module& module);

	void checkThrowIndexError(const Value& index, size_t size, Module& module);
}

#endif // _LOTUSERROR_
