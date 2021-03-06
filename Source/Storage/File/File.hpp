#pragma once
#include "../../Types.hpp"

namespace Galatea
{
	class Exception;

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
			enum Disposition
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

			enum Access
			{
				AccessRead,
				AccessWrite,
				AccessReadWrite
			};

			enum Flags
			{
				ShareRead = 0x1,
				ShareWrite = 0x2,
				OptimizeForRandomAccess = 0x4,
				OptimizeForSequentialAccess = 0x8
			};

			//Returns a File pointer which must be manually deleted after use.
			//On failure, returns a NULL pointer and initialize out_ex if it is set.
			static File* Open(CStr fileName, Disposition behavior, Access access, UInt32 flags, Exception* out_ex = nullptr);

			static Bool Exists(CStr fileName);
			static Bool Delete(CStr fileName);
			static Bool Move(CStr fileName, CStr newName);
			static Bool Copy(CStr fileName, CStr newName, Bool overwrite = false);
			static UInt64 GetFileSize(CStr fileName);

			virtual UInt64 GetFileSize() const = 0;
			virtual UInt64 GetSeekPos() const = 0;
			virtual void Seek(UInt64 position) const = 0;
			virtual void SeekToEnd() const = 0;
			virtual Bool Read(VoidPtr buffer, UInt bufferSize, Exception* out_ex = nullptr) const = 0;
			virtual Bool Write(VoidPtr const buffer, UInt bufferSize, Exception* out_ex = nullptr) const = 0;
			virtual void Close() = 0;
			virtual ~File();
		};
	}
}
