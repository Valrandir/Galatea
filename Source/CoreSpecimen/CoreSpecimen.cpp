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
extern Bool FileTest();
extern Bool TextFileTest();
extern Bool IniFileTest();
extern Bool DisplayTest();

Bool AssertOverride(Core::CoreException const & coreEx)
{
	throw coreEx;
}

Bool CoreSpecimen()
{
	Bool result = true;

	Assert::SetAssertProc(AssertOverride);

#ifdef this_is_not_defined
	CHECK AssertTest();
	CHECK TypesTest();
	CHECK ErrTest();
	CHECK MemoryTest();
	CHECK ThreadTest();
	CHECK ThreadedErrTest();
	CHECK TimeTest();
	CHECK VectorTest();
	CHECK StringTest();
	CHECK FileTest();
	CHECK TextFileTest();
	CHECK IniFileTest();
#endif

	CHECK DisplayTest();

	return result;
}
