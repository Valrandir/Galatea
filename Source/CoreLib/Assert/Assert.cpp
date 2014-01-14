#include "Assert.hpp"

namespace Core
{
	CStr AssertTypeEnum_Default = Text("Default Assert Type");
	CStr AssertTypeEnum_IndexOutOfRange = Text("Index Out Of Range");
	CStr AssertTypeEnum_NullParameter = Text("Null Parameter");
	CStr AssertTypeEnum_SystemCall = Text("System Call Failed");
	CStr AssertTypeEnum_Undefined = Text("Undefined Assert Type");

	Assert::AssertProc Assert::_assertProc = 0;
	CStr Assert::_logFileName = LOG_FILENAME;

	Assert::Assert(){}
	Assert::Assert(Assert const &){}
	Assert& Assert::operator=(Assert const &){return *this;}

	Bool Assert::Failing = false;

	void Assert::SetAssertProc(AssertProc assertProc)
	{
		_assertProc = assertProc;
	}
	
	CStr Assert::GetLogFileName()
	{
		return _logFileName;
	}

	void Assert::SetLogFileName(CStr logFileName)
	{
		_logFileName = logFileName;
	}

	CStr Assert::AssertTypeToCStr(AssertTypeEnum assertType)
	{
		CStr msg;

		switch(assertType)
		{
			case AssertTypeEnum::Default: msg = AssertTypeEnum_Default; break;
			case AssertTypeEnum::IndexOutOfRange: msg = AssertTypeEnum_IndexOutOfRange; break;
			case AssertTypeEnum::NullParameter: msg = AssertTypeEnum_NullParameter; break;
			case AssertTypeEnum::SystemCall: msg = AssertTypeEnum_SystemCall; break;
			default: msg = AssertTypeEnum_Undefined;
		}

		return msg;
	}

	void Assert::Abort(CoreException const & ex)
	{
		if(Failing)
			return;

		Failing = true;

		if(_assertProc)
			if(_assertProc(ex))
				return;

		SystemAbort(ex);
	}
}
