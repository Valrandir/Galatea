#include "CoreException.hpp"
#include "../System.hpp"

namespace Core
{
	void CoreException::CopyToSelf(CoreException const & ex)
	{
		DeletePtr(_holder);

		source_code = ex.source_code;
		function = ex.function;
		file = ex.file;
		line = ex.line;
		err_code = ex.err_code;

		if(ex._holder)
		{
			_holder = new String(*ex._holder);
			err_msg = _holder->CStrPtr();
		}
		else
			err_msg = String::Empty;
	}

	CoreException::CoreException(CoreException const & ex) : _holder(0)
	{
		CopyToSelf(ex);
	}

	CoreException& CoreException::operator=(CoreException const & ex)
	{
		if(&ex != this)
			CopyToSelf(ex);
		return *this;
	}

	CoreException::~CoreException()
	{
		DeletePtr(_holder);
	}

	CoreException::CoreException() :
		_holder(0),
		source_code(String::Empty),
		function(String::Empty),
		file(String::Empty),
		line(0U),
		err_code(0U),
		err_msg(String::Empty)
	{}

	CoreException::CoreException(CStr source_code, CStr function, CStr file, UInt32 line) :
		_holder(0),
		source_code(source_code),
		function(function),
		file(file),
		line(line),
		err_code(0U),
		err_msg(String::Empty)
	{}

	CoreException::CoreException(CStr source_code, CStr function, CStr file, UInt32 line, CStr err_msg) :
		_holder(0),
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
		_holder = new String(GetErrText(err_code));
		err_msg = _holder->CStrPtr();
	}
}
