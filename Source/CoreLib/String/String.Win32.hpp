#pragma once
#include <stdarg.h>
#include "../Types.hpp"
//#include "../String/String.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::TChar const * format, va_list args);
Core::String FormatImpl(Core::TChar const * format, va_list args);
