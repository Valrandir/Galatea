#include "IniFile.hpp"

namespace Core
{
	namespace Storage
	{
		void IniFile::Section::Clear()
		{
			Name.Clear();
			KeyValueList.Clear();
		}

		Bool IniFile::Section::IsEmpty()
		{
			return KeyValueList.IsEmpty();
		}
	}
}
