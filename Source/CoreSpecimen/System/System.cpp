#include <Core.hpp>
using namespace Core;

void ErrTest()
{
	UInt32 ErrCode;
	Char Buffer[512];
	CString ErrText;

	System::SetErrCode(10U);
	ErrCode = System::GetErrCode();
	ErrText = System::GetErrText(ErrCode, Buffer, 512U);
	ErrCode = *ErrText; //To avoid a warning with GPP
}
