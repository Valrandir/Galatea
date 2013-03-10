#pragma once
#include "../../Types.hpp"

#ifdef CoreDebug
	#define Assert(fn) if(!(fn)) Core::Assert::Fail(Text(#fn), Text(__FUNCTION__), Text(__FILE__), __LINE__)
#else
	#define Assert
#endif

namespace Core
{
	namespace Assert
	{
		void Fail(CStr failed_text, CStr function, CStr file, UInt line);
	}
}
