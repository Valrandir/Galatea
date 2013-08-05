#include "../Core.hpp"

using namespace Core;
using namespace Storage;

namespace FileTestNamespace
{
	CStr _nullFileName = (CStr)0;
	CStr _fileName = Text("FileTest.txt");
	CStr _badFileName = Text("<MiG-25M>\\X-15:Rocket.");

	Bool CreateTest()
	{
		Bool result = true;
		File* file;
		CoreException corex;

		//Create fail because _fileName is NULL
		CHECK_ASSERT(File::Create(_nullFileName));

		//Create fail because _fileName is bogus path
		CHECK File::Create(_badFileName) == NULL;
		CHECK File::Create(_badFileName, &corex) == NULL;
		CHECK corex.err_code != 0U;
		CHECK corex.err_msg != String::Empty;

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
		CoreException corex;

		//Create fail because _fileName is NULL
		CHECK_ASSERT(File::Open(_nullFileName));

		//Create fail because _fileName is bogus path
		CHECK File::Open(_badFileName) == NULL;
		CHECK File::Open(_badFileName, &corex) == NULL;
		CHECK corex.err_code != 0U;
		CHECK corex.err_msg != String::Empty;

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
		CoreException corex;

		//Create fail because _fileName is NULL
		CHECK_ASSERT(File::OpenReadOnly(_nullFileName));

		//Create fail because _fileName is bogus path
		CHECK File::OpenReadOnly(_badFileName) == NULL;
		CHECK File::OpenReadOnly(_badFileName, &corex) == NULL;
		CHECK corex.err_code != 0U;
		CHECK corex.err_msg != String::Empty;

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

	Bool MoveTest()
	{
		Bool result = true;
		CStr nop = Text("NoFileName.txt");

		//File does not exists, Move returns false
		{
			CHECK false == File::Move(nop, _fileName);
			CHECK false == File::Exists(nop);
			CHECK false == File::Exists(_fileName);
		}

		//File exists, Move returns true
		{
			File* file = File::Create(_fileName);
			DeletePtr(file);

			CHECK true == File::Move(_fileName, nop);
			CHECK true == File::Exists(nop);
			CHECK false == File::Exists(_fileName);

			File::Delete(_fileName);
			File::Delete(nop);
		}

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

	Bool ReadTest()
	{
		Bool result = true;
		//How to make Read fails?
		return result;
	}

	Bool WriteTest()
	{
		Bool result = true;
		//How to make Write fails?
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
	CHECK MoveTest();
	CHECK GetFileSizeTest();
	CHECK GetSeekPosTest();
	CHECK SeekTest();
	CHECK SeekToEndTest();
	CHECK ReadTest();
	CHECK WriteTest();
	CHECK ReadWriteTest();

	return result;
}
