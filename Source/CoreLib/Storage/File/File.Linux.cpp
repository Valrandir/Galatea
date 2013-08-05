#define _LARGEFILE64_SOURCE
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

		File* File::Create(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			Int32 fileId = open(fileName, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			return fileId == -1 ? NULL : new FileImpl(fileId, false);
		}
			
		File* File::Open(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			Int32 fileId = open(fileName, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
			return fileId == -1 ? NULL : new FileImpl(fileId, false);
		}

		File* File::OpenReadOnly(CStr fileName, CacheMode cacheMode)
		{
			ASSERT_PARAMETER(fileName);
			ASSERT(cacheMode == CacheMode::Default);
			Int32 fileId = open(fileName, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
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
			//return -1 != rename(fileName, newName);
			return true;
		}

		UInt64 File::GetFileSize(CStr fileName)
		{
			ASSERT_PARAMETER(fileName);
			struct stat st = {0};
			int ret = stat(fileName, &st);
			ASSERT(ret != -1);
			return st.st_size;
		}

		UInt64 FileImpl::GetFileSize() const
		{
			ASSERT(_fileId);
			struct stat st = {0};
			int ret = fstat(_fileId, &st);
			ASSERT(ret != -1);
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

		void FileImpl::Read(VoidPtr buffer, UInt bufferSize) const
		{
			ASSERT(_fileId);
			ASSERT(buffer != 0);
			read(_fileId, buffer, bufferSize);
			//size_t ret = read(_fileId, buffer, bufferSize);
			//ASSERT(ret != -1);
		}

		void FileImpl::Write(VoidPtr const buffer, UInt bufferSize) const
		{
			ASSERT(_fileId);
			ASSERT(_isReadOnly == false);
			ASSERT(buffer != 0);
			write(_fileId, buffer, bufferSize);
			//size_t ret = write(_fileId, buffer, bufferSize);
			//ASSERT(ret != -1);
		}

		void FileImpl::Close()
		{
			if(_fileId)
			{
				close(_fileId);
				_fileId = 0;
			}
		}

		FileImpl::~FileImpl()
		{
			Close();
		}
	}
}
