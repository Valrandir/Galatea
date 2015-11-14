#include "../Galatea.hpp"

using namespace Galatea;

Bool ReturnTrue()
{
	return true;
}

Bool ReturnFalse()
{
	return false;
}

Bool CheckException(Exception const & ex, CStr source_code, CStr function, CStr file, UInt line, UInt err_code, CStr err_msg)
{
	Bool result = true;

	CHECK String::Compare(ex.source_code, source_code) == 0;
	CHECK String::Compare(ex.function, function) == 0;
	CHECK String::Compare(ex.file, file) == 0;
	CHECK ex.line == line;
	CHECK ex.err_code == err_code;
	CHECK String::Compare(ex.err_msg, err_msg) == 0;

	return result;
}

Bool ExceptionTest()
{
	Bool result = true;
	CStr source_code = Text("source_code");
	CStr function = Text("function");
	CStr file = Text("file");
	UInt32 line = 50U;
	CStr err_msg = Text("err_msg");

	//Constructor 1
	{
		Exception ex;
		CHECK CheckException(ex, String::Empty, String::Empty, String::Empty, 0U, 0U, String::Empty);
	}

	//Constructor 2
	{
		Exception ex(source_code, function, file, line);
		CHECK CheckException(ex, source_code, function, file, line, 0U, String::Empty);
	}

	//Constructor 3
	{
		Exception ex(source_code, function, file, line, err_msg);
		CHECK CheckException(ex, source_code, function, file, line, 0U, err_msg);
	}

	//Copy Constructor
	{
		Exception ex(source_code, function, file, line, err_msg);
		Exception ex2(ex);
		CHECK CheckException(ex, source_code, function, file, line, 0U, err_msg);
	}

	//operator =
	{
		Exception ex(source_code, function, file, line, err_msg);
		Exception ex2 = ex;
		CHECK CheckException(ex, source_code, function, file, line, 0U, err_msg);
	}

	//InitFromLastErr
	{
		Exception ex(source_code, function, file, line);
		UInt32 errCode = 5U;

		SetErrCode(errCode);
		String errText = GetErrText(GetErrCode());

		ex.InitFromLastErr();

		CHECK CheckException(ex, source_code, function, file, line, errCode, errText);

		//Copy Constructor
		{
			Exception ex2(ex);
			CHECK CheckException(ex2, source_code, function, file, line, errCode, errText);
		}

		//operator =
		{
			Exception ex2 = ex;
			CHECK CheckException(ex2, source_code, function, file, line, errCode, errText);
		}
	}

	//Clear
	{
		Exception ex(source_code, function, file, line);
		SetErrCode(5U);
		ex.InitFromLastErr();
		ex.Clear();
		CHECK CheckException(ex, String::Empty, String::Empty, String::Empty, 0U, 0U, String::Empty);
	}

	return result;
}

Bool AssertTest()
{
	Bool result = true;

	CHECK ExceptionTest();

	//ASSERT OK
	ASSERT(ReturnTrue() == true);

	//ASSERT FAIL
	CHECK_ASSERT(ASSERT(ReturnTrue() == false));

	//ASSERT_RANGE
	{
		UInt idx = 10U;
		UInt count = 5U;
		CHECK_ASSERT(ASSERT_RANGE(idx < count));
	}

	//ASSERT_PARAMETER
	{
		CStr text = (CStr)0;
		CHECK_ASSERT(ASSERT_PARAMETER(text));
	}

	//ASSERT_SYSTEMCALL
	{
		CHECK_ASSERT(ASSERT_SYSTEMCALL(ReturnFalse()));
	}

	//ASSERT_MSG
	{
		CHECK_ASSERT(ASSERT_MSG(ReturnFalse(), Text("The Message")));
	}

	return result;
}
