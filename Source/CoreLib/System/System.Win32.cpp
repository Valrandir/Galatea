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

		CString GetErrText(UInt32 ErrCode, String Buffer, UInt32 BufferSize)
		{
			if(!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, 0, ErrCode, 0, Buffer, BufferSize, 0))
				*Buffer = 0;
			return Buffer;
		}
	}
}
