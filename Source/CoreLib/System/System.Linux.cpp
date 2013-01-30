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

		TChar const * GetErrText(UInt32 ErrCode, TChar* Buffer, UInt32 BufferSize)
		{
			return strerror_r(ErrCode, Buffer, BufferSize);
		}
	}
}
