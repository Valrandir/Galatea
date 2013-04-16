#include <errno.h>
#include <string.h>
#include "System.hpp"

namespace Core
{
	UInt32 GetErrCode()
	{
		return errno;
	}

	void SetErrCode(UInt32 errCode)
	{
		errno = errCode;
	}

	CStr GetErrText(UInt32 errCode, TChar* buffer, UInt32 bufferSize)
	{
		return strerror_r(errCode, buffer, bufferSize);
	}
}
