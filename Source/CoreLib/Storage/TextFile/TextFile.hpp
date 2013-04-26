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
			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize corex if it is set.
			static TextFile* Create(CStr fileName, CoreException* corex = NULL);

			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize corex if it is set.
			static TextFile* Append(CStr fileName, CoreException* corex = NULL);

			//On success, return true and assign text to the file content.
			//On failure, return false, the text param is left intact, initialize corex if it is set.
			static Bool ReadAll(CStr fileName, String& text, CoreException* corex = NULL);

			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize corex if it is set.
			static String::StrPtrVec* ReadLines(CStr fileName, CoreException* corex = NULL);

			//On failure, return false and initialize corex if it is set.
			static Bool WriteText(CStr fileName, CStr text, UInt textLength, CoreException* corex = NULL);
			static Bool WriteText(CStr fileName, CStr text, CoreException* corex = NULL);
			static Bool WriteText(CStr fileName, String const & text, CoreException* corex = NULL);

			//On failure, return false and initialize corex if it is set.
			static Bool AppendText(CStr fileName, CStr text, UInt textLength, CoreException* corex = NULL);
			static Bool AppendText(CStr fileName, CStr text, CoreException* corex = NULL);
			static Bool AppendText(CStr fileName, String const & text, CoreException* corex = NULL);

			//Return a pointer to the underlying File instance
			File const & FileRef() const;

			Bool Write(CStr text, UInt textLength, CoreException* corex = NULL) const;
			Bool Write(CStr text, CoreException* corex = NULL) const;
			Bool Write(String const & text, CoreException* corex = NULL) const;
			Bool WriteLine(CStr text, UInt textLength, CoreException* corex = NULL) const;
			Bool WriteLine(CStr text, CoreException* corex = NULL) const;
			Bool WriteLine(String const & text, CoreException* corex = NULL) const;
			Bool WriteLine(CoreException* corex = NULL) const;
			void Close();
			~TextFile();
		};
	}
}
