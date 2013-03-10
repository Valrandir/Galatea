#pragma once
#include "../File.hpp"
#include "../../String/String.hpp"

namespace Core
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
			static TextFile* Append(CStr fileName);
			static String ReadAll(CStr fileName);
			static String::StrPtrVec* ReadLines(CStr fileName);

			void Write(CStr text, UInt cchLength) const;
			void Write(CStr text) const;
			void Write(String const & text) const;
			void WriteLine(CStr text, UInt cchLength) const;
			void WriteLine(CStr text) const;
			void WriteLine(String const & text) const;
			void WriteLine() const;
			void Close();
			~TextFile();
		};
	}
}
