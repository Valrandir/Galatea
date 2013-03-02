#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "System.hpp"

namespace Core
{
	namespace System
	{
		UInt32 GetErrCode()
		{
			return GetLastError();
		}

		void SetErrCode(UInt32 ErrCode)
		{
			SetLastError(ErrCode);
		}

		CStr GetErrText(UInt32 ErrCode, TChar* Buffer, UInt32 BufferSize)
		{
			if(!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, ErrCode, 0, Buffer, BufferSize, NULL))
				*Buffer = 0;
			return Buffer;
		}
	}
}
