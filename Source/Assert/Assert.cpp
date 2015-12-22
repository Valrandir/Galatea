#include "Assert.hpp"

namespace Galatea
{
	CStr AssertType_Default = Text("Default Assert Type");
	CStr AssertType_IndexOutOfRange = Text("Index Out Of Range");
	CStr AssertType_NullParameter = Text("Null Parameter");
	CStr AssertType_SystemCall = Text("System Call Failed");
	CStr AssertType_Undefined = Text("Undefined Assert Type");

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

	CStr Assert::AssertTypeToCStr(AssertType assertType)
	{
		CStr msg;

		switch(assertType)
		{
			case AssertType::Default: msg = AssertType_Default; break;
			case AssertType::IndexOutOfRange: msg = AssertType_IndexOutOfRange; break;
			case AssertType::NullParameter: msg = AssertType_NullParameter; break;
			case AssertType::SystemCall: msg = AssertType_SystemCall; break;
			default: msg = AssertType_Undefined;
		}

		return msg;
	}

	void Assert::Abort(Exception const & ex)
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
