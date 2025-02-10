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
}

#endif // _LOTUS_ERROR_
