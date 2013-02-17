#include "Assert.hpp"
#include "Win32/AssertWnd.hpp"
#include "../../String/String.hpp"

void ShowAssertWindow(Core::String msg);

namespace Core
{
	namespace Assert
	{
		void Fail(TChar const * failed_text, TChar const * function, TChar const * file, UInt line)
		{
			static Bool failing = false; if(failing) return; failing = true;

			String msg = String::FormatStr
			(
				Text("Failed Call : %s") NewLine
				Text("Function : %s") NewLine
				Text("File : %s") NewLine
				Text("Line : %d") NewLine,
				failed_text,
				function,
				file,
				line
			);

			ShowAssertWindow(msg);
		}
	}
}

void ShowAssertWindow(Core::String msg)
{
	AssertWnd wnd;

	wnd.SetText(msg.GetTChar());
	wnd.ShowModal();

	ExitProcess(1U);
}
