#pragma once
#include "../Types.hpp"
#include "../String/String.hpp"

namespace Galatea
{
	class Exception
	{
		void CopyToSelf(Exception const &);

		public:
		Exception(Exception const &);
		Exception& operator=(Exception const &);

		CStr source_code;
		CStr function;
		CStr file;
		UInt line;
		UInt32 err_code;
		String err_msg;

		Exception();
		Exception(CStr source_code, CStr function, CStr file, UInt32 line);
		Exception(CStr source_code, CStr function, CStr file, UInt32 line, CStr err_msg);
		void InitFromLastErr();
		void Clear();
	};
}
