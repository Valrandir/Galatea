#define _LARGEFILE64_SOURCE
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "File.Linux.hpp"
#include "../../Assert/Assert.hpp"

namespace Core
{
	namespace Storage
	{
		FileImpl::FileImpl(int fileId, Bool readOnly) : _fileId(fileId), _isReadOnly(readOnly)
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

			//HANDLE hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			Int32 fileId = open(fileName, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			ASSERT_COREX(fileId != -1, corex);
			return fileId == -1 ? NULL : new FileImpl(fileId, false);
		}

		//Return NULL on failure, and initialize corex when specified.
		File* File::Open(CStr fileName, CoreException* corex)
		{
			ASSERT_PARAMETER(fileName);
			//HANDLE hFile = CreateFile(fileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			Int32 fileId = open(fileName, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			ASSERT_COREX(fileId != -1, corex);
			return fileId == -1 ? NULL : new FileImpl(fileId, false);
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
			Int32 fileId = open(fileName, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			ASSERT_COREX(fileId != -1, corex);
			return fileId == -1 ? NULL : new FileImpl(fileId, true);
		}

		Bool File::Exists(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			struct stat st = {0};
			int ret = stat(fileName, &st);
			return ret != -1;
		}

		Bool File::Delete(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			return unlink(fileName) == 0;
		}

		Bool File::Move(CStr fileName, CStr newName)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT_PARAMETER(newName);
 			return rename(fileName, newName) != -1;
		}

		UInt64 File::GetFileSize(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			struct stat st = {0};
			stat(fileName, &st);
			//int ret = stat(fileName, &st);
			//ASSERT(ret != -1);
			return st.st_size;
		}

		UInt64 FileImpl::GetFileSize() const
		{
			ASSERT(_fileId);
			struct stat st = {0};
			fstat(_fileId, &st);
			//int ret = fstat(_fileId, &st);
			//ASSERT(ret != -1);
			return st.st_size;
		}

		UInt64 FileImpl::GetSeekPos() const
		{
			ASSERT(_fileId);
			return lseek64(_fileId, 0, SEEK_CUR);
			return 0U;
		}

		void FileImpl::Seek(UInt64 position) const
		{
			ASSERT(_fileId);
			lseek64(_fileId, position, SEEK_SET);
		}

		void FileImpl::SeekToEnd() const
		{
			ASSERT(_fileId);
			lseek64(_fileId, 0U, SEEK_END);
		}

		//When corex is NULL, ASSERT on failure.
		//When corex is not NULL, return false on failure.
		//Return true on success
		Bool FileImpl::Read(VoidPtr buffer, UInt bufferSize, CoreException* corex) const
		{
			ASSERT(_fileId);
			ASSERT(buffer != 0);
			Bool result = read(_fileId, buffer, bufferSize) != -1;
			ASSERT_COREX(result, corex);
			if(!corex) ASSERT_SYSTEMCALL(result);
			return result;
		}

		//When corex is NULL, ASSERT on failure.
		//When corex is not NULL, return false on failure.
		//Return true on success
		Bool FileImpl::Write(VoidPtr const buffer, UInt bufferSize, CoreException* corex) const
		{
			ASSERT(_fileId);
			ASSERT(_isReadOnly == false);
			ASSERT(buffer != 0);
			Bool result = write(_fileId, buffer, bufferSize) != -1;
			ASSERT_COREX(result, corex);
			if(!corex) ASSERT_SYSTEMCALL(result);
			return result;
		}

		void FileImpl::Close()
		{
			if(_fileId)
			{
				close(_fileId);
				_fileId = 0;
			}
		}
	}
}
