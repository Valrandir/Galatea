#include "TextFile.hpp"
#include "../Assert/Assert.hpp"

namespace Core
{
	namespace System
	{
		namespace Storage
		{
			TextFile::TextFile(File* file) : _file(file)
			{
				Assert(file != NULL);
			}

			TextFile::TextFile(TextFile const &)
			{
			}

			TextFile& TextFile::operator=(TextFile&)
			{
				return *this;
			}

			TextFile* TextFile::Create(CStr fileName)
			{
				Assert(fileName != NULL);
				File* file = File::Create(fileName);
				return file ? new TextFile(file) : NULL;
			}

			TextFile* TextFile::Open(CStr fileName)
			{
				Assert(fileName != NULL);
				File* file = File::Open(fileName);
				return file ? new TextFile(file) : NULL;
			}

			TextFile* TextFile::OpenReadOnly(CStr fileName)
			{
				Assert(fileName != NULL);
				File* file = File::OpenReadOnly(fileName);
				return file ? new TextFile(file) : NULL;
			}

			String TextFile::ReadAll() const
			{
				Assert(_file);

				UInt32 fileSize = ToUInt32(_file->GetFileSize());
				String text(fileSize);
				TChar* buffer = text.DrivePointer(fileSize);
				_file->Read(buffer, fileSize);

				return text;
			}

			void TextFile::WriteText(CStr text) const
			{
				Assert(_file);
				UInt32 textSize = ToUInt32(String::GetTCharLength(text));
				_file->Write((VoidPtr)text, textSize);
			}

			void TextFile::WriteText(String text) const
			{
				Assert(_file);
				_file->Write((VoidPtr)text.GetTChar(), text.GetLength());
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
}
