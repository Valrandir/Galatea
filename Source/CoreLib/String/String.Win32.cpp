#include <stdarg.h>
#include <tchar.h>
#include "../Types.hpp"
#include "../String/String.hpp"

using namespace Core;

void FormatImpl(TChar* buffer, UInt buffer_size, TChar const * format, va_list args)
{
	_vsntprintf_s(buffer, buffer_size, _TRUNCATE, format, args);
	//int r = _vsntprintf_s(buffer, buffer_size, _TRUNCATE, format, args);
	//if(r == -1) Assert / Log about buffer being too short and truncated
}

UInt FormatImplGetRequiredSize(TChar const * format, va_list args)
{
	int size = _vsctprintf(format, args) + 1;
	return (UInt)size;
}
