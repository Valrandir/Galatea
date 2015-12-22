#pragma once
#include "../File.hpp"
#include "../../String/String.hpp"

namespace Galatea
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
			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize out_ex if it is set.
			static TextFile* Create(CStr fileName, Exception* out_ex = nullptr);

			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize out_ex if it is set.
			static TextFile* Append(CStr fileName, Exception* out_ex = nullptr);

			//On success, return true and assign text to the file content.
			//On failure, return false, the text param is left intact, initialize out_ex if it is set.
			static Bool ReadAll(CStr fileName, String& text, Exception* out_ex = nullptr);

			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize out_ex if it is set.
			static String::StrPtrVec* ReadLines(CStr fileName, Exception* out_ex = nullptr);

			//On failure, return false and initialize out_ex if it is set.
			static Bool WriteText(CStr fileName, CStr text, UInt textLength, Exception* out_ex = nullptr);
			static Bool WriteText(CStr fileName, CStr text, Exception* out_ex = nullptr);
			static Bool WriteText(CStr fileName, String const & text, Exception* out_ex = nullptr);

			//On failure, return false and initialize out_ex if it is set.
			static Bool AppendText(CStr fileName, CStr text, UInt textLength, Exception* out_ex = nullptr);
			static Bool AppendText(CStr fileName, CStr text, Exception* out_ex = nullptr);
			static Bool AppendText(CStr fileName, String const & text, Exception* out_ex = nullptr);

			//Return a pointer to the underlying File instance
			File const & FileRef() const;

			Bool Write(CStr text, UInt textLength, Exception* out_ex = nullptr) const;
			Bool Write(CStr text, Exception* out_ex = nullptr) const;
			Bool Write(String const & text, Exception* out_ex = nullptr) const;
			Bool WriteLine(CStr text, UInt textLength, Exception* out_ex = nullptr) const;
			Bool WriteLine(CStr text, Exception* out_ex = nullptr) const;
			Bool WriteLine(String const & text, Exception* out_ex = nullptr) const;
			Bool WriteLine(Exception* out_ex = nullptr) const;
			void Close();
			~TextFile();
		};
	}
}
