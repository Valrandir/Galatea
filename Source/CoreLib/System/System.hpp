#pragma once
#include "../Types.hpp"

namespace Core
{
	namespace System
	{
		UInt32 GetErrCode();
		void SetErrCode(UInt32 ErrCode);
		CString GetErrText(UInt32 ErrCode, String Buffer, UInt32 BufferSize);
	}
}
