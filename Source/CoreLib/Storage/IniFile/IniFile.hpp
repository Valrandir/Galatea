#pragma once
#include "../../DataStruct/Vector.hpp"
#include "../../String/String.hpp"

namespace Core
{
	namespace Storage
	{
		class IniFile
		{
			IniFile();
			IniFile(IniFile const &);
			IniFile& operator=(IniFile&);

			public:
			class KeyValue
			{
				public:
				String Key;
				String Value;
			};

			class Section
			{
				public:
				typedef DataStruct::Vector<KeyValue> KeyValueVec;

				String Name;
				KeyValueVec KeyValueList;
			};

			typedef DataStruct::Vector<Section> SectionVec;
			SectionVec SectionList;

			static IniFile ReadIniFile(CStr fileName);
		};
	}
}
