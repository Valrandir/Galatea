#include "CoreException.hpp"

namespace Core
{
	CoreException::CoreException(CStr failed_text, CStr function, CStr file, UInt line) :
		failed_text(failed_text),
		function(function),
		file(file),
		line(line)
	{}
}
