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

		TextFile* TextFile::Create(CStr fileName, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName != nullptr);
			File* file = File::Open(fileName, File::Disposition::CreateAlways, File::Access::AccessWrite, File::Flags::OptimizeForSequentialAccess, out_ex);
			return file ? new TextFile(file) : nullptr;
		}

		TextFile* TextFile::Append(CStr fileName, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName != nullptr);
			File* file = File::Open(fileName, File::Disposition::OpenAlways, File::Access::AccessWrite, File::Flags::OptimizeForSequentialAccess, out_ex);

			if(file)
			{
				file->SeekToEnd();
				return new TextFile(file);
			}

			return nullptr;
		}

		Bool TextFile::ReadAll(CStr fileName, String& text, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName);
			Bool result = false;

			File* file = File::Open(fileName, File::Disposition::OpenExisting, File::Access::AccessRead, File::Flags::ShareRead | File::Flags::OptimizeForSequentialAccess, out_ex);
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
				GALATEA_DELETE_PTR(file);

				if(!result)
				{
					text.Clear();
					text.Shrink();
				}
			}

			return result;
		}

		String::StrPtrVec* TextFile::ReadLines(CStr fileName, Exception* out_ex)
		{
			//Here \r\n is used instead of NewLine so that Linux can see lines from a Windows text file
			ASSERT_PARAMETER(fileName);
			String text;
			if(ReadAll(fileName, text, out_ex))
				return text.Split(text, text.Length(), Text("\r\n"));
			else
				return new String::StrPtrVec();
		}

		Bool TextFile::WriteText(CStr fileName, CStr text, UInt textLength, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);

			TextFile *textFile = TextFile::Create(fileName, out_ex);
			Bool result = false;

			if(textFile)
			{
				result = textFile->Write(text, textLength, out_ex); 
				GALATEA_DELETE_PTR(textFile);
			}

			return result;
		}

		Bool TextFile::WriteText(CStr fileName, CStr text, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);
			return WriteText(fileName, text, String::CStrLength(text), out_ex);
		}

		Bool TextFile::WriteText(CStr fileName, String const & text, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName);
			return WriteText(fileName, text, text.Length(), out_ex);
		}

		Bool TextFile::AppendText(CStr fileName, CStr text, UInt textLength, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);

			TextFile *textFile = TextFile::Append(fileName, out_ex);
			Bool result = false;

			if(textFile)
			{
				result = textFile->Write(text, textLength, out_ex); 
				GALATEA_DELETE_PTR(textFile);
			}

			return result;
		}

		Bool TextFile::AppendText(CStr fileName, CStr text, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(text);
			return AppendText(fileName, text, String::CStrLength(text), out_ex);
		}

		Bool TextFile::AppendText(CStr fileName, String const & text, Exception* out_ex)
		{
			ASSERT_PARAMETER(fileName);
			return AppendText(fileName, text, text.Length(), out_ex);
		}

		File const & TextFile::FileRef() const
		{
			return *_file;
		}

		Bool TextFile::Write(CStr text, UInt textLength, Exception* out_ex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return _file->Write((VoidPtr)text, ToUInt32(textLength) * sizeof(TChar), out_ex);
		}

		Bool TextFile::Write(CStr text, Exception* out_ex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return Write(text, String::CStrLength(text), out_ex);
		}

		Bool TextFile::Write(String const & text, Exception* out_ex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return Write(text, text.Length(), out_ex);
		}

		Bool TextFile::WriteLine(CStr text, UInt textLength, Exception* out_ex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return Write(text, ToUInt32(textLength), out_ex) && Write(NewLine, out_ex);
		}

		Bool TextFile::WriteLine(CStr text, Exception* out_ex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return Write(text, out_ex) && Write(NewLine, out_ex);
		}

		Bool TextFile::WriteLine(String const & text, Exception* out_ex) const
		{
			ASSERT_PARAMETER(text);
			ASSERT(_file);
			return WriteLine(text, text.Length(), out_ex);
		}

		Bool TextFile::WriteLine(Exception* out_ex) const
		{
			ASSERT(_file);
			return Write(NewLine, out_ex);
		}

		void TextFile::Close()
		{
			GALATEA_DELETE_PTR(_file)
		}

		TextFile::~TextFile()
		{
			Close();
		}
	}
}
