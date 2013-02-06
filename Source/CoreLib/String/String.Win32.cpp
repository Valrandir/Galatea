#pragma once
#include <stdarg.h>
#include <tchar.h>
#include "../Types.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::TChar const * format, va_list argptr)
{
	_vsntprintf_s(buffer, buffer_size, _TRUNCATE, format, argptr);
}
