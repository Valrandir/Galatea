#pragma once
#include "../Types.hpp"

namespace Core
{
	namespace System
	{
		UInt32 GetErrCode();
		void SetErrCode(UInt32 ErrCode);
		CStr GetErrText(UInt32 ErrCode, TChar* Buffer, UInt32 BufferSize);
	}
}
