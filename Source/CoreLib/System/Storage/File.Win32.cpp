#pragma once
#include "File.Win32.hpp"

namespace Core
{
	namespace System
	{
		namespace Storage
		{
			File* CreateFile(TChar const * fileName, DWORD mode)
			{
				HANDLE hFile;
				hFile = ::CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, 0, mode, FILE_ATTRIBUTE_NORMAL, 0);

				if(hFile == INVALID_HANDLE_VALUE)
					return 0;
				else
					return new FileImpl(hFile);
			}

			File* File::Create(TChar const * fileName)
			{
				return CreateFile(fileName, CREATE_NEW);
			}

			File* File::Open(TChar const * fileName)
			{
				return CreateFile(fileName, OPEN_EXISTING);
			}

			File* File::CreateOrOpen(TChar const * fileName)
			{
				return CreateFile(fileName, OPEN_ALWAYS);
			}

			FileImpl::FileImpl(HANDLE hFile) : _hFile(hFile)
			{
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
