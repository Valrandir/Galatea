#include "Assert.hpp"
#include "Win32/AssertWnd.hpp"
#include "../String/String.hpp"
#include "../Storage/TextFile.hpp"

namespace Core
{
	void LogToFile(String const& msg);
	void ShowAssertWindow(String const& msg);

	void Assert::SystemAbort(CoreException const & ex)
	{
		String msg = String::FormatToString
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
			ex.err_msg.CStrPtr()
		);

		LogToFile(msg);
		ShowAssertWindow(msg);
	}

	void LogToFile(String const& msg)
	{
		using namespace Storage;
		CStr logFileName = Assert::GetLogFileName();
		String log_msg = File::Exists(logFileName) ? String(Text("\r\n")) + msg : msg;
		TextFile::AppendText(logFileName, log_msg);
	}

	void ShowAssertWindow(String const& msg)
	{
		AssertWnd wnd;

		wnd.SetText(msg.CStrPtr());
		wnd.ShowModal();

		ExitProcess(1U);
	}
}
