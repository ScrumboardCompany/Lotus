#pragma once

#ifndef _VALUE_
#define _VALUE_

#include "utils/lotusTypes.h"
#include "utils/lotusDefines.h"

namespace lotus {

	class IValue {
	public:

		virtual int asInt() = 0;
		virtual double asDouble() = 0;

		virtual String getType() const = 0;

		virtual Value add(const Value& other) = 0;
		virtual Value substract(const Value& other) = 0;
		virtual Value multiply(const Value& other) = 0;
		virtual Value divide(const Value& other) = 0;

		virtual Value unary_plus() = 0;
		virtual Value unary_minus() = 0;

		virtual ~IValue() = default;
	};
}

#endif // _VALUE_