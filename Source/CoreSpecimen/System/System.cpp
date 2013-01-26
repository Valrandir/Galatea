#include "../Core.hpp"
using namespace Core;

void ErrTest()
{
	UInt32 ErrCode;
	TChar Buffer[512];
	TChar const * ErrText;

	System::SetErrCode(10U);
	ErrCode = System::GetErrCode();
	ErrText = System::GetErrText(ErrCode, Buffer, 512U);
}


//Test if SetErrCode / GetErrCode are thread safe
using namespace System;
using namespace Threading;

VoidPtr ThreadA(VoidPtr Param)
{
	UInt32* ErrCode = (UInt32*)Param;
	SetErrCode(*ErrCode);
	Time::Sleep(2500);
	*ErrCode = GetErrCode() + 100;
	return (VoidPtr)ErrCode;
}

VoidPtr ThreadB(VoidPtr Param)
{
	UInt32* ErrCode = (UInt32*)Param;
	SetErrCode(*ErrCode);
	Time::Sleep(5000);
	*ErrCode = GetErrCode() + 1;
	return (VoidPtr)ErrCode;
}

//Pass if aOut = 10U and bOut = 15U
//Fail if aOut == bOut
void ThreadedErrTest()
{
	UInt32 aIn = 10U;
	UInt32 bIn = 15U;
	Thread* aThread = CreateThread(ThreadA, (VoidPtr)&aIn);
	Thread* bThread = CreateThread(ThreadB, (VoidPtr)&bIn);
	//UInt32 aOut = *(UInt32*)aThread->Join();
	//UInt32 bOut = *(UInt32*)bThread->Join();
	UInt32* aOut = (UInt32*)aThread->Join();
	UInt32* bOut = (UInt32*)bThread->Join();
	Delete(aThread);
	Delete(bThread);
}
