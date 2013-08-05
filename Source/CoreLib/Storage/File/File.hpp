#pragma once
#include "../../Types.hpp"

namespace Core
{
	class CoreException;

	namespace Storage
	{
		class File
		{
			protected:
			File();

			private:
			File(File const &);
			File& operator=(File&);

			public:
			enum CacheMode
			{
				Default = 0,
				Random = 1,
				Sequential = 2
			};

			//Overwrite Existing, ReadWrite, NoShare
			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize corex if it is set.
			static File* Create(CStr fileName, CoreException* corex = NULL);

			//FileMustExist, ReadWrite, NoShare
			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize corex if it is set.
			static File* Open(CStr fileName, CoreException* corex = NULL);

			//FileMustExist, ReadOnly, Share
			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize corex if it is set.s
			static File* OpenReadOnly(CStr fileName);
			static File* OpenReadOnly(CStr fileName, CoreException* corex);
			static File* OpenReadOnly(CStr fileName, CacheMode cacheMode);
			static File* OpenReadOnly(CStr fileName, CacheMode cacheMode, CoreException* corex);

			static Bool Exists(CStr fileName);
			static Bool Delete(CStr fileName);
			static Bool Move(CStr fileName, CStr newName);
			static UInt64 GetFileSize(CStr fileName);

			virtual UInt64 GetFileSize() const = 0;
			virtual UInt64 GetSeekPos() const = 0;
			virtual void Seek(UInt64 position) const = 0;
			virtual void SeekToEnd() const = 0;
			virtual Bool Read(VoidPtr buffer, UInt bufferSize, CoreException* corex = NULL) const = 0;
			virtual Bool Write(VoidPtr const buffer, UInt bufferSize, CoreException* corex = NULL) const = 0;
			virtual void Close() = 0;
			virtual ~File();
		};
	}
}
