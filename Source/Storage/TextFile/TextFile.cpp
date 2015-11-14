#include "TextFile.hpp"
#include "../../Assert/Assert.hpp"

namespace Galatea
{
	namespace Storage
	{
		TextFile::TextFile(File* file) : _file(file)
		{
			ASSERT_PARAMETER(file);
		}

		TextFile::TextFile(TextFile const &)
		{
		}

		TextFile& TextFile::operator=(TextFile&)
		{
			return *this;
		}

		TextFile* TextFile::Create(CStr fileName, Exception* corex)
		{
			ASSERT_PARAMETER(fileName != NULL);
			File* file = File::Open(fileName, File::DispositionEnum::CreateAlways, File::AccessEnum::AccessWrite, File::FlagsEnum::OptimizeForSequentialAccess, corex);
			return file ? new TextFile(file) : NULL;
		}

		TextFile* TextFile::Append(CStr fileName, Exception* corex)
		{
			ASSERT_PARAMETER(fileName != NULL);
			File* file = File::Open(fileName, File::DispositionEnum::CreateAlways, File::AccessEnum::AccessWrite, File::FlagsEnum::OptimizeForSequentialAccess, corex);

			if(file)
			{
				file->SeekToEnd();
				return new TextFile(file);
			}

			return NULL;
		}

		Bool TextFile::ReadAll(CStr fileName, String& text, Exception* corex)
		{
			ASSERT_PARAMETER(fileName);
			Bool result = false;

			File* file = File::Open(fileName, File::DispositionEnum::OpenExisting, File::AccessEnum::AccessRead, File::FlagsEnum::ShareRead | File::FlagsEnum::OptimizeForSequentialAccess, corex);
			if(file)
			{
				UInt fileSize = ToUInt(file->GetFileSize());
				UInt length = fileSize / sizeof(TChar);

				//If fileSize is odd then +1 will compensate the division rounding
				if(fileSize % 2)
					++fileSize;

				text.Reserve(length);

				TChar* buffer = text.DrivePointer(length);
				result = file->Read(buffer, fileSize);
				DeletePtr(file);

				if(!result)
				{
					text.Clear();
					text.Shrink();
				}
			}

			return result;
		}

		String::StrPtrVec* TextFile::ReadLines(CStr fileName, Exception* corex)
		{
			//Here \r\n is used instead of NewLine so that Linux can see lines from a Windows text file
			ASSERT_PARAMETER(fileName);
			String text;
			if(ReadAll(fileName, text, corex))
				return text.Split(text, text.Length(), Text("\r\n"));
			else
				return new String::StrPtrVec();
		}

		Bool TextFile::WriteText(CStr fileName, CStr text, UInt textLength, Exception* corex)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);

			TextFile *textFile = TextFile::Create(fileName, corex);
			Bool result = false;

			if(textFile)
			{
				result = textFile->Write(text, textLength, corex); 
				DeletePtr(textFile);
			}

			return result;
		}

		Bool TextFile::WriteText(CStr fileName, CStr text, Exception* corex)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);
			return WriteText(fileName, text, String::CStrLength(text), corex);
		}

		Bool TextFile::WriteText(CStr fileName, String const & text, Exception* corex)
		{
			ASSERT_PARAMETER(fileName);
			return WriteText(fileName, text, text.Length(), corex);
		}

		Bool TextFile::AppendText(CStr fileName, CStr text, UInt textLength, Exception* corex)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);

			TextFile *textFile = TextFile::Append(fileName, corex);
			Bool result = false;

			if(textFile)
			{
				result = textFile->Write(text, textLength, corex); 
				DeletePtr(textFile);
			}

			return result;
		}

		Bool TextFile::AppendText(CStr fileName, CStr text, Exception* corex)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);
			return AppendText(fileName, text, String::CStrLength(text), corex);
		}

		Bool TextFile::AppendText(CStr fileName, String const & text, Exception* corex)
		{
			ASSERT_PARAMETER(fileName);
			return AppendText(fileName, text, text.Length(), corex);
		}

		File const & TextFile::FileRef() const
		{
			return *_file;
		}

		Bool TextFile::Write(CStr text, UInt textLength, Exception* corex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return _file->Write((VoidPtr)text, ToUInt32(textLength) * sizeof(TChar), corex);
		}

		Bool TextFile::Write(CStr text, Exception* corex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return Write(text, String::CStrLength(text), corex);
		}

		Bool TextFile::Write(String const & text, Exception* corex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return Write(text, text.Length(), corex);
		}

		Bool TextFile::WriteLine(CStr text, UInt textLength, Exception* corex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return Write(text, ToUInt32(textLength), corex) && Write(NewLine, corex);
		}

		Bool TextFile::WriteLine(CStr text, Exception* corex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return Write(text, corex) && Write(NewLine, corex);
		}

		Bool TextFile::WriteLine(String const & text, Exception* corex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return WriteLine(text, text.Length(), corex);
		}

		Bool TextFile::WriteLine(Exception* corex) const
		{
			ASSERT(_file);
			return Write(NewLine, corex);
		}

		void TextFile::Close()
		{
			DeletePtr(_file)
		}

		TextFile::~TextFile()
		{
			Close();
		}
	}
}
