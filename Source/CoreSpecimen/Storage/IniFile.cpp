#include "../Core.hpp"

using namespace Core;
using namespace Storage;

namespace IniFileTestNamespace
{
	CStr _fileName = Text("IniFileTest.txt");

	Bool SomeTest()
	{
		Bool result = true;
		return result;
	}
}

Bool IniFileTest()
{
	Bool result = true;
	using namespace IniFileTestNamespace;

	CHECK SomeTest();

	return result;
}
