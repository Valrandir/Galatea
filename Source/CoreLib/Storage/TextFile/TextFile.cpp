#include "TextFile.hpp"
#include "../../Assert/Assert.hpp"

namespace Core
{
	namespace Storage
	{
		TextFile::TextFile(File* file) : _file(file)
		{
			ASSERT_PARAMETER(file != NULL);
		}

		TextFile::TextFile(TextFile const &)
		{
		}

		TextFile& TextFile::operator=(TextFile&)
		{
			return *this;
		}

		TextFile* TextFile::Create(CStr fileName, CoreException* corex)
		{
			ASSERT_PARAMETER(fileName != NULL);
			File* file = File::Create(fileName, corex);
			return file ? new TextFile(file) : NULL;
		}

		TextFile* TextFile::Append(CStr fileName, CoreException* corex)
		{
			ASSERT_PARAMETER(fileName != NULL);
			File* file = File::Open(fileName, corex);

			if(file)
			{
				file->SeekToEnd();
				return new TextFile(file);
			}

			return NULL;
		}

		String TextFile::ReadAll(CStr fileName, CoreException* corex)
		{
			ASSERT_PARAMETER(fileName);
			File* file;
			String text;
			UInt fileSize;
			UInt length;
			TChar* buffer;

			file = File::OpenReadOnly(fileName, corex);
			if(file)
			{
				fileSize = ToUInt(file->GetFileSize());
				length = fileSize / sizeof(TChar);
				text.Reserve(length);
				buffer = text.DrivePointer(length);
				file->Read(buffer, fileSize);
				DeletePtr(file);
			}

			return text;
		}

		String::StrPtrVec* TextFile::ReadLines(CStr fileName, CoreException* corex)
		{
			//Here \r\n is used instead of NewLine,
			//so that Linux can see lines from a Windows text file
			ASSERT_PARAMETER(fileName);
			auto text = ReadAll(fileName, corex);
			auto lines = text.Split(text, text.Length(), Text("\r\n"));
			return lines;
		}

		void TextFile::WriteText(CStr fileName, CStr text, UInt textLength)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);
			TextFile *textFile = TextFile::Create(fileName);
			textFile->Write(text, textLength); 
			DeletePtr(textFile);
		}

		void TextFile::WriteText(CStr fileName, CStr text)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);
			WriteText(fileName, text, String::CStrLength(text));
		}

		void TextFile::WriteText(CStr fileName, String text)
		{
			ASSERT_PARAMETER(fileName);
			WriteText(fileName, text, text.Length());
		}

		void TextFile::AppendText(CStr fileName, CStr text, UInt textLength)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);
			TextFile *textFile = TextFile::Append(fileName);
			textFile->Write(text, textLength); 
			DeletePtr(textFile);
		}

		void TextFile::AppendText(CStr fileName, CStr text)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);
			AppendText(fileName, text, String::CStrLength(text));
		}

		void TextFile::AppendText(CStr fileName, String text)
		{
			ASSERT_PARAMETER(fileName);
			AppendText(fileName, text, text.Length());
		}

		void TextFile::Write(CStr text, UInt textLength) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			_file->Write((VoidPtr)text, ToUInt32(textLength) * sizeof(TChar));
		}

		void TextFile::Write(CStr text) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			Write(text, String::CStrLength(text));
		}

		void TextFile::Write(String const & text) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			Write(text, text.Length());
		}

		void TextFile::WriteLine(CStr text, UInt textLength) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			Write(text, ToUInt32(textLength));
			Write(NewLine);
		}

		void TextFile::WriteLine(CStr text) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			Write(text);
			Write(NewLine);
		}

		void TextFile::WriteLine(String const & text) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			WriteLine(text, text.Length());
		}

		void TextFile::WriteLine() const
		{
			ASSERT(_file);
			Write(NewLine);
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
