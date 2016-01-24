#include "../Galatea.hpp"
using namespace Galatea;

extern Bool BubbleTest();
extern Bool ZoneTest();
extern Bool SpriteTest();

Bool DisplayTest()
{
	Bool result = true;

	CHECK BubbleTest();
	CHECK ZoneTest();
	CHECK SpriteTest();

	return true;
}
