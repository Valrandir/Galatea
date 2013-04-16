#pragma once
#include "../Types.hpp"

namespace Core
{
	struct CoreException
	{
		CStr source_code;
		CStr function;
		CStr file;
		UInt line;
		UInt32 err_code;
		CStr err_msg;

		CoreException(CStr source_code, CStr function, CStr file, UInt32 line);
		CoreException(CStr source_code, CStr function, CStr file, UInt32 line, CStr err_msg);
		CoreException(CStr source_code, CStr function, CStr file, UInt32 line, UInt32 err_code, CStr err_msg);
	};
}
