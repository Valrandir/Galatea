#include "IniFile.hpp"

namespace Core
{
	namespace Storage
	{
		void IniFile::KeyValue::Clear()
		{
			Key.Clear();
			Value.Clear();
		}
	}
}
