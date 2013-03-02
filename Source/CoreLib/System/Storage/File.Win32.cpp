#include "File.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Storage
		{
			FileImpl::FileImpl(HANDLE hFile) : _hFile(hFile)
			{
			}

			File* File::Create(CStr fileName)
			{
				Assert(fileName != NULL);
				HANDLE hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
				return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile);
			}

			File* File::Open(CStr fileName)
			{
				Assert(fileName != NULL);
				HANDLE hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile);
			}

			File* File::OpenReadOnly(CStr fileName)
			{
				Assert(fileName != NULL);
				HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				return hFile == INVALID_HANDLE_VALUE ? NULL : new FileImpl(hFile);
			}

			Bool File::Exists(CStr fileName)
			{
				Assert(fileName != NULL);
				DWORD attr = GetFileAttributes(fileName);
				return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
			}

			Bool File::Delete(CStr fileName)
			{
				Assert(fileName != NULL);
				return DeleteFile(fileName) != 0;
			}

			Int64 File::GetFileSize(CStr fileName)
			{
				Assert(fileName != NULL);
				WIN32_FILE_ATTRIBUTE_DATA attr = {0};
				LARGE_INTEGER li;

				//Assert(GetFileAttributesEx(fileName, GetFileExInfoStandard, &attr));
				GetFileAttributesEx(fileName, GetFileExInfoStandard, &attr);
				li.LowPart = attr.nFileSizeLow;
				li.HighPart = attr.nFileSizeHigh;

				return li.QuadPart;
			}

			Int64 FileImpl::GetFileSize() const
			{
				Assert(_hFile != 0);
				LARGE_INTEGER fileSize;
				Assert(GetFileSizeEx(_hFile, &fileSize));
				return fileSize.QuadPart;
			}

			Int64 FileImpl::GetSeekPos() const
			{
				Assert(_hFile != 0);
				LARGE_INTEGER distance = {0};
				LARGE_INTEGER newPosition = {0};
				SetFilePointerEx(_hFile, distance, &newPosition, FILE_CURRENT);
				return newPosition.QuadPart;
			}

			void FileImpl::Seek(Int64 position) const
			{
				Assert(_hFile != 0);
				LARGE_INTEGER li;
				li.QuadPart = position;
				SetFilePointerEx(_hFile, li, 0, FILE_BEGIN);
			}

			void FileImpl::SeekToEnd() const
			{
				Assert(_hFile != 0);
				LARGE_INTEGER li;
				li.QuadPart = 0U;
				SetFilePointerEx(_hFile, li, 0, FILE_END);
			}

			void FileImpl::Read(VoidPtr buffer, UInt32 bufferSize) const
			{
				Assert(buffer != 0);
				Assert(_hFile != 0);
				DWORD bytesRead;
				BOOL readResult = ReadFile(_hFile, buffer, bufferSize, &bytesRead, 0);
				//Assert(readResult != FALSE);
			}

			void FileImpl::Write(VoidPtr const buffer, UInt32 bufferSize) const
			{
				Assert(buffer != 0);
				Assert(_hFile != 0);
				DWORD bytesWritten;
				BOOL writeResult = WriteFile(_hFile, buffer, bufferSize, &bytesWritten, 0);
				//Assert(writeResult != FALSE);
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
}
