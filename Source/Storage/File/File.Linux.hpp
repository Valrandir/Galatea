#pragma once
#include "File.hpp"

namespace Core
{
	namespace Storage
	{
		class FileImpl : public File
		{
			Int32 _fileId;
			Bool _isReadOnly;

			public:
			FileImpl(int fileId, Bool readOnly);
			~FileImpl();

			UInt64 GetFileSize() const;
			UInt64 GetSeekPos() const;
			void Seek(UInt64 position) const;
			void SeekToEnd() const;
			Bool Read(VoidPtr buffer, UInt bufferSize, CoreException* corex = NULL) const;
			Bool Write(VoidPtr const buffer, UInt bufferSize, CoreException* corex = NULL) const;
			void Close();
		};
	}
}
