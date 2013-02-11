#include "Core.hpp"
using namespace Core;

extern Bool TypesTest();
extern void ErrTest();
extern void MemoryTest();
extern Bool ThreadTest();
extern void ThreadedErrTest();
extern void TimeTest();
extern Bool VectorTest();
extern Bool StdVectorTest();
extern Bool StringTest();

Bool CoreSpecimen()
{
	Bool result = true;

	CHECK TypesTest();

	ErrTest();
	MemoryTest();
	CHECK ThreadTest();
	//ThreadedErrTest();
	//TimeTest();

	CHECK VectorTest();
	CHECK StringTest();

	return result;
}
