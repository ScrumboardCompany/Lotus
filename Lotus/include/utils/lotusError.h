#pragma once

#ifndef _LOTUS_ERROR_
#define _LOTUS_ERROR_

#include "utils/lotusTypes.h"

namespace lotus {

	class LotusException {

		String msg;
	public:
		LotusException() = default;
		LotusException(const LotusException&) = default;
		LotusException(LotusException&&) = default;

		explicit LotusException(const String& msg) : msg(msg) {}

		const String& wwhat() const noexcept {
			return msg;
		}
	};

	void throwOverloadError(const String& overload, const String& type);

	void throwOverloadError(const String& overload, const String& type1, const String& type2);

	void checkThrowIndexError(const Value& index, size_t size);
}

#endif // _LOTUS_ERROR_
