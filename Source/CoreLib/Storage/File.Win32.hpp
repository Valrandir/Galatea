#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "File.hpp"

namespace Core
{
	namespace Storage
	{
		class FileImpl : public File
		{
			HANDLE _hFile;
			Bool _isReadOnly;

			public:
			FileImpl(HANDLE hFile, Bool readOnly);
			UInt64 GetFileSize() const;
			UInt64 GetSeekPos() const;
			void Seek(UInt64 position) const;
			void SeekToEnd() const;
			void Read(VoidPtr buffer, UInt32 bufferSize) const;
			void Write(VoidPtr const buffer, UInt32 bufferSize) const;
			void Close();
			~FileImpl();
		};
	}
}
