#include "CoreException.hpp"

namespace Core
{
	CoreException::CoreException(CStr source_code, CStr function, CStr file, UInt32 line) :
		source_code(source_code),
		function(function),
		file(file),
		line(line),
		err_code(0U),
		err_msg(Text(""))
	{}

	CoreException::CoreException(CStr source_code, CStr function, CStr file, UInt32 line, CStr err_msg) :
		source_code(source_code),
		function(function),
		file(file),
		line(line),
		err_code(0U),
		err_msg(err_msg)
	{}

	CoreException::CoreException(CStr source_code, CStr function, CStr file, UInt32 line, UInt32 err_code, CStr err_msg) :
		source_code(source_code),
		function(function),
		file(file),
		line(line),
		err_code(err_code),
		err_msg(err_msg)
	{}
}
