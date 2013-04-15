#include "Assert.hpp"
#include "Win32/AssertWnd.hpp"
#include "../String/String.hpp"

void ShowAssertWindow(Core::String msg);

namespace Core
{
	Assert::AssertProc Assert::_assertProc = 0;

	Assert::Assert(){}
	Assert::Assert(Assert const &){}
	Assert& Assert::operator=(Assert const &){return *this;}

	void Assert::SetAssertProc(AssertProc assertProc)
	{
		_assertProc = assertProc;
	}

	void Assert::Abort(CoreException const & ex)
	{
		static Bool failing = false; if(failing) return; failing = true;

		if(_assertProc)
			if(_assertProc(ex))
				return;

		String msg = String::FormatToStr
		(
			Text("Failed Call : Assert(%s);") NewLine
			Text("Function : %s") NewLine
			Text("File : %s") NewLine
			Text("Line : %d") NewLine,
			ex.failed_text,
			ex.function,
			ex.file,
			ex.line
		);

		ShowAssertWindow(msg);
	}
}

void ShowAssertWindow(Core::String msg)
{
	AssertWnd wnd;

	wnd.SetText(msg.CStrPtr());
	wnd.ShowModal();

	ExitProcess(1U);
}
