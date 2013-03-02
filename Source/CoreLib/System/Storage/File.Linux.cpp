#define _LARGEFILE64_SOURCE
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "File.Linux.hpp"
 
namespace Core
{
	namespace System
	{
		namespace Storage
		{
			FileImpl::FileImpl(int fileId) : _fileId(fileId)
			{
			}

			File* File::Create(CStr fileName)
			{
				Assert(fileName != NULL);
				Int32 fileId = open(fileName, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				return fileId == -1 ? NULL : new FileImpl(fileId);
			}
			
			File* File::Open(CStr fileName)
			{
				Assert(fileName != NULL);
				Int32 fileId = open(fileName, O_RDWR, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				return fileId == -1 ? NULL : new FileImpl(fileId);
			}

			File* File::OpenReadOnly(CStr fileName)
			{
				Assert(fileName != NULL);
				Int32 fileId = open(fileName, O_RDONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
				return fileId == -1 ? NULL : new FileImpl(fileId);
			}

			Bool File::Exists(CStr fileName)
			{
				Assert(fileName != NULL);
				struct stat st = {0};
				int ret = stat(fileName, &st);
				return ret != -1;
			}

			Bool File::Delete(CStr fileName)
			{
				Assert(fileName != NULL);
				return unlink(fileName) == 0;
			}

			Int64 File::GetFileSize(CStr fileName)
			{
				Assert(fileName != NULL);
				struct stat st = {0};
				int ret = stat(fileName, &st);
				Assert(ret != -1);
				return st.st_size;
			}

			Int64 FileImpl::GetFileSize() const
			{
				Assert(_fileId != 0);
				struct stat st = {0};
				int ret = fstat(_fileId, &st);
				Assert(ret != -1);
				return st.st_size;
			}

			Int64 FileImpl::GetSeekPos() const
			{
				Assert(_fileId != 0);
				return lseek64(_fileId, 0, SEEK_CUR);
				return 0U;
			}

			void FileImpl::Seek(Int64 position) const
			{
				Assert(_fileId != 0);
				lseek64(_fileId, position, SEEK_SET);
			}

			void FileImpl::SeekToEnd() const
			{
				Assert(_fileId != 0);
				lseek64(_fileId, 0U, SEEK_END);
			}

			void FileImpl::Read(VoidPtr buffer, UInt32 bufferSize) const
			{
				Assert(_fileId != 0);
				Assert(buffer != 0);
				read(_fileId, buffer, bufferSize);
				//size_t ret = read(_fileId, buffer, bufferSize);
				//Assert(ret != -1);
			}

			void FileImpl::Write(VoidPtr const buffer, UInt32 bufferSize) const
			{
				Assert(_fileId != 0);
				Assert(buffer != 0);
				write(_fileId, buffer, bufferSize);
				//size_t ret = write(_fileId, buffer, bufferSize);
				//Assert(ret != -1);
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
}
