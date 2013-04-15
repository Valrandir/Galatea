#pragma once
#include "../Types.hpp"

namespace Core
{
	struct CoreException
	{
		CStr failed_text;
		CStr function;
		CStr file;
		UInt line;

		CoreException(CStr failed_text, CStr function, CStr file, UInt line);
	};
}
