#include "Galatea.hpp"
using namespace Galatea;

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

Bool AssertOverride(Galatea::Exception const & ex)
{
	throw ex;
}

Bool TestMain()
{
	Bool result = true;

	Assert::SetAssertProc(AssertOverride);

	//CHECK DisplayTest();

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

	return result;
}
