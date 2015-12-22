#include "Exception.hpp"
#include "../System.hpp"

namespace Galatea
{
	void Exception::CopyToSelf(Exception const & ex)
	{
		source_code = ex.source_code;
		function = ex.function;
		file = ex.file;
		line = ex.line;
		err_code = ex.err_code;
		err_msg = ex.err_msg;
	}

	Exception::Exception(Exception const & ex)
	{
		CopyToSelf(ex);
	}

	Exception& Exception::operator=(Exception const & ex)
	{
		if(&ex != this)
			CopyToSelf(ex);
		return *this;
	}

	Exception::Exception() :
		source_code(String::Empty),
		function(String::Empty),
		file(String::Empty),
		line(0U),
		err_code(0U)
	{}

	Exception::Exception(CStr source_code, CStr function, CStr file, UInt32 line) :
		source_code(source_code),
		function(function),
		file(file),
		line(line),
		err_code(0U)
	{}

	Exception::Exception(CStr source_code, CStr function, CStr file, UInt32 line, CStr err_msg) :
		source_code(source_code),
		function(function),
		file(file),
		line(line),
		err_code(0U),
		err_msg(err_msg)
	{}

	void Exception::InitFromLastErr()
	{
		err_code = GetErrCode();
		err_msg = GetErrText(err_code);
	}

	void Exception::Clear()
	{
		source_code = String::Empty;
		function = String::Empty;
		file = String::Empty;
		line = 0U;
		err_code = 0U;
		err_msg = String::Empty;
	}
}
