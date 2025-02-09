#pragma once

#ifndef _LOTUS_ERROR_
#define _LOTUS_ERROR_

#include <stdexcept>
#include <string>

namespace lotus {

	class LotusException : public std::runtime_error {
	public:
		LotusException() = default;
		LotusException(const LotusException&) = default;
		LotusException(LotusException&&) = default;

		LotusException(const std::string& msg) : runtime_error(msg) {}
	};
}

#endif // _LOTUS_ERROR_
