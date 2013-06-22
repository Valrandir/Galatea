#include "CoreException.hpp"
#include "../System.hpp"

namespace Core
{
	void CoreException::CopyToSelf(CoreException const & ex)
	{
		source_code = ex.source_code;
		function = ex.function;
		file = ex.file;
		line = ex.line;
		err_code = ex.err_code;
		err_msg = ex.err_msg;
	}

	CoreException::CoreException(CoreException const & ex)
	{
		CopyToSelf(ex);
	}

	CoreException& CoreException::operator=(CoreException const & ex)
	{
		if(&ex != this)
			CopyToSelf(ex);
		return *this;
	}

	CoreException::CoreException() :
		source_code(String::Empty),
		function(String::Empty),
		file(String::Empty),
		line(0U),
		err_code(0U)
	{}

	CoreException::CoreException(CStr source_code, CStr function, CStr file, UInt32 line) :
		source_code(source_code),
		function(function),
		file(file),
		line(line),
		err_code(0U)
	{}

	CoreException::CoreException(CStr source_code, CStr function, CStr file, UInt32 line, CStr err_msg) :
		source_code(source_code),
		function(function),
		file(file),
		line(line),
		err_code(0U),
		err_msg(err_msg)
	{}

	void CoreException::InitErr()
	{
		err_code = GetErrCode();
		err_msg = GetErrText(err_code);
	}

	void CoreException::Clear()
	{
		source_code = String::Empty;
		function = String::Empty;
		file = String::Empty;
		line = 0U;
		err_code = 0U;
		err_msg = String::Empty;
	}
}
