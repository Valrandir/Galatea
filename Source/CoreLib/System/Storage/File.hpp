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
				private:
				File(File const &);
				File& operator=(File&);

				protected:
				File();

				public:
				enum OpenFlagEnum
				{
					OpenRead = 1,
					OpenWrite = 2,
					OpenOverwrite = 4,
					OpenExclusive = 8
				};

				static File* Open(TChar const * fileName, UInt32 flags);
				static Bool Exists(TChar const * fileName);
				static Bool Delete(TChar const * fileName);

				virtual ~File();

				virtual UInt64 GetPosition() const = 0;
				virtual void Seek(Int64 distance) = 0;
				virtual void SeekToEnd() = 0;
				virtual void Read(VoidPtr buffer, UInt32 bufferSize) = 0;
				virtual void Write(VoidPtr const buffer, UInt32 bufferSize) = 0;
				virtual void Close() = 0;
			};
		}
	}
}
