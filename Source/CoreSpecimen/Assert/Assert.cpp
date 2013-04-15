#include "../Core.hpp"

using namespace Core;

Bool ReturnTrue()
{
	return true;
}

Bool AssertTest()
{
	Bool result = true;

	//Pass
	ASSERT(ReturnTrue() == true);

	//Fail
	CHECK_ASSERT(ASSERT(ReturnTrue() == false));

	return result;
}
