#include <errno.h>
#include <string.h>
#include "System.hpp"

namespace Core
{
	UInt32 GetErrCode()
	{
		return errno;
	}

	void SetErrCode(UInt32 ErrCode)
	{
		errno = ErrCode;
	}

	CStr GetErrText(UInt32 ErrCode, TChar* Buffer, UInt32 BufferSize)
	{
		return strerror_r(ErrCode, Buffer, BufferSize);
	}
}
