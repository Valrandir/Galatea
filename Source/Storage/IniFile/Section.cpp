#include "IniFile.hpp"

namespace Galatea
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
