#pragma once
#include "../Types.hpp"

namespace Core
{
	class String;

	class CoreException
	{
		String *_holder;
		void CopyToSelf(CoreException const &);

		public:
		CoreException(CoreException const &);
		CoreException& operator=(CoreException const &);
		~CoreException();

		CStr source_code;
		CStr function;
		CStr file;
		UInt line;
		UInt32 err_code;
		CStr err_msg;

		CoreException();
		CoreException(CStr source_code, CStr function, CStr file, UInt32 line);
		CoreException(CStr source_code, CStr function, CStr file, UInt32 line, CStr err_msg);
		void InitErr();
	};
}
