#pragma once
#include "File.hpp"

namespace Core
{
	namespace System
	{
		namespace Storage
		{
			class FileImpl : public File
			{
				Int32 _fileId;

				public:
				FileImpl(int fileId);
				~FileImpl();

				UInt64 GetPosition() const;
				void Seek(Int64 distance);
				void SeekToEnd();
				void Read(VoidPtr buffer, UInt32 bufferSize);
				void Write(VoidPtr const buffer, UInt32 bufferSize);
				void Close();
			};
		}
	}
}
