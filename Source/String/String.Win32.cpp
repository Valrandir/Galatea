#include <stdarg.h>
#include <tchar.h>
#include "../Assert/Assert.hpp"
#include "../Types.hpp"
#include "../String/String.hpp"

using namespace Galatea;

void FormatImpl(TChar* buffer, UInt buffer_size, CStr format, va_list args)
{
	_vsntprintf_s(buffer, buffer_size, _TRUNCATE, format, args);
}

UInt FormatImplGetRequiredSize(CStr format, va_list args)
{
	int size = _vsctprintf(format, args) + 1;
	return (UInt)size;
}
