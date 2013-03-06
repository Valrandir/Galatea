#pragma once
#include "File.hpp"
#include "../../String/String.hpp"

namespace Core
{
	namespace System
	{
		namespace Storage
		{
			class TextFile
			{
				File* _file;

				TextFile(File* file);
				TextFile(TextFile const &);
				TextFile& operator=(TextFile&);

				public:
				static TextFile* Create(CStr fileName);
				static TextFile* Open(CStr fileName);
				static TextFile* OpenReadOnly(CStr fileName);
				String ReadAll() const;
				void WriteText(CStr text) const;
				void WriteText(String text) const;
				void Close();
				~TextFile();
			};
		}
	}
}
