#pragma once
#include "../../Types.hpp"

namespace Core
{
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
			static File* Create(CStr fileName);
			static File* Open(CStr fileName);
			static File* OpenReadOnly(CStr fileName);
			static Bool Exists(CStr fileName);
			static Bool Delete(CStr fileName);
			static UInt64 GetFileSize(CStr fileName);

			virtual UInt64 GetFileSize() const = 0;
			virtual UInt64 GetSeekPos() const = 0;
			virtual void Seek(UInt64 position) const = 0;
			virtual void SeekToEnd() const = 0;
			virtual void Read(VoidPtr buffer, UInt bufferSize) const = 0;
			virtual void Write(VoidPtr const buffer, UInt bufferSize) const = 0;
			virtual void Close() = 0;
			virtual ~File();
		};
	}
}
