#include "Assert.hpp"
#include "Win32/AssertWnd.hpp"
#include "../String/String.hpp"

void ShowAssertWindow(Core::String msg);

namespace Core
{
	void Assert::SystemAbort(CoreException const & ex)
	{
		String msg = String::FormatToStr
		(
			Text("Source Code : Assert(%s);") NewLine
			Text("Function : %s") NewLine
			Text("File : %s") NewLine
			Text("Line : %u") NewLine
			Text("Error Code : %u") NewLine
			Text("Error Message : %s") NewLine,
			ex.source_code,
			ex.function,
			ex.file,
			ex.line,
			ex.err_code,
			ex.err_msg
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
