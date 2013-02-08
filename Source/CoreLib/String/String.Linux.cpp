#include <stdio.h>
#include "../Types.hpp"
#include "../String/String.hpp"

using namespace Core;

void FormatImpl(TChar* buffer, UInt buffer_size, TChar const * format, va_list args)
{
	vsnprintf(buffer, buffer_size, format, args);
	//int r = vsnprintf(buffer, buffer_size, format, args);
	//if(r == -1) Assert / Log about buffer being too short and truncated
}

UInt FormatImplGetRequiredSize(TChar const * format, va_list args)
{
	int size = vsnprintf(0, 0, format, args) + 1;
	return (UInt)size;
}
