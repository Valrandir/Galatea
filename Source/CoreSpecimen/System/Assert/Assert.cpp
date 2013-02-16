#include "../../Core.hpp"

using namespace Core;

Bool ReturnTrue()
{
	return true;
}

Bool AssertTest()
{
	Bool result = true;

	//Pass
	Assert(ReturnTrue() == true);

	//Fail
	//Assert(ReturnTrue() == false);

	return result;
}
