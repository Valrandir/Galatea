#pragma once
#include <stdarg.h>
#include "Types.hpp"

void FormatImpl(Core::TChar* buffer, Core::UInt buffer_size, Core::TChar const * format, va_list argptr);
