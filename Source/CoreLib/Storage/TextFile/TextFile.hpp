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
			static TextFile* Create(CStr fileName, CoreException* corex = NULL);
			static TextFile* Append(CStr fileName, CoreException* corex = NULL);
			static String ReadAll(CStr fileName, CoreException* corex = NULL);
			static String::StrPtrVec* ReadLines(CStr fileName, CoreException* corex = NULL);
			static void WriteText(CStr fileName, CStr text, UInt textLength);
			static void WriteText(CStr fileName, CStr text);
			static void WriteText(CStr fileName, String text);
			static void AppendText(CStr fileName, CStr text, UInt textLength);
			static void AppendText(CStr fileName, CStr text);
			static void AppendText(CStr fileName, String text);

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
