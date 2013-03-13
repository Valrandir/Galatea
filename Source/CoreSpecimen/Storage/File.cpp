#include "../Core.hpp"

using namespace Core;
using namespace Storage;

namespace FileTestNamespace
{
	CStr _fileName = Text("FileTest.txt");

	Bool CreateTest()
	{
		Bool result = true;
		File* file;

		//File does not exists, create it and size will be 0 and SeekPos will be 0
		File::Delete(_fileName);
		CHECK (file = File::Create(_fileName));
		CHECK file->GetFileSize() == 0;
		CHECK file->GetSeekPos() == 0;
		DeletePtr(file);

		//File exists, create it and it will be truncated and SeekPos will be 0
		CHECK (file = File::Create(_fileName));
		CHECK file->GetFileSize() == 0;
		CHECK file->GetSeekPos() == 0;
		DeletePtr(file);

		File::Delete(_fileName);

		return result;
	}

	Bool OpenTest()
	{
		Bool result = true;
		File* file;

		//File does not exists, open it and it will fail
		File::Delete(_fileName);
		file = File::Open(_fileName);
		CHECK file == 0;

		//File exists, open it and it will work
		CHECK (file = File::Create(_fileName));
		DeletePtr(file);
		CHECK (file = File::Open(_fileName));
		DeletePtr(file);

		File::Delete(_fileName);

		return result;
	}

	Bool OpenReadOnlyTest()
	{
		Bool result = true;
		File* file;
		String text;
		UInt fileSize;

		//File does not exists, open it and it will fail
		File::Delete(_fileName);
		file = File::OpenReadOnly(_fileName);
		CHECK file == 0;

		//File exists, open it and it will work, write to it and it will fail
		CHECK (file = File::Create(_fileName));
		file->Write((VoidPtr)_fileName, String::CStrByteSize(_fileName));
		DeletePtr(file);
		CHECK (file = File::OpenReadOnly(_fileName));
		fileSize = ToUInt(file->GetFileSize());
		text.Reserve(fileSize / sizeof(TChar));
		file->Read(text.DrivePointer(fileSize / sizeof(TChar)), fileSize);
		CHECK text == _fileName;
		DeletePtr(file);

		File::Delete(_fileName);

		return result;
	}

	Bool ExistsTest()
	{
		Bool result = true;
		File* file;

		//File does not exists, Exists returns false
		File::Delete(_fileName);
		CHECK File::Exists(_fileName) == false;

		//File exists, Exists returns true
		file = File::Create(_fileName);
		DeletePtr(file)
		CHECK File::Exists(_fileName) == true;

		File::Delete(_fileName);

		return result;
	}

	Bool DeleteTest()
	{
		Bool result = true;
		File* file;

		//File does not exists, Delete returns false
		CHECK File::Delete(_fileName) == false;

		//File exists, Delete returns true, then file no longer exists
		file = File::Create(_fileName);
		DeletePtr(file)
		CHECK File::Delete(_fileName) == true;
		CHECK File::Exists(_fileName) == false;

		return result;
	}

	Bool GetFileSizeTest()
	{
		Bool result = true;
		File* file;

		//File does not exists, GetFileSize returns 0
		File::Delete(_fileName);
		CHECK File::GetFileSize(_fileName) == 0;

		//File exists, but is empty, GetFileSize returns 0
		file = File::Create(_fileName);
		CHECK file->GetFileSize() == 0;
		DeletePtr(file)
		CHECK File::GetFileSize(_fileName) == 0;

		//File exists, and is not empty, GetFileSize returns size
		file = File::Open(_fileName);
		file->Write((VoidPtr)_fileName, 5);
		CHECK file->GetFileSize() == 5;
		DeletePtr(file)
		CHECK File::GetFileSize(_fileName) == 5;

		File::Delete(_fileName);

		return result;
	}

	Bool GetSeekPosTest()
	{
		Bool result = true;
		File* file;

		//SeekPos is at zero, GetSeekPos returns 0
		file = File::Create(_fileName);
		CHECK file->GetSeekPos() == 0;

		//SeekPos is at 5, GetSeekPos returns 5
		file->Write((VoidPtr)_fileName, 5);
		CHECK file->GetSeekPos() == 5;

		DeletePtr(file)
		File::Delete(_fileName);

		return result;
	}

	Bool SeekTest()
	{
		Bool result = true;
		File* file;

		//Seek is at 0, GetSeekPos returns 0
		file = File::Create(_fileName);
		CHECK file->GetSeekPos() == 0;

		//Seek is at 3, GetSeekPos returns 3
		file->Write((VoidPtr)_fileName, 3);
		CHECK file->GetSeekPos() == 3;

		DeletePtr(file)
		File::Delete(_fileName);

		return result;
	}

	Bool SeekToEndTest()
	{
		Bool result = true;
		File* file;

		//Create, write 6 bytes and close
		file = File::Create(_fileName);
		file->Write((VoidPtr)_fileName, 6);
		DeletePtr(file);

		//Create, GetSeekPos returns 0, SeekToEnd, GetSeekPos returns 6
		file = File::Open(_fileName);
		CHECK file->GetSeekPos() == 0;
		file->SeekToEnd();
		CHECK file->GetSeekPos() == 6;

		DeletePtr(file)
		File::Delete(_fileName);

		return result;
	}

	Bool ReadWriteTest()
	{
		Bool result = true;
		File* file;
		UInt32 const bufferSize = 1024;
		TChar buffer[bufferSize];

		file = File::Create(_fileName);
		file->Write((VoidPtr)_fileName, String::CStrByteSize(_fileName) + sizeof(TChar));
		file->Seek(0);
		file->Read(buffer, bufferSize);
		DeletePtr(file);
		File::Delete(_fileName);

		String read = buffer;
		CHECK String::Compare(_fileName, read) == 0;

		return result;
	}
}

Bool FileTest()
{
	Bool result = true;
	using namespace FileTestNamespace;

	CHECK CreateTest();
	CHECK OpenTest();
	CHECK OpenReadOnlyTest();
	CHECK ExistsTest();
	CHECK DeleteTest();
	CHECK GetFileSizeTest();
	CHECK GetSeekPosTest();
	CHECK SeekTest();
	CHECK SeekToEndTest();
	CHECK ReadWriteTest();

	return result;
}
