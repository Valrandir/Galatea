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

				void Clear();
			};

			class Section
			{
				public:
				typedef DataStruct::Vector<KeyValue> KeyValueVec;

				String Name;
				KeyValueVec KeyValueList;
				
				void Clear();
				Bool IsEmpty();
			};

			typedef DataStruct::Vector<Section> SectionVec;
			SectionVec SectionList;

			static IniFile* ReadIniFile(CStr fileName);
		};
	}
}
