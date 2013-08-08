#include "Assert.hpp"

namespace Core
{
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

		//Do something for Linux here
		//ShowAssertWindow(msg);
	}
}
