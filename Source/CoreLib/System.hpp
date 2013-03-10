#pragma once
#include "Types.hpp"

namespace Core
{
	UInt32 GetErrCode();
	void SetErrCode(UInt32 ErrCode);
	CStr GetErrText(UInt32 ErrCode, TChar* Buffer, UInt32 BufferSize);
}
