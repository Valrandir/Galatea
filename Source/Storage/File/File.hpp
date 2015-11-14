#pragma once
#include "../../Types.hpp"

namespace Core
{
	class CoreException;

	namespace Storage
	{
		class File
		{
			private:
			File(File const &);
			File& operator=(File&);

			protected:
			File();

			public:
			enum DispositionEnum
			{
				//Creates a new file, always.
				CreateAlways,
				//Creates a new file, only if it does not already exist.
				CreateNew,
				//Opens a file, always.
				OpenAlways,
				//Opens a file or device, only if it exists.
				OpenExisting,
				//Opens a file and truncates it so that its size is zero bytes, only if it exists.
				TruncateExisting
			};

			enum AccessEnum
			{
				AccessRead,
				AccessWrite,
				AccessReadWrite
			};

			enum FlagsEnum
			{
				ShareRead = 0x1,
				ShareWrite = 0x2,
				OptimizeForRandomAccess = 0x4,
				OptimizeForSequentialAccess = 0x8
			};

			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize corex if it is set.
			static File* Open(CStr fileName, DispositionEnum behavior, AccessEnum access, UInt32 flags, CoreException* corex = NULL);

			static Bool Exists(CStr fileName);
			static Bool Delete(CStr fileName);
			static Bool Move(CStr fileName, CStr newName);
			static Bool Copy(CStr fileName, CStr newName);
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
