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
			File* File::Open(CStr fileName, UInt32 flags)
			{
				Int32 fileId;
				UInt32 mode;

				Assert(fileName != NULL);

				if(flags == 0U)
					flags = OpenFlagEnum::OpenRead;

				mode = flags & OpenFlagEnum::OpenRead ? O_RDONLY : 0U;
				mode |= flags & OpenFlagEnum::OpenWrite ? O_WRONLY : 0U;
				mode |= flags & OpenFlagEnum::OpenOverwrite ? O_CREAT : 0U;

				fileId = open(fileName, mode);

				if(fileId == -1)
					return NULL;

				return new FileImpl(fileId);
			}

			Bool File::Exists(CStr fileName)
			{
				struct stat s;
				int ret;
				
				ret = stat(fileName, &s);

				return ret != -1;
			}

			Bool File::Delete(CStr fileName)
			{
				return unlink(fileName) == 0;
			}

			FileImpl::FileImpl(int fileId) : _fileId(fileId)
			{
			}

			FileImpl::~FileImpl()
			{
				Close();
			}

			UInt64 FileImpl::GetPosition() const
			{
				Assert(_fileId != 0);
				return lseek64(_fileId, 0, SEEK_CUR);
				return 0U;
			}

			void FileImpl::Seek(Int64 distance)
			{
				Assert(_fileId != 0);
				lseek64(_fileId, distance, SEEK_SET);
			}

			void FileImpl::SeekToEnd()
			{
				Assert(_fileId != 0);
				lseek64(_fileId, 0U, SEEK_END);
			}

			void FileImpl::Read(VoidPtr buffer, UInt32 bufferSize)
			{
				ssize_t ret;
				
				Assert(buffer != 0);
				Assert(_fileId != 0);

				ret = read(_fileId, buffer, bufferSize);
				Assert(ret != -1);
			}

			void FileImpl::Write(VoidPtr const buffer, UInt32 bufferSize)
			{
				ssize_t ret;

				Assert(buffer != 0);
				Assert(_fileId != 0);

				ret = write(_fileId, buffer, bufferSize);
				Assert(ret != -1);
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
}
