#include "File.Win32.hpp"
#include "../../Assert/Assert.hpp"

namespace Core
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
		File* File::Create(CStr fileName, CoreException* corex)
		{
			ASSERT_PARAMETER(fileName);
			HANDLE hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			ASSERT_COREX(hFile != INVALID_HANDLE_VALUE, corex);
			return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile, false);
		}

		//Return NULL on failure, and initialize corex when specified.
		File* File::Open(CStr fileName, CoreException* corex)
		{
			ASSERT_PARAMETER(fileName);
			HANDLE hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			ASSERT_COREX(hFile != INVALID_HANDLE_VALUE, corex);
			return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile, false);
		}

		File* File::OpenReadOnly(CStr fileName)
		{
			return OpenReadOnly(fileName, CacheMode::Default, NULL);
		}

		File* File::OpenReadOnly(CStr fileName, CoreException* corex)
		{
			return OpenReadOnly(fileName, CacheMode::Default, corex);
		}

		File* File::OpenReadOnly(CStr fileName, CacheMode cacheMode)
		{
			return OpenReadOnly(fileName, cacheMode, NULL);
		}

		//Return NULL on failure, and initialize corex when specified.
		File* File::OpenReadOnly(CStr fileName, CacheMode cacheMode, CoreException* corex)
		{
			ASSERT_PARAMETER(fileName);
			UInt32 flags = cacheMode == CacheMode::Random ? FILE_FLAG_RANDOM_ACCESS : cacheMode == CacheMode::Sequential ? FILE_FLAG_SEQUENTIAL_SCAN : 0U;
			HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL || flags, NULL);
			ASSERT_COREX(hFile != INVALID_HANDLE_VALUE, corex);
			return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile, true);
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

			//ASSERT(GetFileAttributesEx(fileName, GetFileExInfoStandard, &attr));
			GetFileAttributesEx(fileName, GetFileExInfoStandard, &attr);
			li.LowPart = attr.nFileSizeLow;
			li.HighPart = attr.nFileSizeHigh;

			return li.QuadPart;
		}

		UInt64 FileImpl::GetFileSize() const
		{
			ASSERT(_hFile);
			LARGE_INTEGER fileSize = {0};
			//ASSERT(GetFileSizeEx(_hFile, &fileSize));
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
		Bool FileImpl::Read(VoidPtr buffer, UInt bufferSize, CoreException* corex) const
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
		Bool FileImpl::Write(VoidPtr const buffer, UInt bufferSize, CoreException* corex) const
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
