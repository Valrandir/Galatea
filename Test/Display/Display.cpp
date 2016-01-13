#include "../Galatea.hpp"
using namespace Galatea;

extern Bool BubbleTest();
extern Bool ZoneTest();

Bool DisplayTest()
{
	Bool result = true;

	CHECK BubbleTest();
	CHECK ZoneTest();

	return true;
}
