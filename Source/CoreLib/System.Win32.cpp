#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "System.hpp"

namespace Core
{
	UInt32 GetErrCode()
	{
		return GetLastError();
	}

	void SetErrCode(UInt32 errCode)
	{
		SetLastError(errCode);
	}

	CStr GetErrText(UInt32 errCode, TChar* buffer, UInt32 bufferSize)
	{
		if(!FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, errCode, 0, buffer, bufferSize, NULL))
			*buffer = 0;
		return buffer;
	}
}
