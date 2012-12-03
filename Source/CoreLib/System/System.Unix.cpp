#include <errno.h>
#include <string.h>
#include "System.hpp"

namespace Core
{
	namespace System
	{
		UInt32 GetErrCode()
		{
			return errno;
		}

		void SetErrCode(UInt32 ErrCode)
		{
			errno = ErrCode;
		}

		CString GetErrText(UInt32 ErrCode, String Buffer, UInt32 BufferSize)
		{
			return strerror_r(ErrCode, Buffer, BufferSize);
		}
	}
}
