#include <Core.hpp>

using namespace Core;

void ErrTest()
{
	UInt32 ErrCode;
	Char buffer[512];
	CString ret;

	System::SetErrCode(10U);
	ErrCode = System::GetErrCode();
	ret = System::GetErrText(ErrCode, buffer, 512U);
	ErrCode = *ret; //To avoid a warning with GPP
}
