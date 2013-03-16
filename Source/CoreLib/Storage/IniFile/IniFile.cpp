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

		IniFile* IniFile::ReadIniFile(CStr fileName)
		{
			Assert(fileName);
			CStr braceOpen = Text("[");
			//CStr braceClose = Text("]");
			CStr equal = Text("=");
			IniFile* iniFile;
			String::StrPtrVec* lines;
			String::StrPtrVec::Element* it;
			Section section;
			Int index;
			KeyValue keyValue;

			iniFile = new IniFile();
			lines = TextFile::ReadLines(fileName);

			for(it = lines->Begin(); it < lines->End(); ++it)
			{
				String& line = **it;
				if(line.TrimLeft().StartsWith(braceOpen))
				{
					if(!section.IsEmpty())
					{
						iniFile->SectionList.Add(section);
						section.Clear();
					}
					section.Name = line;
				}
				else if((index = line.IndexOf(equal)) != -1)
				{
					if(!section.Name.IsEmpty())
					{
						keyValue.Key = line.SubString(0U, index - 2).Trim();
						keyValue.Value = line.SubString(index - 1, line.Length() - index - 1).Trim();
						section.KeyValueList.Add(keyValue);
					}
				}
			}

			return iniFile;
		}
	}
}
