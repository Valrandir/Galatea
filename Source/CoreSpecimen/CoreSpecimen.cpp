#include "Core.hpp"
using namespace Core;

extern Bool TypesTest();
extern Bool AssertTest();
extern Bool ErrTest();
extern Bool MemoryTest();
extern Bool ThreadTest();
extern Bool ThreadedErrTest();
extern Bool TimeTest();
extern Bool VectorTest();
extern Bool StdVectorTest();
extern Bool StringTest();

Bool CoreSpecimen()
{
	Bool result = true;

	CHECK TypesTest();
	CHECK AssertTest();
	CHECK ErrTest();
	CHECK MemoryTest();
	CHECK ThreadTest();
	CHECK ThreadedErrTest();
	CHECK TimeTest();
	CHECK VectorTest();
	CHECK StringTest();

	return result;
}
