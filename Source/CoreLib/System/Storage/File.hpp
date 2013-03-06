#pragma once
#include "../../Types.hpp"

namespace Core
{
	namespace System
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
				static Int64 GetFileSize(CStr fileName);

				virtual Int64 GetFileSize() const = 0;
				virtual Int64 GetSeekPos() const = 0;
				virtual void Seek(Int64 position) const = 0;
				virtual void SeekToEnd() const = 0;
				virtual void Read(VoidPtr buffer, UInt32 bufferSize) const = 0;
				virtual void Write(VoidPtr const buffer, UInt32 bufferSize) const = 0;
				virtual void Close() = 0;
				virtual ~File();
			};
		}
	}
}
