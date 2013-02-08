#include "Core.hpp"
using namespace Core;

extern Bool TypesTest();
extern void ErrTest();
extern void MemoryTest();
extern void ThreadTestByValue();
extern void ThreadTestByRef();
extern void ThreadedErrTest();
extern void TimeTest();
extern Bool VectorTest();
extern Bool StdVectorTest();
extern Bool StringTest();

void CoreSpecimen()
{
	Bool Skip = true;

	TypesTest();
	StringTest();

	//Force linking of all tests
	//Select which test to run in debug mode.
	if(!Skip)
	{
		TypesTest();
		ErrTest();
		MemoryTest();
		ThreadTestByValue();
		ThreadTestByRef();
		ThreadedErrTest();
		TimeTest();
		VectorTest();
		StringTest();
	}
}
