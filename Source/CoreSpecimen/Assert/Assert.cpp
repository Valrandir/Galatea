#include "../Core.hpp"

using namespace Core;

Bool ReturnTrue()
{
	return true;
}

Bool ReturnFalse()
{
	return false;
}

Bool CheckException(CoreException const & ex, CStr source_code, CStr function, CStr file, UInt line, UInt err_code, CStr err_msg)
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

Bool CoreExceptionTest()
{
	Bool result = true;
	CStr source_code = Text("source_code");
	CStr function = Text("function");
	CStr file = Text("file");
	UInt32 line = 50U;
	CStr err_msg = Text("err_msg");

	//Constructor 1
	{
		CoreException ex;
		CHECK CheckException(ex, String::Empty, String::Empty, String::Empty, 0U, 0U, String::Empty);
	}

	//Constructor 2
	{
		CoreException ex(source_code, function, file, line);
		CHECK CheckException(ex, source_code, function, file, line, 0U, String::Empty);
	}

	//Constructor 3
	{
		CoreException ex(source_code, function, file, line, err_msg);
		CHECK CheckException(ex, source_code, function, file, line, 0U, err_msg);
	}

	//Copy Constructor
	{
		CoreException ex(source_code, function, file, line, err_msg);
		CoreException ex2(ex);
		CHECK CheckException(ex, source_code, function, file, line, 0U, err_msg);
	}

	//operator =
	{
		CoreException ex(source_code, function, file, line, err_msg);
		CoreException ex2 = ex;
		CHECK CheckException(ex, source_code, function, file, line, 0U, err_msg);
	}

	//InitErr
	{
		CoreException ex(source_code, function, file, line);
		UInt32 errCode = 5U;

		SetErrCode(errCode);
		String errText = GetErrText(GetErrCode());

		ex.InitErr();

		CHECK CheckException(ex, source_code, function, file, line, errCode, errText);

		//Copy Constructor
		{
			CoreException ex2(ex);
			CHECK CheckException(ex2, source_code, function, file, line, errCode, errText);
		}

		//operator =
		{
			CoreException ex2 = ex;
			CHECK CheckException(ex2, source_code, function, file, line, errCode, errText);
		}
	}

	//Clear
	{
		CoreException ex(source_code, function, file, line);
		SetErrCode(5U);
		ex.InitErr();
		ex.Clear();
		CHECK CheckException(ex, String::Empty, String::Empty, String::Empty, 0U, 0U, String::Empty);
	}

	return result;
}

Bool AssertTest()
{
	Bool result = true;

	CHECK CoreExceptionTest();

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
