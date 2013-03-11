#include "IniFile.hpp"
#include "../../Assert/Assert.hpp"
#include "../TextFile.hpp"

namespace Core
{
	namespace Storage
	{
		IniFile::IniFile(){}
		IniFile::IniFile(IniFile const & value){}
		IniFile& IniFile::operator=(IniFile&){return *this;}

		IniFile IniFile::ReadIniFile(CStr fileName)
		{
			Assert(fileName);
			IniFile inifile;
			String::StrPtrVec* lines;
			String::StrPtrVec::Element* it;

			lines = TextFile::ReadLines(fileName);

			for(it = lines->Begin(); it < lines->End(); ++it)
			{
				String& line = **it;
				//if ltrim line startswith [ then add section and make it active
				//if we have an active section and we can read an "=", split it in key value and add in current section
			}

			return inifile;
		}
	}
}
