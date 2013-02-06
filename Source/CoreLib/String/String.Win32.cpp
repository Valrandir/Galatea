#pragma once
#include <stdarg.h>
#include <tchar.h>
#include "../Types.hpp"
#include "../String/String.hpp"

using namespace Core;

void FormatImpl(TChar* buffer, UInt buffer_size, TChar const * format, va_list args)
{
	int r = _vsntprintf_s(buffer, buffer_size, _TRUNCATE, format, args);
	//if(r == -1) Assert / Log about buffer being too short and truncated
}

/*
String FormatImpl(TChar const * format, va_list args)
{
	int size = _vsctprintf(format, args);
	UInt capacity = (UInt)size;
	String str(capacity);

	void* p = (void*)str.GetTChar();
	TChar* c = (TChar*)p;

	FormatImpl(c, capacity, format, args);

	return str;
}
*/

String FormatImpl(TChar const * format, va_list args)
{
	int size = _vsctprintf(format, args) + 1;
	UInt capacity = (UInt)size;
	VoidPtr p = System::Memory::Alloc(capacity * sizeof(TChar));
	TChar* buffer = (TChar*)p;
	FormatImpl(buffer, capacity, format, args);

	String str(buffer);

	System::Memory::Free(p);

	return str;
}
