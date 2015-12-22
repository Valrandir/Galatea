#include "IniFile.hpp"

namespace Galatea
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
