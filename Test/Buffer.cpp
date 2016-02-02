#include "Galatea.hpp"
using namespace Galatea;

Bool CtorEmptyTest()
{
	Bool result = true;

	Buffer buff;

	CHECK buff.ByteSize() == 0;
	CHECK buff.DataPtr() == nullptr;

	return result;
}

Bool CtorParamTest()
{
	Bool result = true;

	Int32 size = sizeof(Int32);
	VoidPtr data = &size;

	Buffer buff(size);
	*static_cast<Int32*>(buff.DataPtr()) = size;

	CHECK buff.ByteSize() == size;
	CHECK *static_cast<Int32*>(buff.DataPtr()) == size;

	return result;
}

Bool CtorMoveTest()
{
	Bool result = true;

	Int32 size = sizeof(Int32);

	Buffer b1(size);
	*static_cast<Int32*>(b1.DataPtr()) = size;

	Buffer b2(reinterpret_cast<Buffer&&>(b1));

	CHECK b1.ByteSize() == 0;
	CHECK b1.DataPtr() == nullptr;

	CHECK b2.ByteSize() == size;
	CHECK *static_cast<Int32*>(b2.DataPtr()) == size;

	return result;
}

Bool OperatorMoveTest()
{
	Bool result = true;

	Int32 size = sizeof(Int32);

	Buffer b1(size);
	*static_cast<Int32*>(b1.DataPtr()) = size;

	Buffer b2;
	b2 = reinterpret_cast<Buffer&&>(b1);

	CHECK b1.ByteSize() == 0;
	CHECK b1.DataPtr() == nullptr;

	CHECK b2.ByteSize() == size;
	CHECK *static_cast<Int32*>(b2.DataPtr()) == size;

	return result;
}

Bool AllocateTest()
{
	Bool result = true;

	Int32 size = sizeof(Int32);

	Buffer buff;
	buff.Allocate(size);

	CHECK buff.ByteSize() == size;
	CHECK buff.DataPtr() != nullptr;

	return result;
}

Bool BufferTest()
{
	Bool result = true;

	CHECK CtorEmptyTest();
	CHECK CtorParamTest();
	CHECK CtorMoveTest();
	CHECK OperatorMoveTest();
	CHECK AllocateTest();

	return result;
}
