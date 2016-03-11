#include <stdio.h> //Needed for "Use Multi-Byte Character Set" in Windows
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

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

int MultiByteToWideChar(const char* text, wchar_t* buffer, int byte_size)
{
	return MultiByteToWideChar(CP_UTF8, 0, text, -1, buffer, byte_size);
}

int WideCharToMultiByte(const wchar_t* text, char* buffer, int byte_size)
{
	return WideCharToMultiByte(CP_UTF8, 0, text, -1, buffer, byte_size, 0, nullptr);
}
