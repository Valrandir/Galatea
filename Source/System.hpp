#pragma once
#include "Types.hpp"
#include "String/String.hpp"

namespace Galatea
{
	UInt32 GetErrCode();
	void SetErrCode(UInt32 errCode);
	CStr GetErrText(UInt32 errCode, TChar* buffer, UInt32 bufferSize);
	String GetErrText(UInt32 errCode);
}
