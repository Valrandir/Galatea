#pragma once
#include "../../Types.hpp"
#include "../../String/String.hpp"

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
				static File* Create(TChar const * fileName);
				static File* Open(TChar const * fileName);
				static File* OpenReadOnly(TChar const * fileName);
				static Bool Exists(TChar const * fileName);
				static Bool Delete(TChar const * fileName);
				static Int64 GetFileSize(TChar const * fileName);

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
