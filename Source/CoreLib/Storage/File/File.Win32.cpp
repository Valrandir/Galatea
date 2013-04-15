#include "File.Win32.hpp"
#include "../../Assert/Assert.hpp"

namespace Core
{
	namespace Storage
	{
		FileImpl::FileImpl(HANDLE hFile, Bool readOnly) : _hFile(hFile), _isReadOnly(readOnly)
		{
		}

		File* File::Create(CStr fileName)
		{
			ASSERT(fileName != NULL);
			HANDLE hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile, false);
		}

		File* File::Open(CStr fileName)
		{
			ASSERT(fileName != NULL);
			HANDLE hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile, false);
		}

		File* File::OpenReadOnly(CStr fileName)
		{
			ASSERT(fileName != NULL);
			HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile, true);
		}

		Bool File::Exists(CStr fileName)
		{
			ASSERT(fileName != NULL);
			DWORD attr = GetFileAttributes(fileName);
			return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
		}

		Bool File::Delete(CStr fileName)
		{
			ASSERT(fileName != NULL);
			return DeleteFile(fileName) != 0;
		}

		UInt64 File::GetFileSize(CStr fileName)
		{
			ASSERT(fileName != NULL);
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
			ASSERT(_hFile != 0);
			LARGE_INTEGER fileSize = {0};
			ASSERT(GetFileSizeEx(_hFile, &fileSize));
			return fileSize.QuadPart;
		}

		UInt64 FileImpl::GetSeekPos() const
		{
			ASSERT(_hFile != 0);
			LARGE_INTEGER distance = {0};
			LARGE_INTEGER newPosition = {0};
			SetFilePointerEx(_hFile, distance, &newPosition, FILE_CURRENT);
			return newPosition.QuadPart;
		}

		void FileImpl::Seek(UInt64 position) const
		{
			ASSERT(_hFile != 0);
			LARGE_INTEGER li;
			li.QuadPart = position;
			SetFilePointerEx(_hFile, li, 0, FILE_BEGIN);
		}

		void FileImpl::SeekToEnd() const
		{
			ASSERT(_hFile != 0);
			LARGE_INTEGER li;
			li.QuadPart = 0U;
			SetFilePointerEx(_hFile, li, 0, FILE_END);
		}

		void FileImpl::Read(VoidPtr buffer, UInt bufferSize) const
		{
			ASSERT(buffer != 0);
			ASSERT(_hFile != 0);
			DWORD bytesRead;
			BOOL readResult = ReadFile(_hFile, buffer, ToUInt32(bufferSize), &bytesRead, 0);
			//ASSERT(readResult != FALSE);
		}

		void FileImpl::Write(VoidPtr const buffer, UInt bufferSize) const
		{
			ASSERT(_hFile != 0);
			ASSERT(_isReadOnly == false);
			ASSERT(buffer != 0);
			DWORD bytesWritten;
			BOOL writeResult = WriteFile(_hFile, buffer, ToUInt32(bufferSize), &bytesWritten, 0);
			//ASSERT(writeResult != FALSE);
		}

		void FileImpl::Close()
		{
			if(_hFile)
			{
				CloseHandle(_hFile);
				_hFile = 0;
			}
		}

		FileImpl::~FileImpl()
		{
			Close();
		}
	}
}
