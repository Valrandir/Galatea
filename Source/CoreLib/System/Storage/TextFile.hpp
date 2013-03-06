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
				String ReadLine() const;
				void Write(CStr text, UInt32 cchLength) const;
				void Write(CStr text) const;
				void Write(String const & text) const;
				void WriteLine(CStr text, UInt32 cchLength) const;
				void WriteLine(CStr text) const;
				void WriteLine(String const & text) const;
				void Close();
				~TextFile();
			};
		}
	}
}
