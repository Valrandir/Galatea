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
				~FileImpl();

				UInt64 GetPosition() const;
				void Seek(Int64 distance);
				void SeekToEnd();
				void Read(VoidPtr buffer, UInt bufferSize);
				void Write(VoidPtr const buffer, UInt bufferSize);
				void Close();
			};
		}
	}
}
