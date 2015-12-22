#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "File.hpp"

namespace Galatea
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
			Bool Read(VoidPtr buffer, UInt bufferSize, Exception* out_ex = NULL) const;
			Bool Write(VoidPtr const buffer, UInt bufferSize, Exception* out_ex = NULL) const;
			void Close();
			~FileImpl();
		};
	}
}
