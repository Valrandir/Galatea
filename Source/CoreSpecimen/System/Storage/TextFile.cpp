#include "../../Core.hpp"

using namespace Core;
using namespace System::Storage;

namespace TextFileTestNamespace
{
	CStr _fileName = Text("TextFileTest.txt");

	Bool ReadAllTest()
	{
		Bool result = true;

		TextFile* tf;
		tf = TextFile::Create(_fileName);
		DeletePtr(tf);

		return result;
	}
}

Bool TextFileTest()
{
	Bool result = true;
	using namespace TextFileTestNamespace;

	CHECK(ReadAllTest());

	return result;
}
