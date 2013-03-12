#include "../Core.hpp"

using namespace Core;
using namespace Storage;

namespace IniFileTestNamespace
{
	CStr _fileName = Text("IniFileTest.txt");

	Bool SomeTest()
	{
		Bool result = true;
		CStr iniFileName = Text("IniFile.ini");
		TextFile* textFile;

		CStr text =
			Text("[Resolution]") NewLine
			Text("ResX = 1024") NewLine
			Text("ResY = 768") NewLine
			NewLine
			Text("[General]") NewLine
			Text("Music = Yes") NewLine
			Text("Effects = Yes") NewLine
			Text("Autosave = Yes") NewLine
			Text("Autoload = No") NewLine
			Text("ExportMode = All") NewLine
		;

		textFile = TextFile::Create(iniFileName);
		textFile->Write(text);
		DeletePtr(textFile);

		IniFile& iniFile = IniFile::ReadIniFile(iniFileName);

		File::Delete(iniFileName);

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
