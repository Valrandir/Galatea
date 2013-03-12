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
			CStr braceOpen = Text("[");
			CStr braceClose = Text("]");
			IniFile iniFile;
			String::StrPtrVec* lines;
			String::StrPtrVec::Element* it;
			Section section;

			lines = TextFile::ReadLines(fileName);

			for(it = lines->Begin(); it < lines->End(); ++it)
			{
				String& line = **it;
				if(line.TrimLeft().StartsWith(braceOpen))
				{
					if(!section.KeyValueList.IsEmpty())
					{
						iniFile.SectionList.Add(section);
					}
				}
				//if ltrim line startswith [ then add section and make it active
				//if we have an active section and we can read an "=", split it in key value and add in current section
			}

			return iniFile;
		}
	}
}
