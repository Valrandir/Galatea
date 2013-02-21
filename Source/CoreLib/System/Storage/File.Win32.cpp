#pragma once
#include "File.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Storage
		{
			File* File::Open(TChar const * fileName, UInt flags)
			{
				DWORD access;
				DWORD share;
				DWORD overwrite;
				HANDLE hFile;

				Assert(fileName != NULL);

				if(flags == 0)
					flags = OpenFlagEnum::OpenRead;

				access = flags & OpenFlagEnum::OpenRead ? GENERIC_READ : 0;
				access |= flags & OpenFlagEnum::OpenWrite ? GENERIC_WRITE : 0;
				share = flags & OpenFlagEnum::OpenExclusive ? 0 : FILE_SHARE_READ;
				overwrite = flags & OpenFlagEnum::OpenOverwrite ? CREATE_ALWAYS : OPEN_ALWAYS;

				hFile = CreateFile(fileName, access, share, 0, overwrite, FILE_ATTRIBUTE_NORMAL, 0);

				if(hFile == INVALID_HANDLE_VALUE)
					return NULL;

				return new FileImpl(hFile);
			}

			Bool File::Exists(TChar const * fileName)
			{
				DWORD attr = GetFileAttributes(fileName);
				return attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY);
			}

			Bool File::Delete(TChar const * fileName)
			{
				return DeleteFile(fileName) != 0;
			}

			FileImpl::FileImpl(HANDLE hFile) : _hFile(hFile)
			{
			}

			FileImpl::~FileImpl()
			{
				Close();
			}

			UInt64 FileImpl::GetPosition() const
			{
				LARGE_INTEGER li[2];

				Assert(_hFile != 0);

				li[0].QuadPart = 0U;
				li[1].QuadPart = 0U;

				SetFilePointerEx(_hFile, *li, li + 1, FILE_CURRENT);

				return li[1].QuadPart;
			}

			void FileImpl::Seek(Int64 distance)
			{
				LARGE_INTEGER li;

				Assert(_hFile != 0);

				li.QuadPart = distance;
				SetFilePointerEx(_hFile, li, 0, FILE_BEGIN);
			}

			void FileImpl::SeekToEnd()
			{
				LARGE_INTEGER li;

				Assert(_hFile != 0);

				li.QuadPart = 0U;
				SetFilePointerEx(_hFile, li, 0, FILE_END);
			}

			void FileImpl::Read(VoidPtr buffer, UInt bufferSize)
			{
				DWORD bytesRead;
				BOOL readResult;

				Assert(buffer != 0);
				Assert(_hFile != 0);

				readResult = ReadFile(_hFile, buffer, bufferSize, &bytesRead, 0);
				Assert(readResult != FALSE);
			}

			void FileImpl::Write(VoidPtr const buffer, UInt bufferSize)
			{
				DWORD bytesWritten;
				BOOL writeResult;

				Assert(buffer != 0);
				Assert(_hFile != 0);

				writeResult = WriteFile(_hFile, buffer, bufferSize, &bytesWritten, 0);
				Assert(writeResult != FALSE);
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
}
