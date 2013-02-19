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
				void Close();
			};
		}
	}
}
