#pragma once
#include "../../Types.hpp"

#ifdef _DEBUG
	#define Assert(fn) if(!fn) Core::Assert::Fail(Text(#fn), Text(__FUNCTION__), Text(__FILE__), __LINE__);
#else
	#define Assert
#endif

namespace Core
{
	namespace Assert
	{
		void Fail(TChar const * failed_text, TChar const * function, TChar const * file, UInt line);
	}
}
