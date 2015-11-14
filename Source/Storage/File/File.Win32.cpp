#include "File.Win32.hpp"
#include "../../Assert/Assert.hpp"

namespace Galatea
{
	namespace Storage
	{
		FileImpl::FileImpl(HANDLE hFile, Bool readOnly) : _hFile(hFile), _isReadOnly(readOnly)
		{
		}

		FileImpl::~FileImpl()
		{
			Close();
		}

		//Return NULL on failure, and initialize corex when specified.
		File* File::Open(CStr fileName, DispositionEnum behavior, AccessEnum access, UInt32 flags, Exception* corex)
		{
			ASSERT_PARAMETER(fileName);

			DWORD desiredAccess = 0;
			switch(access)
			{
				case AccessEnum::AccessRead: desiredAccess = GENERIC_READ; break;
				case AccessEnum::AccessWrite: desiredAccess = GENERIC_WRITE; break;
				case AccessEnum::AccessReadWrite: desiredAccess = GENERIC_READ | GENERIC_WRITE; break;
			}

			DWORD shareMode = 0;
			if(flags && FlagsEnum::ShareRead) shareMode |= FILE_SHARE_READ;
			if(flags && FlagsEnum::ShareWrite) shareMode |= FILE_SHARE_WRITE;

			DWORD creationDisposition;
			switch(behavior)
			{
				case DispositionEnum::CreateAlways : creationDisposition = CREATE_ALWAYS; break;
				case DispositionEnum::CreateNew : creationDisposition = CREATE_NEW; break;
				case DispositionEnum::OpenAlways : creationDisposition = OPEN_ALWAYS; break;
				case DispositionEnum::OpenExisting : creationDisposition = OPEN_EXISTING; break;
				case DispositionEnum::TruncateExisting : creationDisposition = TRUNCATE_EXISTING; break;
				default: creationDisposition = 0;
			}

			DWORD flagsAndAttributes = FILE_ATTRIBUTE_NORMAL | (flags & FlagsEnum::OptimizeForSequentialAccess ? FILE_FLAG_SEQUENTIAL_SCAN : FILE_FLAG_RANDOM_ACCESS);

			HANDLE hFile = CreateFile(fileName, desiredAccess, shareMode, NULL, creationDisposition, flagsAndAttributes, NULL);
			ASSERT_COREX(hFile != INVALID_HANDLE_VALUE, corex);
			return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile, false);
		}

		Bool File::Exists(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			DWORD attr = GetFileAttributes(fileName);
			return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
		}

		Bool File::Delete(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			return DeleteFile(fileName) != 0;
		}

		Bool File::Move(CStr fileName, CStr newName)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(newName);
 			return MoveFile(fileName, newName) != 0;
		}

		UInt64 File::GetFileSize(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			WIN32_FILE_ATTRIBUTE_DATA attr = {0};
			LARGE_INTEGER li = {0};

			GetFileAttributesEx(fileName, GetFileExInfoStandard, &attr);
			li.LowPart = attr.nFileSizeLow;
			li.HighPart = attr.nFileSizeHigh;

			return li.QuadPart;
		}

		UInt64 FileImpl::GetFileSize() const
		{
			ASSERT(_hFile);
			LARGE_INTEGER fileSize = {0};
			ASSERT(GetFileSizeEx(_hFile, &fileSize));
			return fileSize.QuadPart;
		}

		UInt64 FileImpl::GetSeekPos() const
		{
			ASSERT(_hFile);
			LARGE_INTEGER distance = {0};
			LARGE_INTEGER newPosition = {0};
			SetFilePointerEx(_hFile, distance, &newPosition, FILE_CURRENT);
			return newPosition.QuadPart;
		}

		void FileImpl::Seek(UInt64 position) const
		{
			ASSERT(_hFile);
			LARGE_INTEGER li;
			li.QuadPart = position;
			SetFilePointerEx(_hFile, li, 0, FILE_BEGIN);
		}

		void FileImpl::SeekToEnd() const
		{
			ASSERT(_hFile);
			LARGE_INTEGER li;
			li.QuadPart = 0U;
			SetFilePointerEx(_hFile, li, 0, FILE_END);
		}

		//When corex is NULL, ASSERT on failure.
		//When corex is not NULL, return false on failure.
		//Return true on success
		Bool FileImpl::Read(VoidPtr buffer, UInt bufferSize, Exception* corex) const
		{
			ASSERT(_hFile);
			ASSERT_PARAMETER(buffer != 0);
			DWORD bytesRead;
			Bool result = ReadFile(_hFile, buffer, ToUInt32(bufferSize), &bytesRead, 0) != FALSE;
			ASSERT_COREX(result, corex);
			if(!corex) ASSERT_SYSTEMCALL(result);
			return result;
		}

		//When corex is NULL, ASSERT on failure.
		//When corex is not NULL, return false on failure.
		//Return true on success
		Bool FileImpl::Write(VoidPtr const buffer, UInt bufferSize, Exception* corex) const
		{
			ASSERT(_hFile);
			ASSERT_PARAMETER(buffer != 0);
			ASSERT(_isReadOnly == false);
			DWORD bytesWritten;
			Bool result = WriteFile(_hFile, buffer, ToUInt32(bufferSize), &bytesWritten, 0) != FALSE;
			ASSERT_COREX(result, corex);
			if(!corex) ASSERT_SYSTEMCALL(result);
			return result;
		}

		void FileImpl::Close()
		{
			if(_hFile)
			{
				CloseHandle(_hFile);
				_hFile = 0;
			}
		}
	}
}
