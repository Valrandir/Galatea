#pragma once
#include "../Types.hpp"
#include "../String/String.hpp"

namespace Core
{
	class CoreException
	{
		void CopyToSelf(CoreException const &);

		public:
		CoreException(CoreException const &);
		CoreException& operator=(CoreException const &);

		CStr source_code;
		CStr function;
		CStr file;
		UInt line;
		UInt32 err_code;
		String err_msg;

		CoreException();
		CoreException(CStr source_code, CStr function, CStr file, UInt32 line);
		CoreException(CStr source_code, CStr function, CStr file, UInt32 line, CStr err_msg);
		void InitErr();
		void Clear();
	};
}
