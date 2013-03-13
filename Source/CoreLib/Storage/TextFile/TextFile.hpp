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
			static void WriteAll(CStr fileName, CStr text, UInt textLength);
			static void WriteAll(CStr fileName, CStr text);
			static void WriteAll(CStr fileName, String text);
			static void AppendAll(CStr fileName, CStr text, UInt textLength);
			static void AppendAll(CStr fileName, CStr text);
			static void AppendAll(CStr fileName, String text);

			void Write(CStr text, UInt textLength) const;
			void Write(CStr text) const;
			void Write(String const & text) const;
			void WriteLine(CStr text, UInt textLength) const;
			void WriteLine(CStr text) const;
			void WriteLine(String const & text) const;
			void WriteLine() const;
			void Close();
			~TextFile();
		};
	}
}
