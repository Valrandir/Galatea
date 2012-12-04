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


//Test if SetErrCode / GetErrCode are thread safe
using namespace System;
using namespace Threading;

VoidPtr ThreadA(VoidPtr Param)
{
	UInt32 ErrCode = (UInt32)Param;
	SetErrCode(ErrCode);
	Time::Sleep(2500);
	return (VoidPtr)GetErrCode();
}

VoidPtr ThreadB(VoidPtr Param)
{
	UInt32 ErrCode = (UInt32)Param;
	SetErrCode(ErrCode);
	Time::Sleep(5000);
	return (VoidPtr)GetErrCode();
}

void ThreadedErrTest()
{
	//Pass if code_a = 10U and code_b = 15U
	//Fail if code_a == code_b
	Thread* a = CreateThread(ThreadA, (VoidPtr)10U);
	Thread* b = CreateThread(ThreadA, (VoidPtr)15U);
	UInt32 code_a = (UInt32)a->Join();
	UInt32 code_b = (UInt32)b->Join();
}
