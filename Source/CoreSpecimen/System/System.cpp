#include "../Core.hpp"
using namespace Core;
using namespace System;
using namespace Threading;

Bool ErrTest()
{
	Bool result = true;

	UInt32 errCode;
	TChar buffer[512];
	CStr errText;

	System::SetErrCode(10U);
	errCode = System::GetErrCode();
	errText = System::GetErrText(errCode, buffer, 512U);

	CHECK errCode == 10U;
	CHECK String::GetTCharLength(errText) > 4;
	
	return result;
}

VoidPtr ThreadA(VoidPtr Param)
{
	UInt32* errCode = (UInt32*)Param;
	SetErrCode(*errCode);
	Time::Sleep(20);
	*errCode = GetErrCode() + 100;
	return (VoidPtr)errCode;
}

VoidPtr ThreadB(VoidPtr Param)
{
	UInt32* errCode = (UInt32*)Param;
	Time::Sleep(10);
	SetErrCode(*errCode);
	*errCode = GetErrCode() + 1;
	return (VoidPtr)errCode;
}

//Test if SetErrCode / GetErrCode are thread safe
//Pass if aOut = 110U and bOut = 16U
//Fail if aOut == bOut
Bool ThreadedErrTest()
{
	Bool result = true;

	UInt32 aIn = 10U;
	UInt32 bIn = 15U;

	Thread* aThread = CreateThread(ThreadA, (VoidPtr)&aIn);
	Thread* bThread = CreateThread(ThreadB, (VoidPtr)&bIn);

	UInt32 aOut = *(UInt32*)aThread->Join();
	UInt32 bOut = *(UInt32*)bThread->Join();

	DeletePtr(aThread);
	DeletePtr(bThread);

	CHECK aOut == 110U;
	CHECK bOut == 16U;

	return result;
}
