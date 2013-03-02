#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "File.hpp"

namespace Core
{
	namespace System
	{
		namespace Storage
		{
			class FileImpl : public File
			{
				HANDLE _hFile;

				public:
				FileImpl(HANDLE hFile);
				Int64 GetFileSize() const;
				Int64 GetSeekPos() const;
				void Seek(Int64 position) const;
				void SeekToEnd() const;
				void Read(VoidPtr buffer, UInt32 bufferSize) const;
				void Write(VoidPtr const buffer, UInt32 bufferSize) const;
				void Close();
				~FileImpl();
			};
		}
	}
}
